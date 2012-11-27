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
 * \file casock/rpc/protobuf/client/RPCRequestBuilder.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_REQUEST_BUILDER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_REQUEST_BUILDER_H_

#include <string>
#include "casock/util/types.h"

namespace google {
  namespace protobuf {
    class MethodDescriptor;
    class Message;
  }
}

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcRequest;
      }

      namespace client {
        class RPCRequestBuilder
        {
          public:
            RPCRequestBuilder ()
              : mID (0)
            { }

          public:
            casock::rpc::protobuf::api::RpcRequest* buildRpcRequest (
                const google::protobuf::MethodDescriptor* method,
                const google::protobuf::Message* request) const;

            casock::rpc::protobuf::api::RpcRequest* buildRpcRequest (
                const std::string& operation,
                const google::protobuf::Message* request) const;

          private:
            mutable uint32 mID;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_REQUEST_BUILDER_H_
