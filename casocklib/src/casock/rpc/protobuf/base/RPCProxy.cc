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
 * \file casock/rpc/protobuf/base/RPCProxy.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/base/RPCProxy.h"
#include "casock/util/Thread.h"
#include "casock/util/Logger.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace base {
        uint32 RPCProxy::DEFAULT_NUM_CALL_HANDLERS = 1;

        RPCProxy::~RPCProxy ()
        {
          LOGMSG (LOW_LEVEL, "%s - remove call handlers...\n", __PRETTY_FUNCTION__);
          removeCallHandlers (mCallHandlers.size ());
        }

        void RPCProxy::addCallHandlers (const uint32& n)
        {
          LOGMSG (MEDIUM_LEVEL, "%s - n [%zu]\n", __PRETTY_FUNCTION__, n);

          for (uint32 i = 0; i < n; i++)
          {
            LOGMSG (HIGH_LEVEL, "%s - i [%zu] - build call handler\n", __PRETTY_FUNCTION__, i);
            casock::util::Thread* pCallHandler = buildCallHandler ();

            LOGMSG (HIGH_LEVEL, "%s - i [%zu] - start call handler\n", __PRETTY_FUNCTION__, i);
            pCallHandler->start ();

            LOGMSG (HIGH_LEVEL, "%s - i [%zu] - push call handler back\n", __PRETTY_FUNCTION__, i);
            mCallHandlers.push_back (pCallHandler);
          }
        }

        void RPCProxy::removeCallHandlers (const uint32& n)
        {
          LOGMSG (LOW_LEVEL, "%s - n [%zu]\n", __PRETTY_FUNCTION__, n);

          for (uint32 i = 0; i < n; i++)
          {
            casock::util::Thread* pCallHandler = mCallHandlers.back ();
            mCallHandlers.pop_back ();
            LOGMSG (LOW_LEVEL, "%s - cancel handler [%zp]\n", __PRETTY_FUNCTION__, pCallHandler);
            pCallHandler->cancel ();
            LOGMSG (LOW_LEVEL, "%s - handler canceled [%zp]\n", __PRETTY_FUNCTION__, pCallHandler);
            delete pCallHandler;
          }
        }

        void RPCProxy::setNumCallHandlers (const uint32& n)
        {
          if (mCallHandlers.size () < n)
            addCallHandlers (n - mCallHandlers.size ());
          else if (mCallHandlers.size () > n)
            removeCallHandlers (mCallHandlers.size () - n);
        }
      }
    }
  }
}
