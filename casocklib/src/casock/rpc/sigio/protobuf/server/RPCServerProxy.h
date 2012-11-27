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
 * \file casock/rpc/sigio/protobuf/server/RPCServerProxy.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_
#define __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_

#include "casock/rpc/protobuf/server/RPCServerProxy.h"

namespace casock {
  namespace sigio {
    namespace base {
      class Dispatcher;
    }

    namespace server {
      class SocketServer;
    }
  }

  namespace rpc {
    namespace sigio {
      namespace protobuf {
        namespace server {
          class RPCAcceptorHandler;
          using casock::rpc::protobuf::server::RPCCallHandlerFactory;

          class RPCServerProxy : public casock::rpc::protobuf::server::RPCServerProxy
          {
            public:
              RPCServerProxy (
                  RPCCallHandlerFactory& rCallHandlerFactory,
                  casock::sigio::base::Dispatcher& rDispatcher,
                  const unsigned int& port);
              virtual ~RPCServerProxy ();

            public:
              void start ();
              void stop ();

            private:
              casock::sigio::base::Dispatcher&      mrDispatcher;
              casock::sigio::server::SocketServer*  mpSocketServer;
              RPCAcceptorHandler*                   mpAcceptorHandler;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_
