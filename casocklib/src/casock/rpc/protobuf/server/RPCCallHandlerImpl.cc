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
 * \file casock/rpc/protobuf/server/RPCCallHandlerImpl.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/server/RPCCallHandlerImpl.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>

#include "casock/util/Logger.h"
#include "casock/util/Thread.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/server/RPCCall.h"
#include "casock/rpc/protobuf/server/RPCCallQueue.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        RPCCallHandlerImpl::RPCCallHandlerImpl (RPCCallQueue& rCallQueue, ::google::protobuf::Service* pService)
          : mrCallQueue (rCallQueue), mpService (pService)
        { }

        void RPCCallHandlerImpl::run ()
        {
          while (true)
          {
            LOGMSG (LOW_LEVEL, "RPCCallHandlerImpl::%s () - calling mrCallQueue.pop ()...\n", __FUNCTION__);
            RPCCall* pCall = mrCallQueue.pop ();
            LOGMSG (LOW_LEVEL, "RPCCallHandlerImpl::%s () - got pCall [%p]!\n", __FUNCTION__, pCall);

            const RpcRequest* const pRpcRequest = pCall->request ();

            LOGMSG (NO_DEBUG, "RPCCallhandler::%s () - mpService [%p]\n", __FUNCTION__, mpService);
            LOGMSG (NO_DEBUG, "RPCCallhandler::%s () - mpService->GetDescriptor () [%p]\n", __FUNCTION__, mpService->GetDescriptor ());
            LOGMSG (NO_DEBUG, "RPCCallhandler::%s () - pRpcRequest [%p]\n", __FUNCTION__, pRpcRequest);

            const ::google::protobuf::MethodDescriptor* method = mpService->GetDescriptor ()->FindMethodByName (pRpcRequest->operation ());

            if (method != NULL)
            {
              LOGMSG (NO_DEBUG, "RPCCallHandlerImpl::%s () - OK\n", __FUNCTION__);

              ::google::protobuf::Message* request = mpService->GetRequestPrototype (method).New ();
              request->ParseFromString (pRpcRequest->request ());

              /*!
               * I didn't see anybody using a controller in the server side yet.
               * So, just for now, let's set it as NULL.
               */
              ::google::protobuf::RpcController* controller = NULL;
              ::google::protobuf::Message* response = mpService->GetResponsePrototype (method).New ();

              /*!
               * The RPCCallEntry will be deleted on RPCCallHandler::callback (RPCCallEntry*).
               */
              ::google::protobuf::Closure* closure = ::google::protobuf::NewCallback (RPCCallHandler::callback, new RPCCallEntry (pCall, response)); //, controller));

              mpService->CallMethod (method, controller, request, response, closure);

              delete request;
            }
            else
              LOGMSG (NO_DEBUG, "RPCCallHandlerImpl::%s () - no method called [%s]\n", __FUNCTION__, pRpcRequest->operation ().c_str ());
          }
        }
      }
    }
  }
}
