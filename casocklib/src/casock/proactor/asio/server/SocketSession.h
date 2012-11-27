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
 * \file casock/proactor/asio/server/SocketSession.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_PROACTOR_ASIO_SERVER__SOCKET_SESSION_H_
#define __CASOCKLIB__CASOCK_PROACTOR_ASIO_SERVER__SOCKET_SESSION_H_

#include "casock/proactor/asio/base/SocketChannel.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace server {
        class SocketServer;

        class SocketSession : protected casock::proactor::asio::base::SocketChannel
        {
          private:
            friend class SocketServer;

          public:
            SocketSession (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, SocketServer& rSocketServer);

          private:
            virtual void onConnect () = 0;
            virtual void onConnectionFailure ();

          protected:
            virtual void close ();

          private:
            SocketServer& mrSocketServer;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_PROACTOR_ASIO_SERVER__SOCKET_SESSION_H_
