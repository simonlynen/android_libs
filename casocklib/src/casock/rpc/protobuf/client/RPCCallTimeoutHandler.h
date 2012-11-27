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
 * \file casock/rpc/protobuf/client/RPCCallTimeoutHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_TIMEOUT_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_TIMEOUT_HANDLER_H_

#include <queue>
#include <map>

#include <glog/logging.h>

#include "casock/util/Thread.h"
#include "casock/util/Lockable.h"
#include "casock/util/SafeLock.h"
#include "casock/rpc/protobuf/client/RPCCall.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCCallHash;
        class RPCCallQueue;

        class RPCCallTimeoutHandler : public casock::util::Thread, private casock::util::Lockable
        {
          private:
            class entry : private std::pair<uint32, struct timespec>
            {
              public:
                entry (const uint32& id, const struct timeval& timeout)
                {
                  first = id;

                  struct timeval tv_now;
                  gettimeofday (&tv_now, NULL);

                  second.tv_sec = (tv_now.tv_sec + timeout.tv_sec) + (tv_now.tv_usec + timeout.tv_usec) / 1000000;
                  second.tv_nsec = ((tv_now.tv_usec + timeout.tv_usec) % 1000000) * 1000;
                }

              public:
                const bool operator>(const entry& other) const
                {
                  return (
                      (second.tv_sec > other.second.tv_sec) ||
                      (second.tv_sec == other.second.tv_sec && second.tv_nsec > other.second.tv_nsec));
                }

                const bool operator==(const entry& other) const
                {
                  return (first != other.first);
                }

                const bool operator!=(const entry& other) const
                {
                  return !(*this == other);
                }

              public:
                const bool isTimedOut () const
                {
                  bool bRet = false;

                  struct timeval tv_now;
                  gettimeofday (&tv_now, NULL);

                  bRet = (
                      (tv_now.tv_sec > timeout ().tv_sec) ||
                      (tv_now.tv_sec == timeout ().tv_sec && tv_now.tv_usec * 1000 >= timeout ().tv_nsec));

                  return bRet;
                }

              public:
                const uint32& id () const { return first; }
                const struct timespec& timeout () const { return second; }
            };

          public:
            RPCCallTimeoutHandler (RPCCallHash& rCallHash, RPCCallQueue& rCallQueue);

          public:
            void run ();

          private:
            void verifyEntries ();
            void handleTimedOutEntry (const entry& e);

          public:
            void registerTimeout (const uint32& id, const struct timeval& timeout);

          private:
            RPCCallHash& mrCallHash;
            RPCCallQueue& mrCallQueue;
            std::priority_queue<entry, std::vector<entry>, std::greater<std::vector<entry>::value_type> > mEntries;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_TIMEOUT_HANDLER_H_
