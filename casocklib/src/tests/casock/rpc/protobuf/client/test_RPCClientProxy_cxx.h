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
 * \file tests/casock/rpc/protobuf/client/test_RPCClientProxy_cxx.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__TEST_RPC_CLIENT_PROXY_CXX_H_
#define __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__TEST_RPC_CLIENT_PROXY_CXX_H_

#include <cxxtest/TestSuite.h>

#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallHash.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"
#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "casock/util/Logger.h"

#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"
#include "tests/casock/rpc/protobuf/client/RPCClientProxyTest.h"
#include "tests/casock/rpc/protobuf/client/RPCCallHandlerFactoryMock.h"
#include "tests/casock/rpc/protobuf/client/RPCCallHandlerFactoryStub.h"
#include "tests/casock/rpc/protobuf/client/RPCResponseHandlerMock.h"

class test_RPCClientProxy_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { }

  public:
    void test_basic ()
    {
      tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryStub factory;
      tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);

      TS_ASSERT (proxy.mpCallHash->empty ());
      TS_ASSERT (proxy.mpCallQueue != NULL);
      TS_ASSERT (proxy.mpCallQueue->empty ());
      TS_ASSERT (proxy.mCallHandlers.empty ());
      TS_ASSERT_EQUALS (0, proxy.timeoutInSeconds ());
    }

    void test_addremoveCallHandlers ()
    {
      tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryMock factory;

      LOGMSG (LOW_LEVEL, "%s - construct proxy with 1 handler\n", __PRETTY_FUNCTION__);
      tests::casock::rpc::protobuf::client::RPCClientProxyTest* pProxy = new tests::casock::rpc::protobuf::client::RPCClientProxyTest (factory);
      pProxy->setNumCallHandlers (1);

      TS_ASSERT_EQUALS ((size_t) 1, factory.handlers.size ());

      LOGMSG (LOW_LEVEL, "%s - add 3 handlers\n", __PRETTY_FUNCTION__);
      pProxy->addCallHandlers (3);
      TS_ASSERT_EQUALS ((size_t) 4, factory.handlers.size ());

      LOGMSG (LOW_LEVEL, "%s - remove 4 handlers\n", __PRETTY_FUNCTION__);
      pProxy->removeCallHandlers (4);
      TS_ASSERT_EQUALS ((size_t) 0, factory.handlers.size ());

      pProxy->addCallHandlers (100);
      TS_ASSERT_EQUALS ((size_t) 100, factory.handlers.size ());

      delete pProxy;
      TS_ASSERT_EQUALS ((size_t) 0, factory.handlers.size ());
    }

    void test_setNumCallHandlers ()
    {

      tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryMock factory;
      tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);

      proxy.setNumCallHandlers (10);
      TS_ASSERT_EQUALS ((size_t) 10, factory.handlers.size ());

      proxy.setNumCallHandlers (100);
      TS_ASSERT_EQUALS ((size_t) 100, factory.handlers.size ());

      proxy.setNumCallHandlers (78);
      TS_ASSERT_EQUALS ((size_t) 78, factory.handlers.size ());

      proxy.setNumCallHandlers (0);
      TS_ASSERT_EQUALS ((size_t) 0, factory.handlers.size ());
    }

    void test_registerRPCCall ()
    {
      tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryStub factory;
      tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);
      
      casock::rpc::protobuf::client::RPCCall call (NULL, NULL, NULL);
      proxy.registerRPCCall (0, &call);
      TS_ASSERT (! proxy.mpCallHash->empty ());
      TS_ASSERT_EQUALS (&call, proxy.mpCallHash->pop (0));
      TS_ASSERT (proxy.mpCallHash->empty ());
    }

    void test_CallMethod ()
    {
      tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryStub factory;
      tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);
      tests::casock::rpc::protobuf::api::TestService* pService = new tests::casock::rpc::protobuf::api::TestService::Stub (&proxy);

      tests::casock::rpc::protobuf::api::TestRequest request;
      tests::casock::rpc::protobuf::api::TestResponse response;
      casock::rpc::protobuf::client::RPCCallController* controller = proxy.buildRPCCallController ();
      tests::casock::rpc::protobuf::client::RPCResponseHandlerMock handler;

      request.set_id (1);
      request.set_message (2);

      pService->TestCall (controller, &request, &response, handler.closure ());

      TS_ASSERT_EQUALS ((size_t) 1, proxy.requests.size ());

      TS_ASSERT_EQUALS ((uint32) 1, proxy.requests.front ().first.id ());
      TS_ASSERT_EQUALS ("TestCall", proxy.requests.front ().first.operation ());
      TS_ASSERT_EQUALS (request.SerializeAsString (), proxy.requests.front ().first.request ());

      TS_ASSERT_EQUALS (&response, proxy.requests.front ().second->response ());
      TS_ASSERT_EQUALS (controller, proxy.requests.front ().second->controller ());

      proxy.requests.front ().second->closure ()->Run ();
      TS_ASSERT_EQUALS (true, handler.called);

      delete controller;
    }
};

#endif // __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__TEST_RPC_CLIENT_PROXY_CXX_H_
