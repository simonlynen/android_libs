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
 * \file tests/casock/rpc/asio/protobuf/test2_cxx.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */


#ifndef __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_CXX_H_
#define __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_CXX_H_

#include <cxxtest/TestSuite.h>

#include "casock/proactor/asio/base/AsyncProcessor.h"

#include "casock/rpc/protobuf/client/RPCCallHandlerFactoryImpl.h"
#include "casock/rpc/protobuf/server/RPCCallHandlerFactoryImpl.h"

#include "casock/rpc/asio/protobuf/client/RPCClientProxy.h"
#include "casock/rpc/asio/protobuf/client/RPCSocketClientFactoryImpl.h"
#include "casock/rpc/asio/protobuf/server/RPCServerProxy.h"
#include "casock/rpc/asio/protobuf/server/RPCSocketServerFactoryImpl.h"

#include "tests/casock/rpc/asio/protobuf/Test2ServiceImpl.h"
#include "tests/casock/rpc/asio/protobuf/Test2Manager.h"
#include "tests/casock/rpc/asio/protobuf/Test2ClientThread.h"
#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"
#include "casock/util/Logger.h"

class test2_cxx : public CxxTest::TestSuite
{
  private:
    tests::casock::rpc::asio::protobuf::Test2Manager      mManager;
    tests::casock::rpc::asio::protobuf::Test2ServiceImpl  mServiceServer;
    tests::casock::rpc::asio::protobuf::Test2ClientThread mClientThread;
    ::casock::proactor::asio::base::AsyncProcessor* mpAsyncProcessor;

  public:
    void setUp ()
    {
      LOGGER->setDebugLevel (SILENT);
      ::casock::proactor::asio::base::AsyncProcessor::initialize ();
      mpAsyncProcessor = ::casock::proactor::asio::base::AsyncProcessor::getInstance ();
    }

    void tearDown ()
    {
      ::casock::proactor::asio::base::AsyncProcessor::destroy ();
      LOGGER->finalize ();
    }

  public:
    void test_basic ()
    {
      size_t numCalls = 10;

      /*! server */
      ::casock::rpc::protobuf::server::RPCCallHandlerFactoryImpl callHandlerFactoryServer (&mServiceServer);
      ::casock::rpc::asio::protobuf::server::RPCSocketServerFactoryImpl socketServerFactory (*mpAsyncProcessor, 2000);
      ::casock::rpc::asio::protobuf::server::RPCServerProxy serverProxy (socketServerFactory, callHandlerFactoryServer);
      serverProxy.setNumCallHandlers (1);
      mServiceServer.setProxy (&serverProxy);
      serverProxy.start ();

      /*! client */
      ::casock::rpc::asio::protobuf::client::RPCSocketClientFactoryImpl clientSocketFactory (*mpAsyncProcessor, "localhost", "2000");
      ::casock::rpc::protobuf::client::RPCCallHandlerFactoryImpl callHandlerFactory;
      ::casock::rpc::asio::protobuf::client::RPCClientProxy clientProxy (clientSocketFactory, callHandlerFactory);
      clientProxy.setNumCallHandlers (1);
      tests::casock::rpc::protobuf::api::TestService* pServiceClient = new tests::casock::rpc::protobuf::api::TestService::Stub (&clientProxy);

      /*! running client thread */
      mClientThread.setNumCalls (numCalls);
      mClientThread.setService (pServiceClient);
      mClientThread.setManager (&mManager);
      mClientThread.setProxy (&clientProxy);
      mClientThread.start ();

      /*! running async processor */
      mpAsyncProcessor->run ();

      TS_ASSERT (mManager.getCallEntryHash ().empty ());
      TS_ASSERT_EQUALS (mManager.getCallEntryRespHash ().size (), static_cast<size_t> (numCalls));
    }
};

#endif // __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_CXX_H_
