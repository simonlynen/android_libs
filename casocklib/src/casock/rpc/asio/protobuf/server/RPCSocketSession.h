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
 * \file casock/rpc/asio/protobuf/server/RPCSocketSession.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SESSION_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SESSION_H_

#include "casock/proactor/asio/server/SocketSession.h"
#include "casock/rpc/protobuf/server/RPCCallResponseHandler.h"

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
          class RPCServerCommunicator;
          using casock::rpc::protobuf::server::RPCCallResponseHandler;

          class RPCSocketSession : public casock::proactor::asio::server::SocketSession
          {
            public:
              RPCSocketSession (
                  casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor,
                  casock::proactor::asio::server::SocketServer& rSocketServer,
                  casock::rpc::protobuf::server::RPCCallQueue& rCallQueue);
              virtual ~RPCSocketSession ();

            private:
              void onConnect ();

            private:
              RPCServerCommunicator*  mpCommunicator;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SESSION_H_
