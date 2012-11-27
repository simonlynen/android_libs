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
 * \file casock/rpc/asio/protobuf/client/RPCClientCommunicatorImpl.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_CLIENT_COMMUNICATOR_IMPL_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_CLIENT_COMMUNICATOR_IMPL_H_

#include "casock/rpc/asio/protobuf/base/RPCCommunicator.h"
#include "casock/rpc/asio/protobuf/client/RPCClientCommunicator.h"

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
          using casock::rpc::protobuf::client::RPCCallHash;
          using casock::rpc::protobuf::client::RPCCallQueue;

          class RPCClientCommunicatorImpl : public RPCClientCommunicator, public casock::rpc::asio::protobuf::base::RPCCommunicator
          {
            public:
              RPCClientCommunicatorImpl (casock::proactor::asio::base::SocketChannel* const pChannel, RPCCallHash& rCallHash, RPCCallQueue& rCallQueue);

            private:
              ::google::protobuf::Message* createRecvMessage ();
              void recvResponse (::boost::function<void(const ::asio::error_code&, ::google::protobuf::Message*)> handler);
              void onRecvResponse (const ::asio::error_code& error, ::google::protobuf::Message* pMessage);

            public:
              void startReceivingResponses ();
              void sendRequest (const ::google::protobuf::Message& message, ::boost::function<void(const ::asio::error_code&)> handler);

            private:
              RPCCallHash&					mrCallHash;
              RPCCallQueue&         mrCallQueue;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_CLIENT__RPC_CLIENT_COMMUNICATOR_IMPL_H_
