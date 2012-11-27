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
 * \file tests/casock/rpc/protobuf/client/test_RPCCallResponseReceiver.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include <gtest/gtest.h>
#include <glog/logging.h>
#include <gflags/gflags.h>

#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallHash.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"
#include "casock/rpc/protobuf/client/RPCCallResponseReceiver.h"
#include "casock/rpc/protobuf/client/RPCRequestBuilder.h"

#include "tests/casock/rpc/protobuf/api/rpc_test.pb.h"

class RPCCallResponseReceiverFixture : public ::testing::Test
{
  protected:
    casock::rpc::protobuf::client::RPCCallHash* pHash;
    casock::rpc::protobuf::client::RPCCallQueue* pQueue;

  protected:
    void SetUp ()
    {
      pHash = new casock::rpc::protobuf::client::RPCCallHash ();
      pQueue = new casock::rpc::protobuf::client::RPCCallQueue ();
    }

    void TearDown ()
    {
      delete pQueue;
      delete pHash;
    }
};

TEST_F(RPCCallResponseReceiverFixture, Basic) {
  casock::rpc::protobuf::client::RPCCallResponseReceiver receiver (*pHash, *pQueue);

  tests::casock::rpc::protobuf::api::TestRequest request;

  request.set_id (1);
  request.set_message (1);
  const std::string operation = "Operation";

  ::casock::rpc::protobuf::client::RPCRequestBuilder builder;
  ::casock::rpc::protobuf::api::RpcRequest* pRpcRequest = builder.buildRpcRequest (operation, &request);

  ::casock::rpc::protobuf::client::RPCCall* pCall = new ::casock::rpc::protobuf::client::RPCCall (NULL, NULL, NULL);
  pHash->push (pRpcRequest->id (), pCall);

  EXPECT_EQ (1, pHash->size ());
  EXPECT_TRUE (pQueue->empty ());

  ::casock::rpc::protobuf::api::RpcResponse* pRpcResponse = new ::casock::rpc::protobuf::api::RpcResponse ();

  pRpcResponse->set_id (request.id ());

  receiver.handle (pRpcResponse);

  EXPECT_TRUE (pHash->empty ());
  EXPECT_EQ (1, pQueue->size ());
}

int main (int argc, char **argv) {
  google::InitGoogleLogging (argv[0]);
  google::ParseCommandLineFlags (&argc, &argv, true);
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}
