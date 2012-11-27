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
 * \file casock/rpc/asio/protobuf/server/RPCSocketServer.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/asio/protobuf/server/RPCSocketServer.h"
#include "casock/rpc/asio/protobuf/server/RPCSocketSession.h"

namespace casock {
  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace server {
          RPCSocketServer::RPCSocketServer (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const unsigned short& port, RPCCallQueue& rCallQueue)
            : casock::proactor::asio::server::SocketServer (rAsyncProcessor, port), mrCallQueue (rCallQueue)
          {
          }

          casock::proactor::asio::server::SocketSession* RPCSocketServer::buildSession (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor)
          {
            return new RPCSocketSession (rAsyncProcessor, *this, mrCallQueue);
          }
        }
      }
    }
  }
}
