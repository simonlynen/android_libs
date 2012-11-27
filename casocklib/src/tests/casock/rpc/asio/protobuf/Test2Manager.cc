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
 * \file tests/casock/rpc/asio/protobuf/Test2Manager.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "tests/casock/rpc/asio/protobuf/Test2Manager.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace asio {
        namespace protobuf {
          uint32 Test2Manager::mID = 0;

          Test2Manager::CallEntry::CallEntry (
              const uint32& id,
              tests::casock::rpc::protobuf::api::TestRequest* request,
              tests::casock::rpc::protobuf::api::TestResponse* response,
              ::casock::rpc::protobuf::client::RPCCallController* controller,
              Test2ResponseHandlerImpl* handler)
            : mID (id), mpRequest (request), mpResponse (response), mpController (controller), mpHandler (handler)
          { }

          void Test2Manager::addCallEntry (
              const uint32& id,
              tests::casock::rpc::protobuf::api::TestRequest* request,
              tests::casock::rpc::protobuf::api::TestResponse* response,
              ::casock::rpc::protobuf::client::RPCCallController* controller,
              Test2ResponseHandlerImpl* handler)
          {
            ::casock::util::SafeLock lock (mCallEntryHash);
            mCallEntryHash [id] = new CallEntry (id, request, response, controller, handler);
          }

          void Test2Manager::setResponseReceivedByID (const uint32& id)
          {
            ::casock::util::SafeLock lockHash (mCallEntryHash);

            if (mCallEntryHash.find (id) != mCallEntryHash.end ())
            {
              CallEntry* pEntry = mCallEntryHash [id];
              mCallEntryHash.erase (id);

              ::casock::util::SafeLock lockRespHash (mCallEntryRespHash);
              mCallEntryRespHash [id] = pEntry;
            }
          }
        }
      }
    }
  }
}
