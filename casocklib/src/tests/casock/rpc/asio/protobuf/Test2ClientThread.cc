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
 * \file tests/casock/rpc/asio/protobuf/Test2ClientThread.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "tests/casock/rpc/asio/protobuf/Test2ClientThread.h"

#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "casock/rpc/asio/protobuf/client/RPCClientProxy.h"
#include "tests/casock/rpc/asio/protobuf/Test2Manager.h"
#include "tests/casock/rpc/asio/protobuf/Test2ResponseHandlerImpl.h"
#include "tests/casock/rpc/asio/protobuf/Test2ShutdownResponseHandlerImpl.h"
#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace asio {
        namespace protobuf {
          Test2ClientThread::Test2ClientThread ()
            : mNumCalls (0)
          { }

          void Test2ClientThread::run ()
          {
            for (uint32 i = 0; i < mNumCalls; i++)
            {
              uint32 id = Test2Manager::getID ();

              tests::casock::rpc::protobuf::api::TestRequest* request = new tests::casock::rpc::protobuf::api::TestRequest ();
              tests::casock::rpc::protobuf::api::TestResponse* response = new tests::casock::rpc::protobuf::api::TestResponse ();
              ::casock::rpc::protobuf::client::RPCCallController* controller = mpProxy->buildRPCCallController ();
              tests::casock::rpc::asio::protobuf::Test2ResponseHandlerImpl* handler = new tests::casock::rpc::asio::protobuf::Test2ResponseHandlerImpl (controller, response, mpManager);

              request->set_id (id);
              request->set_message (id * id);
              mpService->TestCall (controller, request, response, handler->closure ());

              mpManager->addCallEntry (id, request, response, controller, handler);
            }

            uint32 id = Test2Manager::getID ();

            tests::casock::rpc::protobuf::api::TestRequest* request = new tests::casock::rpc::protobuf::api::TestRequest ();
            tests::casock::rpc::protobuf::api::TestResponse* response = new tests::casock::rpc::protobuf::api::TestResponse ();
            ::casock::rpc::protobuf::client::RPCCallController* controller = mpProxy->buildRPCCallController ();
            tests::casock::rpc::asio::protobuf::Test2ShutdownResponseHandlerImpl* handler = new tests::casock::rpc::asio::protobuf::Test2ShutdownResponseHandlerImpl (controller, response, mpManager, mpProxy);

            request->set_id (id);
            request->set_message (id * id);
            mpService->TestShutdown (controller, request, response, handler->closure ());
          }
        }
      }
    }
  }
}
