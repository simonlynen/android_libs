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
 * \file tests/casock/rpc/asio/protobuf/test1_cxx.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */


#ifndef __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_CXX_H_
#define __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_CXX_H_

#include <cxxtest/TestSuite.h>

#include "casock/proactor/asio/base/AsyncProcessor.h"

#include "casock/rpc/protobuf/client/RPCCallHandlerFactoryImpl.h"
#include "casock/rpc/protobuf/server/RPCCallHandlerFactoryImpl.h"

#include "casock/rpc/asio/protobuf/client/RPCClientProxy.h"
#include "casock/rpc/asio/protobuf/client/RPCSocketClientFactoryImpl.h"
#include "casock/rpc/asio/protobuf/server/RPCServerProxy.h"
#include "casock/rpc/asio/protobuf/server/RPCSocketServerFactoryImpl.h"

#include "tests/casock/rpc/asio/protobuf/Test1ServiceImpl.h"
#include "tests/casock/rpc/asio/protobuf/Test1ResponseHandlerImpl.h"
#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"
#include "casock/util/Logger.h"

class test1_cxx : public CxxTest::TestSuite
{
  private:
    tests::casock::rpc::asio::protobuf::Test1ServiceImpl mServiceServer;
    ::casock::proactor::asio::base::AsyncProcessor* mpAsyncProcessor;

  public:
    void setUp ()
    {
      LOGMSG (LOW_LEVEL, "test1_cxx::setUp ()\n");
      LOGGER->setDebugLevel (SILENT);
      ::casock::proactor::asio::base::AsyncProcessor::initialize ();
      mpAsyncProcessor = ::casock::proactor::asio::base::AsyncProcessor::getInstance ();
    }

    void tearDown ()
    {
      LOGMSG (LOW_LEVEL, "test1_cxx::tearDown ()\n");
      ::casock::proactor::asio::base::AsyncProcessor::destroy ();
      LOGGER->finalize ();
    }

  public:
    void test_basic ()
    {
      //try
      //{
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
        //casock::rpc::asio::protobuf::client::RPCClientProxy clientProxy (*mpAsyncProcessor, "localhost", "2000");
        ::casock::rpc::asio::protobuf::client::RPCClientProxy clientProxy (clientSocketFactory, callHandlerFactory);
        clientProxy.setNumCallHandlers (1);
        tests::casock::rpc::protobuf::api::TestService* pServiceClient = new tests::casock::rpc::protobuf::api::TestService::Stub (&clientProxy);

        /*! sending message */
        tests::casock::rpc::protobuf::api::TestRequest* request = new tests::casock::rpc::protobuf::api::TestRequest ();
        tests::casock::rpc::protobuf::api::TestResponse* response = new tests::casock::rpc::protobuf::api::TestResponse ();
        ::casock::rpc::protobuf::client::RPCCallController* controller = clientProxy.buildRPCCallController ();

        request->set_id (1);
        request->set_message (2);
        tests::casock::rpc::asio::protobuf::Test1ResponseHandlerImpl handler (controller, response);
        handler.setProxy (&clientProxy);
        pServiceClient->TestCall (controller, request, response, handler.closure ());

        /*! running async processor */
        mpAsyncProcessor->run ();

        TS_ASSERT_EQUALS (request->id (), response->id ());
        TS_ASSERT_EQUALS (request->message (), response->message ());
      //}
      //catch (::std::exception& e)
      //{
      //  LOGMSG (LOW_LEVEL, "test_basic () - catch (::std::exception&) [%s]\n", e.what ());
      //  TS_FAIL (::std::string ("::std::exception [") + e.what () + "]");
      //}
      //
      LOGMSG (LOW_LEVEL, "%s - end\n", __PRETTY_FUNCTION__);
    }
};

#endif // __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST1_CXX_H_
