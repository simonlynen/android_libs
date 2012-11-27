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
 * \file tests/casock/rpc/protobuf/client/test_RPCClientProxy.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include <gtest/gtest.h>

#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCallHash.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"
#include "casock/rpc/protobuf/client/RPCCallController.h"

#include "tests/casock/rpc/protobuf/client/RPCCallHandlerFactoryStub.h"
#include "tests/casock/rpc/protobuf/client/RPCClientProxyTest.h"

class RPCClientProxyTestFixture : public ::testing::Test
{
  protected:
    tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryStub factory;
};

TEST_F(RPCClientProxyTestFixture, Basic) {
  tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);

  EXPECT_TRUE (proxy.mpCallHash->empty ());
  EXPECT_NE (static_cast<casock::rpc::protobuf::client::RPCCallQueue*>(NULL), proxy.mpCallQueue);
  EXPECT_TRUE (proxy.mpCallQueue->empty ());
  EXPECT_TRUE (proxy.mCallHandlers.empty ());
  EXPECT_EQ (0, proxy.timeoutInSeconds ());
  EXPECT_EQ (0, proxy.timeoutInUSeconds ());
}

TEST_F(RPCClientProxyTestFixture, Timeout) {
  tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);

  EXPECT_EQ (0, proxy.timeoutInSeconds ());
  EXPECT_EQ (0, proxy.timeoutInUSeconds ());

  proxy.setTimeoutInSeconds (1);

  EXPECT_EQ (1, proxy.timeoutInSeconds ());
  EXPECT_EQ (1000000, proxy.timeoutInUSeconds ());

  proxy.setTimeoutInUSeconds (2500000);

  EXPECT_EQ (2, proxy.timeoutInSeconds ());
  EXPECT_EQ (2500000, proxy.timeoutInUSeconds ());
}

TEST_F(RPCClientProxyTestFixture, TimeoutRPCCallController) {
  tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);

  casock::rpc::protobuf::client::RPCCallController* controller = proxy.buildRPCCallController ();

  EXPECT_EQ (proxy.timeoutInSeconds (), controller->timeoutInSeconds ());
  EXPECT_EQ (proxy.timeoutInUSeconds (), controller->timeoutInUSeconds ());

  delete controller;
  proxy.setTimeoutInUSeconds (3600000);
  controller = proxy.buildRPCCallController ();

  EXPECT_EQ (proxy.timeoutInSeconds (), controller->timeoutInSeconds ());
  EXPECT_EQ (proxy.timeoutInUSeconds (), controller->timeoutInUSeconds ());

  controller->setTimeoutInUSeconds (4800000);

  EXPECT_EQ (4, controller->timeoutInSeconds ());
  EXPECT_EQ (4800000, controller->timeoutInUSeconds ());
  EXPECT_EQ (3, proxy.timeoutInSeconds ());
  EXPECT_EQ (3600000, proxy.timeoutInUSeconds ());
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}
