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
 * \file casock/rpc/asio/protobuf/server/RPCServerProxy.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_

#include "casock/rpc/protobuf/server/RPCServerProxy.h"

namespace casock {
  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace server {
          class RPCSocketServer;
          class RPCSocketServerFactory;
          using casock::rpc::protobuf::server::RPCCallHandlerFactory;

          /*!
           * This is the workflow of an RPC request:
           *
           * 1) The RPCSocketServer asynchronously receives a client connection and
           *  creates an RPCSocketSession to treat it, i.e., to receive the requests.
           *
           * 2) The RPCSocketSession uses an RPCServerCommunicator to asynchronously
           *  read the raw data sent by the client and creates a ::google::protobuf::Message
           *  defined by the RPC API (casock::rpc::protobuf::api::RpcRequest).
           *
           * 3) The RPCSocketSession creates an RPCCall for each request received,
           *  set itself as the response handler and put them into the RPCCallQueue.
           *
           * 4) The RPCCallHandler is a thread that gets the RPCCalls from the queue,
           * calls the operations, creates the ::google::protobuf::Message response
           * and calls RPCCall::callback ().
           *
           * 5) The RPCCall::callback () calls the callback of its RPCResponseHandler
           *  (that is the same RPCSocketSession that received the request).
           *
           * 6) The RPCSocketSession::callback () sends the response to the client
           *  using the RPCServerCommunicator.
           */

          class RPCServerProxy : public casock::rpc::protobuf::server::RPCServerProxy
          {
            public:
              RPCServerProxy (const RPCSocketServerFactory& rSocketServerFactory, const RPCCallHandlerFactory& rCallHandlerFactory);
              virtual ~RPCServerProxy ();

            public:
              void start ();
              void stop ();
              void stopReceivingCalls ();

            private:
              RPCSocketServer*  mpSocketServer;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_
