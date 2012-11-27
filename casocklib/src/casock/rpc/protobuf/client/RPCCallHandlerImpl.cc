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
 * \file casock/rpc/protobuf/client/RPCCallHandlerImpl.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/client/RPCCallHandlerImpl.h"

#include <google/protobuf/service.h>

#include "casock/util/Logger.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        RPCCallHandlerImpl::RPCCallHandlerImpl (RPCCallQueue& rCallQueue)
          : mrCallQueue (rCallQueue)
        {
          LOGMSG (NO_DEBUG, "%s\n", __PRETTY_FUNCTION__);
        }

        void RPCCallHandlerImpl::run ()
        {
          LOGMSG (NO_DEBUG, "%s\n", __PRETTY_FUNCTION__);

          while (true)
          {
            casock::rpc::protobuf::client::RPCCall* pCall = mrCallQueue.pop ();

            RpcResponse* pRpcResponse = static_cast<RpcResponse*>(pCall->rpcResponse ());
            google::protobuf::RpcController* controller = pCall->controller ();
            google::protobuf::Closure* closure = pCall->closure ();

            if (pRpcResponse)
            {
              LOGMSG (LOW_LEVEL, "RPCCallHandlerImpl::%s () - controller [%p], id [%u], type [%u]\n", __FUNCTION__, controller, pRpcResponse->id (), pRpcResponse->type ());
              pCall->response ()->ParseFromString (pRpcResponse->response ());
              delete pRpcResponse;
            }
            else
            {
              LOGMSG (LOW_LEVEL, "RPCCallHandlerImpl::%s () - controller [%p], pRpcResponse [%p]\n", __FUNCTION__, controller, pRpcResponse);
              controller->SetFailed ("Error receiving response!");
            }

            closure->Run ();

            delete pCall;
          }
        }
      }
    }
  }
}
