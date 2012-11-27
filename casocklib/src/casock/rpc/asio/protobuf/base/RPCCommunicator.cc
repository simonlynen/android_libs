/*
 * casocklib - An asynchronous communication library for C++
 * ---------------------------------------------------------
 * Copyright (C) 2010 Leandro Costa
 *
 * This file is part of casocklib.
 *
 * casocklib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * casocklib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with casocklib. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file casock/rpc/asio/protobuf/base/RPCCommunicator.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/asio/protobuf/base/RPCCommunicator.h"

#include <boost/bind.hpp>
#include <google/protobuf/message.h>

#include "casock/util/Logger.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/base/CASRPCException.h"
#include "casock/rpc/base/CASRPCUnfinishedMessageException.h"

namespace casock {
  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace base {
          RPCCommunicator::RPCCommunicator (SocketChannel* const pChannel) : casock::proactor::asio::base::Communicator (pChannel)
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::RPCCommunicator () - p [%zp]\n", this);
          }

          void RPCCommunicator::onSentMessage (const ::asio::error_code& error, const std::stringstream* pBuffer, ::boost::function<void(const ::asio::error_code&)> handler)
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - p [%zp]\n", __FUNCTION__, this);
            delete pBuffer;
            handler (error);
          }

          void RPCCommunicator::onReadSize (const ::asio::error_code& error, size_t* pSize, ::boost::function<void(const ::asio::error_code&, google::protobuf::Message*)> handler)
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - p [%zp]\n", __FUNCTION__, this);

            if (! error)
            {
              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - size [%zu]\n", __FUNCTION__, *pSize);
              char* pBuffer = new char [*pSize];
              read (pBuffer, *pSize, ::boost::bind (&RPCCommunicator::onReadBuffer, this, ::asio::placeholders::error, pBuffer, pSize, handler));
            }
            else
            {
              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              delete pSize;
            }
          }

          void RPCCommunicator::onReadBuffer (const ::asio::error_code& error, char* pBuffer, size_t* pSize, ::boost::function<void(const ::asio::error_code&, google::protobuf::Message*)> handler)
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - p [%zp]\n", __FUNCTION__, this);

            google::protobuf::Message* pResponse = NULL;

            if (! error)
            {
              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - no error!\n", __FUNCTION__);
              pResponse = createRecvMessage ();
              std::stringstream ss (std::string (pBuffer, *pSize));
              pResponse->ParseFromIstream (&ss);
            }
            else
            {
              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
            }

            delete[] pBuffer;
            delete pSize;

            handler (error, pResponse);
          }

          void RPCCommunicator::sendMessage (const ::google::protobuf::Message& message, ::boost::function<void(const ::asio::error_code&)> handler)
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - p [%zp]\n", __FUNCTION__, this);
            LOGMSG (NO_DEBUG, "RPCCommunicator::%s () - sending size [%zd]\n", __FUNCTION__, message.ByteSize ());

            size_t size = message.ByteSize ();
            std::stringstream* pBuffer = new std::stringstream (std::ios_base::in | std::ios_base::out | std::ios_base::binary);
            pBuffer->write (reinterpret_cast<const char*> (&size), sizeof (size_t));
            message.SerializeToOstream (pBuffer);
            write (pBuffer->str ().c_str (), size + sizeof (size_t), ::boost::bind (&RPCCommunicator::onSentMessage, this, ::asio::placeholders::error, pBuffer, handler));
          }

          void RPCCommunicator::recvMessage (::boost::function<void(const ::asio::error_code&, ::google::protobuf::Message*)> handler)
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - p [%zp]\n", __FUNCTION__, this);
            LOGMSG (NO_DEBUG, "RPCCommunicator::%s () - receiving size...\n", __FUNCTION__);
            size_t* pSize = new size_t;
            read (*pSize, ::boost::bind (&RPCCommunicator::onReadSize, this, ::asio::placeholders::error, pSize, handler));
          }
        }
      }
    }
  }
}
