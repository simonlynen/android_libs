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
 * \file casock/proactor/asio/server/SocketSession.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/proactor/asio/server/SocketSession.h"
#include "casock/proactor/asio/server/SocketServer.h"
#include "casock/util/Logger.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace server {
        SocketSession::SocketSession (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, SocketServer& rSocketServer)
          : casock::proactor::asio::base::SocketChannel (rAsyncProcessor), mrSocketServer (rSocketServer)
        { }

        void SocketSession::onConnectionFailure ()
        {
          LOGMSG (LOW_LEVEL, "SocketSession::%s ()\n", __FUNCTION__);
        }

        void SocketSession::close ()
        {
          casock::proactor::asio::base::SocketChannel::close ();
          mrSocketServer.removeSession (this);
        }
      }
    }
  }
}
