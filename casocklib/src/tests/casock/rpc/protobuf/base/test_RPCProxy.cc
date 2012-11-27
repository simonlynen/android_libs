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
 * \file tests/casock/rpc/protobuf/base/test_RPCProxy.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include <gtest/gtest.h>
#include "tests/casock/rpc/protobuf/base/RPCProxyTest.h"

TEST(casock_rpc_protobuf_base_RPCProxy, Basic) {
  tests::casock::rpc::protobuf::base::RPCProxyTest proxy;
  EXPECT_TRUE(proxy.mCallHandlers.empty ());

  proxy.addCallHandlers (5);
  EXPECT_EQ(5, proxy.mCallHandlers.size ());

  proxy.removeCallHandlers (2);
  EXPECT_EQ(3, proxy.mCallHandlers.size ());

  proxy.setNumCallHandlers (10);
  EXPECT_EQ(10, proxy.mCallHandlers.size ());

  proxy.setNumCallHandlers (0);
  EXPECT_TRUE(proxy.mCallHandlers.empty ());
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}
