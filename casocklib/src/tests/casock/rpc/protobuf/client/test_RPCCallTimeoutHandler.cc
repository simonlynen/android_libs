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
 * \file tests/casock/rpc/protobuf/client/test_RPCCallTimeoutHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include <glog/logging.h>
#include <gflags/gflags.h>
#include <gtest/gtest.h>

#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallHash.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"
#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "casock/rpc/protobuf/client/RPCCallTimeoutHandler.h"

#include "tests/casock/rpc/protobuf/client/RPCCallHandlerFactoryStub.h"

class RPCCallTimeoutHandlerFixture : public ::testing::Test
{
  protected:
    casock::rpc::protobuf::client::RPCCallHash* pHash;
    casock::rpc::protobuf::client::RPCCallQueue* pQueue;
    casock::rpc::protobuf::client::RPCCallTimeoutHandler* pHandler;

    uint32 id;
    struct timeval timeout;

  protected:
    void SetUp ()
    {
      pHash = new casock::rpc::protobuf::client::RPCCallHash ();
      pQueue = new casock::rpc::protobuf::client::RPCCallQueue ();
      pHandler = new casock::rpc::protobuf::client::RPCCallTimeoutHandler (*pHash, *pQueue);
    }

    void TearDown ()
    {
      delete pHandler;
      delete pQueue;
      delete pHash;
    }

  protected:
    casock::rpc::protobuf::client::RPCCallController* buildController (const uint32& timeout_secs, const uint32& timeout_usecs)
    {
      timeout.tv_sec = timeout_secs;
      timeout.tv_usec = timeout_usecs;
      casock::rpc::protobuf::client::RPCCallController* pController = new casock::rpc::protobuf::client::RPCCallController();
      pController->setTimeout (timeout);

      return pController;
    }
};

TEST_F(RPCCallTimeoutHandlerFixture, Basic) {
  pHandler->start ();

  id = 1;
  casock::rpc::protobuf::client::RPCCallController* pController = buildController (0, 1);
  casock::rpc::protobuf::client::RPCCall call (NULL, pController, NULL);
  pHash->push (id, &call);

  pHandler->registerTimeout (id, pController->timeout ());
  usleep (pController->timeoutInUSeconds ());

  EXPECT_TRUE (pHash->empty ());
  EXPECT_EQ ((size_t) 1, pQueue->size ());
  EXPECT_TRUE (pController->Failed ());

  delete pController;
  pHandler->cancel ();
}

TEST_F(RPCCallTimeoutHandlerFixture, TwoCalls) {
  pHandler->start ();

  /*!
   * Creating the first call
   */
  id = 1;
  casock::rpc::protobuf::client::RPCCallController* pController1 = buildController (0, 200);
  casock::rpc::protobuf::client::RPCCall call1 (NULL, pController1, NULL);
  pHash->push (id, &call1);

  pHandler->registerTimeout (id, pController1->timeout ());

  /*!
   * Creating the second call
   */
  id = 2;
  casock::rpc::protobuf::client::RPCCallController* pController2 = buildController (0, 10);
  casock::rpc::protobuf::client::RPCCall call2 (NULL, pController2, NULL);
  pHash->push (id, &call2);

  pHandler->registerTimeout (id, pController2->timeout ());

  /*!
   * Waiting for the first timeout
   */
  usleep (10 * pController2->timeoutInUSeconds ());

  EXPECT_EQ ((size_t) 1, pHash->size ());
  EXPECT_EQ ((size_t) 1, pQueue->size ());
  EXPECT_TRUE (pController2->Failed ());

  /*!
   * Waiting for the second timeout
   */
  usleep (pController1->timeoutInUSeconds ());

  EXPECT_TRUE (pHash->empty ());
  EXPECT_EQ ((size_t) 2, pQueue->size ());
  EXPECT_TRUE (pController1->Failed ());

  delete pController1;
  pHandler->cancel ();
}

int main (int argc, char **argv) {
  google::InitGoogleLogging (argv[0]);
  google::ParseCommandLineFlags (&argc, &argv, true);
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}
