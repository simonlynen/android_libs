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
 * \file casock/rpc/asio/protobuf/client/RPCClientCommunicator.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/asio/protobuf/client/RPCClientCommunicator.h"

#include <boost/bind.hpp>

#include "casock/util/Logger.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallHash.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"

namespace casock {
  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace client {
          RPCClientCommunicator::RPCClientCommunicator (casock::proactor::asio::base::SocketChannel* const pChannel, RPCCallHash& rCallHash, RPCCallQueue& rCallQueue)
            : casock::rpc::asio::protobuf::base::RPCCommunicator (pChannel), mrCallHash (rCallHash), mrCallQueue (rCallQueue)
          { }

          ::google::protobuf::Message* RPCClientCommunicator::createRecvMessage ()
          {
            LOGMSG (MEDIUM_LEVEL, "RPCClientCommunicator::%s ()\n", __FUNCTION__);
            return new casock::rpc::protobuf::api::RpcResponse ();
          }

          void RPCClientCommunicator::onRecvResponse (const ::asio::error_code& error, ::google::protobuf::Message* pMessage)
          {
            LOGMSG (NO_DEBUG, "%s\n", __PRETTY_FUNCTION__);

            if (! error)
            {
              LOGMSG (LOW_LEVEL, "%s - no error!\n", __PRETTY_FUNCTION__);

              casock::rpc::protobuf::api::RpcResponse* pResponse = static_cast<casock::rpc::protobuf::api::RpcResponse *>(pMessage);

              LOGMSG (LOW_LEVEL, "%s - response received: %d bytes - id [%u]\n", __PRETTY_FUNCTION__, pResponse->ByteSize (), pResponse->id ());

              casock::rpc::protobuf::client::RPCCall* pCall = mrCallHash.pop (pResponse->id ());

              if (pCall)
              {
                pCall->setRpcResponse (pResponse);
                mrCallQueue.push (pCall);
              }
              else
              {
                LOGMSG (NO_DEBUG, "%s - pCall not found in mrCallHash for ID [%u]\n", __PRETTY_FUNCTION__, pResponse->id ());
                delete pResponse;
              }

              try
              {
                recvResponse (::boost::bind (&RPCClientCommunicator::onRecvResponse, this, ::asio::placeholders::error, _2));
              }
              catch (casock::base::CASClosedConnectionException& e)
              {
                LOGMSG (NO_DEBUG, "%s - catch (casock::base::CASClosedConnectionException&) [%s]\n", __PRETTY_FUNCTION__, e.what ());
              }
            }
            else
            {
              LOGMSG (LOW_LEVEL, "%s - error [%s]\n", __PRETTY_FUNCTION__, error.message ().c_str ());
            }
          }

          void RPCClientCommunicator::startReceivingResponses ()
          {
            try
            {
              recvResponse (::boost::bind (&RPCClientCommunicator::onRecvResponse, this, ::asio::placeholders::error, _2));
            }
            catch (casock::base::CASClosedConnectionException& e)
            {
              LOGMSG (NO_DEBUG, "%s - catch (casock::base::CASClosedConnectionException&) [%s]\n", __PRETTY_FUNCTION__, e.what ());
            }
          }

          void RPCClientCommunicator::sendRequest (const ::google::protobuf::Message& message, ::boost::function<void(const ::asio::error_code&)> handler)
          {
            LOGMSG (MEDIUM_LEVEL, "RPCClientCommunicator::%s () - sending size [%zd]\n", __FUNCTION__, message.ByteSize ());
            sendMessage (message, handler);
          }

          void RPCClientCommunicator::recvResponse (::boost::function<void(const ::asio::error_code&, ::google::protobuf::Message*)> handler)
          {
            LOGMSG (NO_DEBUG, "RPCClientCommunicator::%s ()\n", __FUNCTION__);
            recvMessage (handler);
          }
        }
      }
    }
  }
}
