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
 * \file examples/proactor/asio/ftp/FTPSocketServer.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_SERVER_H_
#define __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_SERVER_H_

#include "casock/util/Logger.h"
#include "casock/proactor/asio/server/SocketServer.h"
#include "examples/proactor/asio/ftp/FTPSocketSession.h"

namespace examples {
  namespace proactor {
    namespace asio {
      namespace ftp {
        class FTPSocketServer : public casock::proactor::asio::server::SocketServer
        {
          public:
            FTPSocketServer (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const unsigned short& port)
              : casock::proactor::asio::server::SocketServer (rAsyncProcessor, port)
            {
              LOGMSG (LOW_LEVEL, "FTPSocketServer::FTPSocketServer () - port [%hu]\n", port);
            }

          private:
            casock::proactor::asio::server::SocketSession* buildSession (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor)
            {
              LOGMSG (LOW_LEVEL, "FTPSocketServer::%s ()\n", __FUNCTION__);
              return new FTPSocketSession (rAsyncProcessor, *this);
            }
        };
      }
    }
  }
}

#endif // __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_SERVER_H_
