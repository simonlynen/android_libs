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
 * \file casock/rpc/asio/protobuf/server/RPCSocketSession.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/server/RPCCallQueue.h"
#include "casock/rpc/asio/protobuf/server/RPCSocketSession.h"
#include "casock/rpc/asio/protobuf/server/RPCServerCommunicator.h"
#include "casock/util/Logger.h"

namespace casock {
  namespace rpc {
    namespace asio {
      namespace protobuf {
        namespace server {
          RPCSocketSession::RPCSocketSession (
              casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor,
              casock::proactor::asio::server::SocketServer& rSocketServer,
              casock::rpc::protobuf::server::RPCCallQueue& rCallQueue)
            : casock::proactor::asio::server::SocketSession (rAsyncProcessor, rSocketServer)
          {
            mpCommunicator = new RPCServerCommunicator (this, rCallQueue);
          }

          RPCSocketSession::~RPCSocketSession ()
          {
            delete mpCommunicator;
          }

          void RPCSocketSession::onConnect ()
          {
            LOGMSG (LOW_LEVEL, "RPCSocketSession::%s ()\n", __FUNCTION__);

            mpCommunicator->startReceivingRequests ();
          }
        }
      }
    }
  }
}
