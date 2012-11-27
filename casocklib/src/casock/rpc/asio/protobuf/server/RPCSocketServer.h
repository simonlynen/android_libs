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
 * \file casock/rpc/asio/protobuf/server/RPCSocketServer.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_H_

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        class AsyncProcessor;
      }

      namespace server {
        class SocketSession;
      }
    }
  }

  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace server {
          class RPCSocketSession;

          class RPCSocketServer
          {
            public:
              virtual ~RPCSocketServer () { };

            private:
              virtual casock::proactor::asio::server::SocketSession* buildSession (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor) = 0;

            public:
              virtual void start () = 0;
              virtual void close () = 0;
              virtual void closeAcceptor () = 0;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_H_
