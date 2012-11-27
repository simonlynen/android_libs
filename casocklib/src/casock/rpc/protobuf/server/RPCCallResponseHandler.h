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
 * \file casock/rpc/protobuf/server/RPCCallResponseHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_RESPONSE_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_RESPONSE_HANDLER_H_

#include "casock/util/types.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcResponse;
      }
    }

    namespace protobuf {
      namespace server {
        class RPCCall;

        class RPCCallResponseHandler
        {
          public:
            virtual ~RPCCallResponseHandler () { }

          protected:
            virtual void invalidateCalls () = 0;

          public:
            virtual void registerCall (const uint32& id, const RPCCall* const pCall) = 0;
            virtual void unregisterCall (const uint32& id) = 0;
            virtual const bool tryUnregisterCall (const uint32& id) = 0;
            virtual void callback (const casock::rpc::protobuf::api::RpcResponse& response) = 0;
        };
      }
    }
  }
}


#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_RESPONSE_HANDLER_H_

