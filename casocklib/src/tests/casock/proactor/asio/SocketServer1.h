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
 * \file tests/casock/proactor/asio/SocketServer1.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_SERVER1_H_
#define __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_SERVER1_H_

#include "casock/util/Logger.h"
#include "casock/proactor/asio/server/SocketServer.h"
#include "tests/casock/proactor/asio/SocketSession1.h"

namespace tests {
  namespace casock {
    namespace proactor {
      namespace asio {
        class SocketServer1 : public ::casock::proactor::asio::server::SocketServer
        {
          public:
            SocketServer1 (::casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const unsigned short& port)
              : ::casock::proactor::asio::server::SocketServer (rAsyncProcessor, port)
            {
              LOGMSG (MAX_LEVEL, "SocketServer1::SocketServer1 () - port [%hu]\n", port);
            }

          private:
            ::casock::proactor::asio::server::SocketSession* buildSession (::casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor)
            {
              LOGMSG (MEDIUM_LEVEL, "SocketServer1::%s ()\n", __FUNCTION__);

              return new SocketSession1 (rAsyncProcessor, *this);
            }
        };
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_SERVER1_H_
