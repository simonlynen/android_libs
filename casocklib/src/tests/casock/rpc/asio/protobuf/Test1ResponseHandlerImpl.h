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
 * \file tests/casock/rpc/asio/protobuf/Test1ResponseHandlerImpl.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_RESPONSE_HANDLER_IMPL_H_
#define __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_RESPONSE_HANDLER_IMPL_H_

#include "casock/rpc/asio/protobuf/client/RPCClientProxy.h"
#include "casock/rpc/protobuf/client/RPCResponseHandler.h"
#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"
#include "casock/util/Logger.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace asio {
        namespace protobuf {
          class Test1ResponseHandlerImpl : public ::casock::rpc::protobuf::client::RPCResponseHandler
          {
            public:
              Test1ResponseHandlerImpl (::casock::rpc::protobuf::client::RPCCallController* pController, tests::casock::rpc::protobuf::api::TestResponse* pResponse)
                : mpController (pController), mpResponse (pResponse)
              { }

            public:
              void setProxy (::casock::rpc::asio::protobuf::client::RPCClientProxy* pClientProxy)
              {
                mpClientProxy = pClientProxy;
              }

            public:
              void callback ()
              {
                LOGMSG (NO_DEBUG, "Test1ResponseHandlerImpl::%s ()\n", __FUNCTION__);

                if (! mpController->Failed ())
                  LOGMSG (NO_DEBUG, "Test1ResponseHandlerImpl::%s () - message [%u]\n", __FUNCTION__, mpResponse->message ());

                try
                {
                  LOGMSG (NO_DEBUG, "Test1ResponseHandlerImpl::%s () - close proxy\n", __FUNCTION__);
                  mpClientProxy->close ();
                }
                catch (::std::exception& e)
                {
                  LOGMSG (NO_DEBUG, "Test1ResponseHandlerImpl::%s () - catch (::std::exception&) [%s]\n", __FUNCTION__, e.what ());
                  throw e;
                }
              }

            private:
              ::casock::rpc::asio::protobuf::client::RPCClientProxy* mpClientProxy;
              ::casock::rpc::protobuf::client::RPCCallController* mpController;
              tests::casock::rpc::protobuf::api::TestResponse* mpResponse;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_RESPONSE_HANDLER_IMPL_H_
