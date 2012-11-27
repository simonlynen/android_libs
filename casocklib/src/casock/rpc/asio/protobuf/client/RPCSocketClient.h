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
 * \file casock/rpc/asio/protobuf/client/RPCSocketClient.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_SOCKET_CLIENT_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_SOCKET_CLIENT_H_

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
				class RPCCallHash;
        class RPCCallQueue;
      }
    }

    namespace asio {
      namespace protobuf {
        namespace client {
          class RPCClientCommunicator;

          class RPCSocketClient
          {
            public:
              virtual ~RPCSocketClient () { }

            public:
              virtual RPCClientCommunicator* buildCommunicator (
                  casock::rpc::protobuf::client::RPCCallHash& rCallHash,
                  casock::rpc::protobuf::client::RPCCallQueue& rCallQueue) = 0;

              virtual void close () = 0;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_SOCKET_CLIENT_H_
