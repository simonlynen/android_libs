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
 * \file casock/rpc/protobuf/client/RPCRequestBuilder.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/client/RPCRequestBuilder.h"

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

#include "casock/rpc/protobuf/api/rpc.pb.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        casock::rpc::protobuf::api::RpcRequest* RPCRequestBuilder::buildRpcRequest (
            const google::protobuf::MethodDescriptor* method,
            const google::protobuf::Message* request) const
        {
          casock::rpc::protobuf::api::RpcRequest* pRequest = new casock::rpc::protobuf::api::RpcRequest ();
          pRequest->set_id (++mID);
          pRequest->set_operation (method->name ());
          pRequest->set_request (request->SerializeAsString ());

          return pRequest;
        }

        casock::rpc::protobuf::api::RpcRequest* RPCRequestBuilder::buildRpcRequest (
            const std::string& operation,
            const google::protobuf::Message* request) const
        {
          casock::rpc::protobuf::api::RpcRequest* pRequest = new casock::rpc::protobuf::api::RpcRequest ();
          pRequest->set_id (++mID);
          pRequest->set_operation (operation);
          pRequest->set_request (request->SerializeAsString ());

          return pRequest;
        }
      }
    }
  }
}
