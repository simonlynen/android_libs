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
 * \file examples/proactor/asio/FTPSocketSession.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_SESSION_H_
#define __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_SESSION_H_

#include <sstream>
#include <iomanip>
#include <boost/bind.hpp>

#include "casock/util/Logger.h"
#include "casock/proactor/asio/server/SocketSession.h"
#include "examples/proactor/asio/ftp/FTPCommunicator.h"
#include "examples/ftp/FTPFile.h"

namespace examples {
  namespace proactor {
    namespace asio {
      namespace ftp {
        class FTPSocketSession : public casock::proactor::asio::server::SocketSession
        {
          public:
            FTPSocketSession (
                casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor,
                casock::proactor::asio::server::SocketServer& rSocketServer)
              : casock::proactor::asio::server::SocketSession (rAsyncProcessor, rSocketServer), mCommunicator (this)
            {
              LOGMSG (LOW_LEVEL, "FTPSocketSession::FTPSocketSession ()\n");
            }

          public:
            void onGetFile (const ::asio::error_code& error, examples::ftp::FTPFile* pFile)
            {
              if (! error)
              {
                pFile->save ();
                delete pFile;
                mCommunicator.getFile (::boost::bind (&FTPSocketSession::onGetFile, this, ::asio::placeholders::error, _2));
              }
              else
              {
                close ();
              }
            }

          private:
            void onConnect ()
            {
              LOGMSG (LOW_LEVEL, "FTPSocketSession::%s ()\n", __FUNCTION__);
              mCommunicator.getFile (::boost::bind (&FTPSocketSession::onGetFile, this, ::asio::placeholders::error, _2));
            }

          private:
            examples::proactor::asio::ftp::FTPCommunicator mCommunicator;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_SESSION_H_
