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
 * \file tests/casock/rpc/asio/protobuf/Test2ResponseHandlerImpl.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "tests/casock/rpc/asio/protobuf/Test2ResponseHandlerImpl.h"

#include "casock/util/Logger.h"
#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"
#include "tests/casock/rpc/asio/protobuf/Test2Manager.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace asio {
        namespace protobuf {
          Test2ResponseHandlerImpl::Test2ResponseHandlerImpl (::casock::rpc::protobuf::client::RPCCallController* pController, tests::casock::rpc::protobuf::api::TestResponse* pResponse, Test2Manager* pManager)
            : mpController (pController), mpResponse (pResponse), mpManager (pManager)
          { }

          void Test2ResponseHandlerImpl::callback ()
          {
            LOGMSG (NO_DEBUG, "Test2ResponseHandlerImpl::%s ()\n", __FUNCTION__);

            if (! mpController->Failed ())
            {
              LOGMSG (NO_DEBUG, "Test2ResponseHandlerImpl::%s () - message [%u]\n", __FUNCTION__, mpResponse->message ());
              mpManager->setResponseReceivedByID (mpResponse->id ());
            }
          }
        }
      }
    }
  }
}
