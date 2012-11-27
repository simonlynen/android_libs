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
 * \file examples/proactor/asio/ftp/FTPCommunicator.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_COMMUNICATOR_H_
#define __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_COMMUNICATOR_H_

#include <boost/function.hpp>

#include "casock/proactor/asio/base/Communicator.h"
#include "examples/ftp/FTPFile.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        class SocketChannel;
      }
    }
  }
}

namespace examples {
  namespace proactor {
    namespace asio {
      namespace ftp {
        class FTPCommunicator : private casock::proactor::asio::base::Communicator
        {
          public:
            FTPCommunicator (casock::proactor::asio::base::SocketChannel* const pChannel)
              : casock::proactor::asio::base::Communicator (pChannel), mSize (0)
            { }

          private:
            void onSentSize (const ::asio::error_code& error, const examples::ftp::FTPFile& rFile, ::boost::function<void(const ::asio::error_code&)> handler)
            {
              if (! error)
              {
                write (rFile.getBuffer (), rFile.getSize (), ::boost::bind (&FTPCommunicator::onSentBuffer, this, ::asio::placeholders::error, handler));
              }
              else
              {
                LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              }
            }

            void onSentBuffer (const ::asio::error_code& error, ::boost::function<void(const ::asio::error_code&)> handler)
            {
              if (error)
              {
                LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              }

              handler (error);
            }
 
            void onReadSize (const ::asio::error_code& error, ::boost::function<void(const ::asio::error_code&, examples::ftp::FTPFile*)> handler)
            {
              if (! error)
              {
                char* buffer = new char [mSize];
                read (buffer, mSize, ::boost::bind (&FTPCommunicator::onReadBuffer, this, ::asio::placeholders::error, buffer, handler));
              }
              else
              {
                LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              }
            }

            void onReadBuffer (const ::asio::error_code& error, char* buffer, ::boost::function<void(const ::asio::error_code&, examples::ftp::FTPFile*)> handler)
            {
              examples::ftp::FTPFile* pFile = NULL;

              if (! error)
              {
                stringstream ss;
                ss << "file_";
                ss << ++mCounter;
                ss << ".ftp";

                std::string filename = ss.str ();

                pFile = new examples::ftp::FTPFile (filename);
                pFile->setSize (mSize);
                pFile->setBuffer (buffer);
              }
              else
              {
                LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              }

              handler (error, pFile);
            }

          public:
            void sendFile (const examples::ftp::FTPFile& rFile, ::boost::function<void(const ::asio::error_code&)> handler)
            {
              write (rFile.getSize (), ::boost::bind (&FTPCommunicator::onSentSize, this, ::asio::placeholders::error, rFile, handler));
            }

            void getFile (::boost::function<void(const ::asio::error_code&, examples::ftp::FTPFile*)> handler)
            {
              read (mSize, ::boost::bind (&FTPCommunicator::onReadSize, this, ::asio::placeholders::error, handler));
            }

          private:
            size_t mSize;
            static unsigned long mCounter;
        };

        unsigned long FTPCommunicator::mCounter = 0;
      }
    }
  }
}

#endif // __CASOCKLIB__EXAMPLES_PROACTOR_ASIO_FTP__FTP_COMMUNICATOR_H_
