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
 * \file casock/rpc/asio/protobuf/client/RPCClientProxy.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_H_

#include <string>
#include <asio.hpp>
#include "casock/rpc/protobuf/client/RPCClientProxy.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcRequest;
      }

      namespace client {
        class RPCCallHandlerFactory;
      }
    }

    namespace asio {
      namespace protobuf {
        namespace client {
          class RPCSocketClient;
          class RPCSocketClientFactory;
          class RPCClientCommunicator;
          using casock::rpc::protobuf::client::RPCCallHandlerFactory;

          /*!
           * This is the workflow of an RPC request:
           *
           * 1) The user defines an RPC service and constructs it passing
           *  a RPCClientProxy as parameter (::gogole::protobuf::RpcChannel).
           *
           * 2) The client executes an operation of the service passing a
           *  controller and a closure for callback.
           *
           * 3) The google protobuf framework is responsible to call RPCClientProxy to
           * send the request to the server. RPCClientProxy creates an RPCCall, put it
           * on the call hash and executes the method RPCClientProxy::sendRpcRequest ().
           *
           * 4) The google protobuf framework is also used to send the request
           *  to the server. The TODO: RPCChannel is used to it.
           *
           * 5) The RPCClientCommunicator is used by TODO: RPCChannel to send the
           *  request to the server. The RPCSocketClient is used as the
           *  communication channel.
           *
           * 6) The RPCSocketClient asynchronously receives the responses
           * and put them into the RPCCallQueue.
           *
           * 7) The RPCCallHandler is a thread responsible to get the RPCCalls
           * from RPCCallQueue and call the RPCCall's closure.
           */

          class RPCClientProxy : public casock::rpc::protobuf::client::RPCClientProxy
          {
            public:
              RPCClientProxy (const RPCSocketClientFactory& rSocketClientFactory, const RPCCallHandlerFactory& rCallHandlerFactory);
              virtual ~RPCClientProxy ();

            private:
              /*!
               * This is our way to send the message to RPC server.
               * Because we implemented our own controllers, we don't need the
               * RPC service provided by Google Protocol Buffers. We only need
               * the messages and serializations.
               */
              void sendRpcRequest (const casock::rpc::protobuf::api::RpcRequest& request, casock::rpc::protobuf::client::RPCCall* pCall);

							void onSentRequest (const ::asio::error_code& error, const uint32 id, casock::rpc::protobuf::client::RPCCall* pCall);

            public:
              void close ();

            private:
              RPCSocketClient*        mpSocketClient;
              RPCClientCommunicator*  mpCommunicator;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_H_
