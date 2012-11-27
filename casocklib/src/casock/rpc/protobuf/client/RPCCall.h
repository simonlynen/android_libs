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
 * \file casock/rpc/protobuf/client/RPCCall.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_H_

#include "casock/util/Lockable.h"

namespace google {
  namespace protobuf {
    class Message;
    class Closure;
    class RpcController;
  }
}

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcResponse;
      }
    }

    namespace protobuf {
      namespace client {
        class RPCReaderHandler;
        using casock::rpc::protobuf::api::RpcResponse;

        class RPCCall : public casock::util::Lockable
        {
          public:
            RPCCall (::google::protobuf::Message* pResponse, ::google::protobuf::RpcController* pController, ::google::protobuf::Closure* pClosure)
              : mpResponse (pResponse), mpController (pController), mpClosure (pClosure), mpRpcResponse (NULL)
            { }

          public:
            ::google::protobuf::Message* response () { return mpResponse; }
            ::google::protobuf::RpcController* controller () { return mpController; }
            ::google::protobuf::Closure* closure () { return mpClosure; }

            void setRpcResponse (RpcResponse* pRpcResponse) { mpRpcResponse = pRpcResponse; }
            RpcResponse* rpcResponse () { return mpRpcResponse; }

          private:
            ::google::protobuf::Message* mpResponse;
            ::google::protobuf::RpcController* mpController;
            ::google::protobuf::Closure* mpClosure;

            RpcResponse* mpRpcResponse;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_H_
