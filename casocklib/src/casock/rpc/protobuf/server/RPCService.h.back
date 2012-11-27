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
 * \file casock/rpc/sigio/protobuf/server/RPCService.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef _RPC_SERVICE_H_
#define _RPC_SERVICE_H_

#include "casock/rpc/protobuf/api/rpc.pb.h"

class RPCService : public casock::rpc::protobuf::api::RpcService
{
  public:
    void RpcCall(::google::protobuf::RpcController* controller,
        const ::casock::rpc::protobuf::api::RpcRequest* request,
        ::casock::rpc::protobuf::api::RpcResponse* response,
        ::google::protobuf::Closure* done)
    {
      response->set_id (10);
      done->Run ();
    }
};

#endif // _RPC_SERVICE_H_
