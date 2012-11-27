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
 * \file casock/rpc/protobuf/server/RPCCall.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/server/RPCCall.h"
#include "casock/util/Logger.h"
#include "casock/util/Lockable.h"
#include "casock/util/SafeLock.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/server/RPCCallResponseHandler.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        RPCCall::RPCCall (RPCCallResponseHandler* const pResponseHandler, const RpcRequest* const pRequest)
          : mpResponseHandler (pResponseHandler), mpRequest (pRequest)
        {
          if (mpResponseHandler)
            mpResponseHandler->registerCall (mpRequest->id (), this);
        }

        RPCCall::~RPCCall ()
        {
          /*
           * We need unregister the call.
           * We need a way to avoid deadlock when a disconnect happens:
           */

          bool unregistered = false;

          do
          {
            lock ();
            if (mpResponseHandler)
            {
              LOGMSG (LOW_LEVEL, "RPCCall::~RPCCall () - trying to unregister from response handler [%p]...\n", __FUNCTION__, mpResponseHandler);
              unregistered = mpResponseHandler->tryUnregisterCall (mpRequest->id ());
            }
            unlock ();
          } while (! unregistered && ! sleep (1));

          delete mpRequest;
        }

        void RPCCall::invalidateHandler ()
        {
          casock::util::SafeLock lock (*this);
          mpResponseHandler = NULL;
        }

        void RPCCall::callback (const RpcResponse& response)
        {
          LOGMSG (LOW_LEVEL, "RPCCall::%s ()\n", __FUNCTION__);

          if (mpResponseHandler)
            mpResponseHandler->callback (response);
        }
      }
    }
  }
}
