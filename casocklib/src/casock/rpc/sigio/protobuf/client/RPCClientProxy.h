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
 * \file casock/rpc/sigio/protobuf/client/RPCClientProxy.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_H_
#define __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_H_

#include <string>
#include "casock/rpc/protobuf/client/RPCClientProxy.h"

namespace casock {
  namespace sigio {
    namespace base {
      class Dispatcher;
    }

    namespace client {
      class SocketClient;
    }
  }

  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcRequest;
      }

      namespace client {
        class RPCCall;
      }
    }

    namespace sigio {
      namespace protobuf {
        namespace client {
          class RPCReaderHandler;
          using casock::sigio::client::SocketClient;
          using casock::rpc::protobuf::client::RPCCallHandlerFactory;

          class RPCClientProxy : public casock::rpc::protobuf::client::RPCClientProxy
          {
            public:
              RPCClientProxy (casock::sigio::base::Dispatcher& rDispatcher, const std::string& host, const unsigned int& port, const RPCCallHandlerFactory& rCallHandlerFactory);

            private:
              void sendRpcRequest (const casock::rpc::protobuf::api::RpcRequest& request, casock::rpc::protobuf::client::RPCCall* pCall);

            private:
              SocketClient*     mpSocketClient; /*!< the client socket used to connect into RPC server socket */
              RPCReaderHandler* mpReaderHandler; /*!< responsable for asynchronously receive responses from RPC server */
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_H_
