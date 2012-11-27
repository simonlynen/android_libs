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
 * \file casock/rpc/protobuf/server/RPCCallHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/server/RPCCallHandler.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>

#include "casock/util/Logger.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/server/RPCCall.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        RPCCallHandler::RPCCallEntry::RPCCallEntry (RPCCall* pCall, ::google::protobuf::Message* pResponse)
          : mpCall (pCall), mpResponse (pResponse)
        { }

        RPCCallHandler::RPCCallEntry::~RPCCallEntry ()
        {
          delete mpCall;
          delete mpResponse;
        }

        void RPCCallHandler::callback (RPCCallEntry* pCallEntry)
        {
          LOGMSG (LOW_LEVEL, "RPCCallHandler::%s ()\n", __FUNCTION__);

          RPCCall* pCall = pCallEntry->call ();
          ::google::protobuf::Message* pResponse = pCallEntry->response ();

          RpcResponse rpcResponse;
          rpcResponse.set_id (pCall->request ()->id ());
          rpcResponse.set_type (casock::rpc::protobuf::api::RESPONSE_TYPE_OK);
          rpcResponse.set_response (pResponse->SerializeAsString ());

          pCall->lock ();
          pCall->callback (rpcResponse);
          pCall->unlock ();

          delete pCallEntry;
        }
      }
    }
  }
}
