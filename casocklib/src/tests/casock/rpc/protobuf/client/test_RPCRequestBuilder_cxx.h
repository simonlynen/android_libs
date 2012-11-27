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
 * \file tests/casock/rpc/protobuf/client/test_RPCRequestBuilder_cxx.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__TEST_RPC_REQUEST_BUILDER_CXX_H_
#define __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__TEST_RPC_REQUEST_BUILDER_CXX_H_

#include <map>
#include <vector>
#include <cxxtest/TestSuite.h>
#include <google/protobuf/descriptor.h>

#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCRequestBuilder.h"
#include "casock/util/Thread.h"

#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"
#include "tests/casock/rpc/protobuf/client/RPCCallHandlerFactoryStub.h"
#include "tests/casock/rpc/protobuf/client/RPCClientProxyStub.h"


class test_RPCRequestBuilder_cxx : public CxxTest::TestSuite
{
  class RPCRequestBuilderTesterThread : public ::casock::util::Thread
  {
    public:
      RPCRequestBuilderTesterThread (
          tests::casock::rpc::protobuf::api::TestService& service,
          tests::casock::rpc::protobuf::api::TestRequest& request,
          ::casock::rpc::protobuf::client::RPCRequestBuilder& builder,
          std::vector< ::casock::rpc::protobuf::api::RpcRequest*>& rpcRequests,
          uint32 numRuns)
        : m_service (service), m_request (request), m_builder (builder), m_rpcRequests (rpcRequests), m_numRuns (numRuns)
      { };

      void run ()
      {
        for (uint32 i = 0; i < m_numRuns; i++)
        {
          m_rpcRequests.push_back (m_builder.buildRpcRequest (m_service.GetDescriptor ()->FindMethodByName ("TestCall"), &m_request));
        }
      }

    public:
      tests::casock::rpc::protobuf::api::TestService& m_service;
      tests::casock::rpc::protobuf::api::TestRequest& m_request;
      ::casock::rpc::protobuf::client::RPCRequestBuilder& m_builder;
      std::vector< ::casock::rpc::protobuf::api::RpcRequest*>& m_rpcRequests;
      uint32 m_numRuns;
  };

  public:
    void setUp () { }
    void tearDown () { }

  public:
    void test_basic ()
    {
      tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryStub factory;
      tests::casock::rpc::protobuf::client::RPCClientProxyStub proxy (factory);
      tests::casock::rpc::protobuf::api::TestService* pService = new tests::casock::rpc::protobuf::api::TestService::Stub (&proxy);
      tests::casock::rpc::protobuf::api::TestRequest request;

      request.set_id (1);
      request.set_message (1);

      ::casock::rpc::protobuf::client::RPCRequestBuilder builder;
      ::casock::rpc::protobuf::api::RpcRequest* pRpcRequest = builder.buildRpcRequest (pService->GetDescriptor ()->FindMethodByName ("TestCall"), &request);

      TS_ASSERT_EQUALS ((uint32) 1, pRpcRequest->id ());
      TS_ASSERT_EQUALS ("TestCall", pRpcRequest->operation ());
      TS_ASSERT_EQUALS (request.SerializeAsString (), pRpcRequest->request ());
    }

    void test_concurrent ()
    {
      uint32 numThreads = 10;
      uint32 numRequestsByThread = 1000;
      std::string methodName = "TestCall";

      tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryStub factory;
      tests::casock::rpc::protobuf::client::RPCClientProxyStub proxy (factory);
      tests::casock::rpc::protobuf::api::TestService* pService = new tests::casock::rpc::protobuf::api::TestService::Stub (&proxy);
      tests::casock::rpc::protobuf::api::TestRequest request;

      request.set_id (1);
      request.set_message (1);

      ::casock::rpc::protobuf::client::RPCRequestBuilder builder;
      std::map<uint32, std::vector< ::casock::rpc::protobuf::api::RpcRequest*> > rpcRequestsMap;

      for (uint32 i = 0; i < numThreads; i++)
      {
        rpcRequestsMap [i] = std::vector< ::casock::rpc::protobuf::api::RpcRequest*> ();
        RPCRequestBuilderTesterThread* pTester = new RPCRequestBuilderTesterThread (*pService, request, builder, rpcRequestsMap [i], numRequestsByThread);
        pTester->run ();
      }

      sleep (1);

      TS_ASSERT_EQUALS ((size_t) numThreads, rpcRequestsMap.size ());

      uint32 id = 0;

      for (uint32 i = 0; i < numThreads; i++)
      {
        TS_ASSERT_EQUALS ((size_t) numRequestsByThread, rpcRequestsMap [i].size ());

        std::vector< ::casock::rpc::protobuf::api::RpcRequest*>& rpcRequests = rpcRequestsMap [i];

        for (uint32 j = 0; j < numRequestsByThread; j++)
        {
          TS_ASSERT_EQUALS (++id, rpcRequests.at (j)->id ());
          TS_ASSERT_EQUALS (methodName, rpcRequests[j]->operation ());
          TS_ASSERT_EQUALS (request.SerializeAsString (), rpcRequests[j]->request ());
        }
      }

      TS_ASSERT_EQUALS (numThreads * numRequestsByThread, id);
    }
};

#endif // __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__TEST_RPC_REQUEST_BUILDER_CXX_H_
