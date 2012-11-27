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
 * \file casock/rpc/asio/protobuf/server/RPCSocketServerImpl.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_IMPL_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_IMPL_H_

#include "casock/rpc/asio/protobuf/server/RPCSocketServer.h"
#include "casock/proactor/asio/server/SocketServer.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        class RPCCallQueue;
      }
    }

    namespace asio {
      namespace protobuf {
        namespace server {
          using casock::rpc::protobuf::server::RPCCallQueue;

          class RPCSocketServerImpl : public RPCSocketServer, public casock::proactor::asio::server::SocketServer
          {
            public:
              RPCSocketServerImpl (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const unsigned short& port, RPCCallQueue& rCallQueue);

            private:
              casock::proactor::asio::server::SocketSession* buildSession (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor);

            public:
              void start () { casock::proactor::asio::server::SocketServer::start (); }
              void close () { casock::proactor::asio::server::SocketServer::close (); }
              void closeAcceptor () { casock::proactor::asio::server::SocketServer::closeAcceptor (); }

            private:
              RPCCallQueue& mrCallQueue;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_IMPL_H_
