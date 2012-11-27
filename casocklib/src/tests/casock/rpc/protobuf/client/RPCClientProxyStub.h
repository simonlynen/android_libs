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
 * \file tests/casock/rpc/protobuf/client/RPCCallHandlerMock.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_STUB_H_
#define __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_STUB_H_

#include "casock/rpc/protobuf/client/RPCClientProxy.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace protobuf {
        namespace client {
          class RPCClientProxyStub : public ::casock::rpc::protobuf::client::RPCClientProxy
          {
            public:
              RPCClientProxyStub (const ::casock::rpc::protobuf::client::RPCCallHandlerFactory& factory)
                : ::casock::rpc::protobuf::client::RPCClientProxy (factory)
              { }

            private:
              void sendRpcRequest (const ::casock::rpc::protobuf::api::RpcRequest& request, ::casock::rpc::protobuf::client::RPCCall* pRPCCall)
              { }
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_STUB_H_
