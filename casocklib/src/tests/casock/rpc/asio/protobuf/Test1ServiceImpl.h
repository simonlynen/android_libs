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
 * \file tests/casock/rpc/asio/protobuf/Test1ServiceImpl.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_SERVICE_IMPL_H_
#define __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_SERVICE_IMPL_H_

#include "casock/rpc/asio/protobuf/server/RPCServerProxy.h"
#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"
#include "casock/util/Logger.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace asio {
        namespace protobuf {
          class Test1ServiceImpl : public tests::casock::rpc::protobuf::api::TestService
          {
            public:
              void setProxy (::casock::rpc::asio::protobuf::server::RPCServerProxy* pServerProxy)
              {
                mpServerProxy = pServerProxy;
              }

            public:
              void TestCall(::google::protobuf::RpcController* controller,
                  const tests::casock::rpc::protobuf::api::TestRequest* request,
                  tests::casock::rpc::protobuf::api::TestResponse* response,
                  ::google::protobuf::Closure* done)
              {
                LOGMSG (LOW_LEVEL, "Test1ServiceImpl::%s () - request->message () [%u]\n", __FUNCTION__, request->message ());

                response->set_id (request->id ());
                response->set_message (request->message ());
                done->Run ();

                mpServerProxy->stopReceivingCalls ();
              }

            private:
              ::casock::rpc::asio::protobuf::server::RPCServerProxy* mpServerProxy;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_SERVICE_IMPL_H_
