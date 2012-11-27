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
 * \file casock/rpc/asio/protobuf/server/RPCServerCommunicator.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/asio/protobuf/server/RPCServerCommunicator.h"

#include <boost/bind.hpp>

#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/server/RPCCall.h"
#include "casock/rpc/protobuf/server/RPCCallQueue.h"
#include "casock/util/Logger.h"

namespace casock {
  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace server {
          RPCServerCommunicator::RPCServerCommunicator (
              SocketChannel* const pChannel,
              RPCCallQueue& rCallQueue)
            : casock::rpc::asio::protobuf::base::RPCCommunicator (pChannel), mrCallQueue (rCallQueue)
          { }

          ::google::protobuf::Message* RPCServerCommunicator::createRecvMessage ()
          {
            LOGMSG (MEDIUM_LEVEL, "RPCServerCommunicator::%s ()\n", __FUNCTION__);
            return new casock::rpc::protobuf::api::RpcRequest ();
          }

          void RPCServerCommunicator::onRecvRequest (const ::asio::error_code& error, ::google::protobuf::Message* pMessage)
          {
            LOGMSG (LOW_LEVEL, "RPCServerCommunicator::%s () - error [%d], pMessage [%p]\n", __FUNCTION__, error.value (), pMessage);

            if (! error)
            {
              casock::rpc::protobuf::api::RpcRequest* request = static_cast<casock::rpc::protobuf::api::RpcRequest *> (pMessage);

              LOGMSG (HIGH_LEVEL, "RPCServerCommunicator::%s () - request received: %d bytes - id [%u], operation [%s]\n", __FUNCTION__, request->ByteSize (), request->id (), request->operation ().c_str ());

              /*!
               * The RPCCall will be deleted by RPCCallEntry destructor.
               * The RPCCallEntry will be created by RPCCallHandler<_TpResponseHandler>::run () 
               *  and deleted on RPCCallHandler<_TpResponseHandler>::callback (RPCCallEntry*).
               */
              mrCallQueue.push (new casock::rpc::protobuf::server::RPCCall (this, request));

              try
              {
                recvRequest (::boost::bind (&RPCServerCommunicator::onRecvRequest, this, ::asio::placeholders::error, _2));
              }
              catch (casock::base::CASClosedConnectionException& e)
              {
                LOGMSG (NO_DEBUG, "RPCServerCommunicator::%s () - catch (casock::base::CASClosedConnectionException&) [%s]\n", __FUNCTION__, e.what ());
                invalidateCalls ();
              }
            }
            else
            {
              invalidateCalls ();
            }
          }

          void RPCServerCommunicator::onSentResponse (const ::asio::error_code& error)
          {
            LOGMSG (LOW_LEVEL, "RPCServerCommunicator::%s () - error [%d]\n", __FUNCTION__, error.value ());
          }

          void RPCServerCommunicator::startReceivingRequests ()
          {
            LOGMSG (LOW_LEVEL, "RPCServerCommunicator::%s ()\n", __FUNCTION__);

            try
            {
              recvRequest (::boost::bind (&RPCServerCommunicator::onRecvRequest, this, ::asio::placeholders::error, _2));
            }
            catch (casock::base::CASClosedConnectionException& e)
            {
              LOGMSG (NO_DEBUG, "RPCServerCommunicator::%s () - catch (casock::base::CASClosedConnectionException&) [%s]\n", __FUNCTION__, e.what ());
            }
          }

          void RPCServerCommunicator::recvRequest (::boost::function<void(const ::asio::error_code&, ::google::protobuf::Message*)> handler)
          {
            LOGMSG (MEDIUM_LEVEL, "RPCServerCommunicator::%s ()\n", __FUNCTION__);
            recvMessage (handler);
          }

          void RPCServerCommunicator::sendResponse (const ::google::protobuf::Message& message, ::boost::function<void(const ::asio::error_code&)> handler)
          {
            LOGMSG (MEDIUM_LEVEL, "RPCServerCommunicator::%s ()\n", __FUNCTION__);
            sendMessage (message, handler);
          }

          void RPCServerCommunicator::callback (const casock::rpc::protobuf::api::RpcResponse& response)
          {
            LOGMSG (LOW_LEVEL, "RPCServerCommunicator::%s ()\n", __FUNCTION__);

            try
            {
              sendResponse (response, ::boost::bind (&RPCServerCommunicator::onSentResponse, this, ::asio::placeholders::error));
            }
            catch (casock::base::CASClosedConnectionException& e)
            {
              LOGMSG (NO_DEBUG, "RPCServerCommunicator::%s () - catch (casock::base::CASClosedConnectionException&) [%s]\n", __FUNCTION__, e.what ());
            }
          }
        }
      }
    }
  }
}
