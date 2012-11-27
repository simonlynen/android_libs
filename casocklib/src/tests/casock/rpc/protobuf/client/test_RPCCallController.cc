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
 * \file tests/casock/rpc/protobuf/client/test_RPCCallController.cc
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
#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "tests/casock/rpc/protobuf/client/RPCCallHandlerFactoryStub.h"
#include "tests/casock/rpc/protobuf/client/RPCClientProxyTest.h"

TEST(casock_rpc_protobuf_client_RPCCallController, Timeout) {
  tests::casock::rpc::protobuf::client::RPCCallHandlerFactoryStub factory;
  tests::casock::rpc::protobuf::client::RPCClientProxyTest proxy (factory);
  casock::rpc::protobuf::client::RPCCallController* controller = proxy.buildRPCCallController ();

  EXPECT_EQ (0, controller->timeoutInSeconds ());
  EXPECT_EQ (0, controller->timeoutInUSeconds ());

  controller->setTimeoutInSeconds (1);

  EXPECT_EQ (1, controller->timeoutInSeconds ());
  EXPECT_EQ (1000000, controller->timeoutInUSeconds ());

  controller->setTimeoutInUSeconds (2500000);

  EXPECT_EQ (2, controller->timeoutInSeconds ());
  EXPECT_EQ (2500000, controller->timeoutInUSeconds ());

  delete controller;
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}
