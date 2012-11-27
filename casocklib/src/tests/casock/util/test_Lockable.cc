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
 * \file tests/casock/util/test_Lockable.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */
 
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "casock/util/Lockable.h"
#include "casock/util/Thread.h"
#include "casock/util/Logger.h"

using ::testing::Invoke;

class MockThread : public casock::util::Thread
{
  public:
    MOCK_METHOD0(run, void());
};

class LockableTestFixture : public ::testing::Test, public casock::util::Lockable
{
  protected:
    MockThread* pThread;

  protected:
    void SetUp ()
    {
      pThread = new MockThread ();
    }

    void TearDown ()
    {
      delete pThread;
    }

  protected:
    const struct timespec timeoutInTimespec (const struct timeval& timeout) const
    {
      struct timeval tv_now;
      struct timespec ts_timeout;

      gettimeofday (&tv_now, NULL);

      ts_timeout.tv_sec = (tv_now.tv_sec + timeout.tv_sec) + (tv_now.tv_usec + timeout.tv_usec) / 1000000;
      ts_timeout.tv_nsec = ((tv_now.tv_usec + timeout.tv_usec) % 1000000) * 1000;

      return ts_timeout;
    }
};


TEST_F(LockableTestFixture, Basic) {
  EXPECT_TRUE (tryLock ());
  unlock ();
}

TEST_F(LockableTestFixture, CondWaitTimeout) {
  struct timeval tv_ini;
  struct timeval tv_end;
  uint32 timeout = 1;

  gettimeofday (&tv_ini, NULL);
  cond_wait (timeout);
  gettimeofday (&tv_end, NULL);

  int diff = (tv_end.tv_sec - tv_ini.tv_sec) + (tv_end.tv_usec - tv_ini.tv_usec) / 1000000;

  EXPECT_EQ (1, diff);
}

TEST_F(LockableTestFixture, CondWaitTimeoutTimeval) {
  struct timeval tv_ini;
  struct timeval tv_end;
  struct timeval timeout;

  timeout.tv_sec = 0;
  timeout.tv_usec = 1000;

  gettimeofday (&tv_ini, NULL);
  cond_wait (timeout);
  gettimeofday (&tv_end, NULL);

  int diff = (tv_end.tv_sec - tv_ini.tv_sec) * 1000000 + (tv_end.tv_usec - tv_ini.tv_usec);

  EXPECT_LE (900, diff);
  EXPECT_GE (1100, diff);
}

TEST_F(LockableTestFixture, CondWaitTimeoutTimespec) {
  struct timeval tv_ini;
  struct timeval tv_end;
  struct timeval timeout;

  timeout.tv_sec = 0;
  timeout.tv_usec = 1000;

  gettimeofday (&tv_ini, NULL);
  cond_wait (timeoutInTimespec (timeout));
  gettimeofday (&tv_end, NULL);

  int diff = (tv_end.tv_sec - tv_ini.tv_sec) * 1000000 + (tv_end.tv_usec - tv_ini.tv_usec);

  EXPECT_LE (900, diff);
  EXPECT_GE (1100, diff);
}

ACTION_P2(run_CondWait, pLockable, usecs) {
  pLockable->lock ();
  pLockable->cond_wait ();
  usleep (usecs);
  pLockable->unlock ();
}

TEST_F(LockableTestFixture, ThreadCondWait) {
  EXPECT_CALL(*pThread, run()).WillOnce(run_CondWait(this, 2000));

  lock ();
  pThread->start ();
  unlock ();
  usleep (1000);

  EXPECT_TRUE (tryLock ());

  cond_signal ();
  unlock ();
  usleep (1000);

  EXPECT_FALSE (tryLock ());

  usleep (2000);

  EXPECT_TRUE (tryLock ());

  unlock ();
}

ACTION_P3(run_CondWaitTimeout, pLockable, secs, usecs) {
  pLockable->lock ();
  pLockable->cond_wait (secs);
  usleep (usecs);
  pLockable->unlock ();
}

TEST_F(LockableTestFixture, ThreadCondWaitTimeout) {
  EXPECT_CALL(*pThread, run()).WillOnce(run_CondWaitTimeout(this, 1, 1000000));

  lock ();
  pThread->start ();
  unlock ();
  usleep (500000);

  EXPECT_TRUE (tryLock ());

  unlock ();
  usleep (1000000);

  EXPECT_FALSE (tryLock ());

  usleep (1000000);

  EXPECT_TRUE (tryLock ());

  unlock ();
}

ACTION_P3(run_CondWaitTimeoutTimeval, pLockable, wait_timeout, sleep_usecs) {
  pLockable->lock ();
  pLockable->cond_wait (wait_timeout);
  usleep (sleep_usecs);
  pLockable->unlock ();
}

TEST_F(LockableTestFixture, ThreadCondWaitTimeoutTimeval) {
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 999999;
  EXPECT_CALL(*pThread, run()).WillOnce(run_CondWaitTimeoutTimeval(this, timeout, 1000000));

  lock ();
  pThread->start ();
  unlock ();
  usleep (500000);

  EXPECT_TRUE (tryLock ());

  unlock ();
  usleep (1000000);

  EXPECT_FALSE (tryLock ());

  usleep (1000000);

  EXPECT_TRUE (tryLock ());

  unlock ();
}

TEST_F(LockableTestFixture, ThreadCondWaitTimeoutTimespec) {
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 999999;
  EXPECT_CALL(*pThread, run()).WillOnce(run_CondWaitTimeoutTimeval(this, timeoutInTimespec (timeout), 1000000));

  lock ();
  pThread->start ();
  unlock ();
  usleep (500000);

  EXPECT_TRUE (tryLock ());

  unlock ();
  usleep (1000000);

  EXPECT_FALSE (tryLock ());

  usleep (1000000);

  EXPECT_TRUE (tryLock ());

  unlock ();
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}
