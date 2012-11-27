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
 * \file tests/casock/rpc/protobuf/base/RPCProxyTest.h
 * \brief Defines test-specific subclass for casock::rpc::protobuf::base::RPCProxy
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_PROTOBUF_BASE__RPC_PROXY_TEST_H_
#define __CASOCKLIB__TESTS_RPC_PROTOBUF_BASE__RPC_PROXY_TEST_H_

#include "casock/rpc/protobuf/base/RPCProxy.h"
#include "casock/util/Thread.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace protobuf {
        namespace base {
          /*!
           * \class RPCProxyTest
           * \brief A test-specific subclass for casock::rpc::protobuf::base::RPCProxy
           * \author Leandro Costa
           * \date 2010
           *
           * A class created just to define the \b buildCallHandler method of its superclass.
           * The test-specific subclass is a pattern found in http://xunitpatterns.com.
           */

          class RPCProxyTest : public ::casock::rpc::protobuf::base::RPCProxy
          {
            private:
              class CallHandlerStub : public ::casock::util::Thread
            {
              public:
                void run () { }
            };

            private:
              ::casock::util::Thread* buildCallHandler ()
              {
                return new CallHandlerStub ();
              }

            public:
              using ::casock::rpc::protobuf::base::RPCProxy::mCallHandlers;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_PROTOBUF_BASE__RPC_PROXY_TEST_H_
