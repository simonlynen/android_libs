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
 * \file casock/rpc/sigio/protobuf/client/RPCChannel.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT__RPC_CHANNEL_H_
#define __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT__RPC_CHANNEL_H_

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcRequest;
      }

      namespace client {
        class RPCCall;
      }
    }

    namespace sigio {
      namespace protobuf {
        namespace base {
          class RPCCommunicator;
        }

        namespace client {
          using casock::rpc::sigio::protobuf::base::RPCCommunicator;

          class RPCChannel
          {
            public:
              RPCChannel (casock::rpc::sigio::protobuf::base::RPCCommunicator* pCommunicator);

            public:
              void RpcCall (const casock::rpc::protobuf::api::RpcRequest& request);

            private:
              RPCCommunicator* mpCommunicator;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT__RPC_CHANNEL_H_
