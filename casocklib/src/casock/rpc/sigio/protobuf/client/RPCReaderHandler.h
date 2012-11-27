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
 * \file casock/rpc/sigio/protobuf/client/RPCReaderHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT_RPC_READER_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT_RPC_READER_HANDLER_H_

#include "casock/sigio/base/Handler.h"
#include "casock/rpc/sigio/protobuf/client/RPCClientCommunicator.h"

namespace casock {
  namespace sigio {
    namespace base {
      class Dispatcher;
      class FileDescriptor;
    }
  }

  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCCall;
        class RPCCallHash;
        class RPCCallQueue;
      }
    }

    namespace sigio {
      namespace protobuf {
        namespace client {
          using casock::rpc::protobuf::client::RPCCall;
          using casock::rpc::protobuf::client::RPCCallHash;
          using casock::rpc::protobuf::client::RPCCallQueue;

          class RPCReaderHandler : public casock::sigio::base::Handler
          {
            public:
              RPCReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const casock::sigio::base::FileDescriptor* const pFileDescriptor, RPCCallHash& rCallHash, RPCCallQueue& rCallQueue);

            private:
              void destroy () { delete this; }

            public:
              void handle ();
              RPCClientCommunicator& communicator () { return mCommunicator; }

            private:
              RPCClientCommunicator mCommunicator; /*!< used to read from socket, returns an object of type casock::rpc::protobuf::api::RpcResponse */

              RPCCallHash&  mrCallHash;
              RPCCallQueue& mrCallQueue;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_SIGIO_PROTOBUF_CLIENT_RPC_READER_HANDLER_H_
