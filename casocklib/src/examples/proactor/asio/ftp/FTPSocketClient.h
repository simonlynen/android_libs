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
 * \file examples/proactor/asio/ftp/FTPSocketClient.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_CLIENT_H_
#define __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_CLIENT_H_

#include <boost/bind.hpp>

#include "casock/util/Logger.h"
#include "casock/proactor/asio/client/SocketClient.h"
#include "examples/proactor/asio/ftp/FTPCommunicator.h"
#include "examples/ftp/FTPFile.h"

namespace examples {
  namespace proactor {
    namespace asio {
      namespace ftp {
        class FTPSocketClient : public casock::proactor::asio::client::SocketClient
        {
          public:
            FTPSocketClient (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const std::string& host, const std::string& port, const examples::ftp::FTPFile& rFile)
              : casock::proactor::asio::client::SocketClient (rAsyncProcessor, host, port), mrFile (rFile), mCommunicator (this)
            {
              LOGMSG (LOW_LEVEL, "FTPSocketClient::FTPSocketClient () - host [%s], port [%s]\n", host.c_str (), port.c_str ());
            }

          public:
            void onSentFile (const ::asio::error_code& error)
            {
              if (! error)
              {
                LOGMSG (LOW_LEVEL, "FTPSocketClient::%s () - NO ERROR!\n", __FUNCTION__);
              }
              else
              {
                LOGMSG (LOW_LEVEL, "FTPSocketClient::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              }

              close ();
            }

          protected:
            void onConnect ()
            {
              LOGMSG (LOW_LEVEL, "FTPSocketClient::%s ()\n", __FUNCTION__);
              mCommunicator.sendFile (mrFile, ::boost::bind (&FTPSocketClient::onSentFile, this, ::asio::placeholders::error));
            }

            void onConnectionFailure ()
            {
              LOGMSG (LOW_LEVEL, "FTPSocketClient::%s ()\n", __FUNCTION__);
            }

          private:
            const examples::ftp::FTPFile& mrFile;
            examples::proactor::asio::ftp::FTPCommunicator mCommunicator;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_SOCKET_CLIENT_H_
