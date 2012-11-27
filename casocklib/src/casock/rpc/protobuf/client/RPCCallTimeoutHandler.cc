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
 * \file casock/rpc/protobuf/client/RPCCallTimeoutHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/client/RPCCallTimeoutHandler.h"

#include <google/protobuf/service.h>

#include "casock/util/SafeLock.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallHash.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        RPCCallTimeoutHandler::RPCCallTimeoutHandler (RPCCallHash& rCallHash, RPCCallQueue& rCallQueue)
          : mrCallHash (rCallHash), mrCallQueue (rCallQueue)
        { }

        void RPCCallTimeoutHandler::run ()
        {
          casock::util::SafeLock lock (*this);

          while (true)
          {
            verifyEntries ();
            cond_wait ();
          }

          unlock ();
        }

        void RPCCallTimeoutHandler::verifyEntries ()
        {
          while (! mEntries.empty ())
          {
            const entry e = mEntries.top ();

            if (e.isTimedOut ())
            {
              handleTimedOutEntry (e);
              mEntries.pop ();
            }
            else
              cond_wait (e.timeout ());
          }
        }

        void RPCCallTimeoutHandler::handleTimedOutEntry (const entry& e)
        {
          RPCCall* pCall = mrCallHash.pop (e.id ());

          if (pCall)
          {
            pCall->controller ()->SetFailed ("timeout");
            mrCallQueue.push (pCall);
          }
        }

        void RPCCallTimeoutHandler::registerTimeout (const uint32& id, const struct timeval& timeout)
        {
          casock::util::SafeLock lock (*this);

          if (! mEntries.empty ())
          {
            const entry e = mEntries.top ();
            mEntries.push (entry (id, timeout));

            if (e != mEntries.top ())
              cond_signal ();
          }
          else
          {
            mEntries.push (entry (id, timeout));
            cond_signal ();
          }
        }
      }
    }
  }
}
