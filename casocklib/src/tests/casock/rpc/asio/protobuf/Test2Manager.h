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
 * \file tests/casock/rpc/asio/protobuf/Test2Manager.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_MANAGER_H_
#define __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_MANAGER_H_

#include "casock/util/Thread.h"
#include "casock/util/LockableHash.h"
#include "casock/util/SafeLock.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCCallController;
      }
    }
  }
}

namespace tests {
  namespace casock {
    namespace rpc {
      namespace protobuf {
        namespace api {
          class TestRequest;
          class TestResponse;
        }
      }

      namespace asio {
        namespace protobuf {
          class Test2ResponseHandlerImpl;

          class Test2Manager
          {
            private:
              class CallEntry
              {
                public:
                  CallEntry (
                      const uint32& id,
                      tests::casock::rpc::protobuf::api::TestRequest* request,
                      tests::casock::rpc::protobuf::api::TestResponse* response,
                      ::casock::rpc::protobuf::client::RPCCallController* controller,
                      Test2ResponseHandlerImpl* handler);

                private:
                  uint32 mID;
                  tests::casock::rpc::protobuf::api::TestRequest* mpRequest;
                  tests::casock::rpc::protobuf::api::TestResponse* mpResponse;
                  ::casock::rpc::protobuf::client::RPCCallController* mpController;
                  Test2ResponseHandlerImpl* mpHandler;
              };

            public:
              static uint32 getID () { return ++mID; }

            public:
              void addCallEntry (
                  const uint32& id,
                  tests::casock::rpc::protobuf::api::TestRequest* request,
                  tests::casock::rpc::protobuf::api::TestResponse* response,
                  ::casock::rpc::protobuf::client::RPCCallController* controller,
                  Test2ResponseHandlerImpl* handler);

              void setResponseReceivedByID (const uint32& id);


              const ::casock::util::LockableHash<uint32, CallEntry*>& getCallEntryHash () const { return mCallEntryHash; }
              const ::casock::util::LockableHash<uint32, CallEntry*>& getCallEntryRespHash () const { return mCallEntryRespHash; }

            private:
              static uint32 mID;
              ::casock::util::LockableHash<uint32, CallEntry*> mCallEntryHash;
              ::casock::util::LockableHash<uint32, CallEntry*> mCallEntryRespHash;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_MANAGER_H_
