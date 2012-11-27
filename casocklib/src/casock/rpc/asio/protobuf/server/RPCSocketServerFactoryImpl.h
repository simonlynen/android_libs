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
 * \file casock/rpc/asio/protobuf/server/RPCSocketServerFactoryImpl.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_FACTORY_IMPL_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_FACTORY_IMPL_H_

#include "casock/util/types.h"
#include "casock/rpc/asio/protobuf/server/RPCSocketServerFactory.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        class AsyncProcessor;
      }
    }
  }

  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace server {
          using casock::proactor::asio::base::AsyncProcessor;

          class RPCSocketServerFactoryImpl : public RPCSocketServerFactory
          {
            public:
              RPCSocketServerFactoryImpl (
                  AsyncProcessor& rAsyncProcessor,
                  const uint32& port);

            public:
              RPCSocketServer* buildRPCSocketServer (casock::rpc::protobuf::server::RPCCallQueue& rCallQueue) const;

            private:
              AsyncProcessor& mrAsyncProcessor;
              const uint32 m_port;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_SERVER__RPC_SOCKET_SERVER_FACTORY_IMPL_H_
