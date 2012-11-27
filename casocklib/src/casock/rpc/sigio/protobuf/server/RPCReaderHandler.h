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
 * \file casock/rpc/sigio/protobuf/server/RPCReaderHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_SERVER__RPC_READER_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_SERVER__RPC_READER_HANDLER_H_

#include "casock/sigio/base/Handler.h"
#include "casock/rpc/protobuf/server/RPCCallResponseHandlerImpl.h"
#include "casock/rpc/sigio/protobuf/server/RPCServerCommunicator.h"

namespace casock {
  namespace sigio {
    namespace base {
      class Dispatcher;
    }
  }

  namespace rpc {
    namespace protobuf {
      namespace server {
        class RPCCallQueue;
      }
    }

    namespace protobuf {
      namespace api {
        class RpcResponse;
      }
    }

    namespace sigio {
      namespace protobuf {
        namespace server {
          using casock::rpc::protobuf::api::RpcResponse;
          using casock::rpc::protobuf::server::RPCCallResponseHandlerImpl;
          using casock::rpc::protobuf::server::RPCCallQueue;

          class RPCReaderHandler : public casock::sigio::base::Handler, public RPCCallResponseHandlerImpl
          {
            public:
              RPCReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const int& fd, RPCCallQueue& rCallQueue);

            private:
              void destroy () { delete this; }

            public:
              void handle ();
              void callback (const RpcResponse& response);

            private:
              RPCServerCommunicator mCommunicator;
              RPCCallQueue&         mrCallQueue;
          };
        }
      }
    }
  }
}


#endif // __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_SERVER__RPC_READER_HANDLER_H_

