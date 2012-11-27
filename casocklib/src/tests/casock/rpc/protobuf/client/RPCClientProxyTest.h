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
 * \file tests/casock/rpc/protobuf/client/RPCClientProxyTest.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_TEST_H_
#define __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_TEST_H_

#include <list>

#include "casock/rpc/protobuf/client/RPCClientProxy.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcRequest;
      }
    }
  }
}

namespace tests {
  namespace casock {
    namespace rpc {
      namespace protobuf {
        namespace client {
          using ::casock::rpc::protobuf::api::RpcRequest;
          using ::casock::rpc::protobuf::client::RPCCall;

          class RPCClientProxyTest : public ::casock::rpc::protobuf::client::RPCClientProxy
          {
            public:
              RPCClientProxyTest (const ::casock::rpc::protobuf::client::RPCCallHandlerFactory& factory)
                : ::casock::rpc::protobuf::client::RPCClientProxy (factory)
              { }

            private:
              void sendRpcRequest (const ::casock::rpc::protobuf::api::RpcRequest& request, ::casock::rpc::protobuf::client::RPCCall* pRPCCall)
              {
                requests.push_back (std::pair<RpcRequest, RPCCall*> (request, pRPCCall));
              }

            public:
              using ::casock::rpc::protobuf::client::RPCClientProxy::registerRPCCall;
              using ::casock::rpc::protobuf::client::RPCClientProxy::addCallHandlers;
              using ::casock::rpc::protobuf::client::RPCClientProxy::removeCallHandlers;

            public:
              using ::casock::rpc::protobuf::client::RPCClientProxy::mpCallHash;
              using ::casock::rpc::protobuf::client::RPCClientProxy::mpCallQueue;
              using ::casock::rpc::protobuf::client::RPCClientProxy::mCallHandlers;

            public:
              std::list<std::pair<RpcRequest, RPCCall*> > requests;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CLIENT_PROXY_TEST_H_
