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
 * \file casock/rpc/asio/protobuf/client/RPCSocketClientImpl.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/asio/protobuf/client/RPCSocketClientImpl.h"
#include "casock/rpc/asio/protobuf/client/RPCClientCommunicatorImpl.h"
#include "casock/util/Logger.h"

namespace casock {
  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace client {
          RPCSocketClientImpl::RPCSocketClientImpl (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const std::string& host, const std::string& port)
            : casock::proactor::asio::client::SocketClient (rAsyncProcessor, host, port)
          {
            LOGMSG (LOW_LEVEL, "%s - host [%s], port [%s]\n", __PRETTY_FUNCTION__, host.c_str (), port.c_str ());
            syncConnect ();
          }

          void RPCSocketClientImpl::onConnect ()
          {
            LOGMSG (LOW_LEVEL, "%s\n", __PRETTY_FUNCTION__);
          }

          void RPCSocketClientImpl::onConnectionFailure ()
          {
            LOGMSG (LOW_LEVEL, "%s\n", __PRETTY_FUNCTION__);
          }

          RPCClientCommunicator* RPCSocketClientImpl::buildCommunicator (
              casock::rpc::protobuf::client::RPCCallHash& rCallHash,
              casock::rpc::protobuf::client::RPCCallQueue& rCallQueue)
          {
            return new RPCClientCommunicatorImpl (this, rCallHash, rCallQueue);
          }
        }
      }
    }
  }
}
