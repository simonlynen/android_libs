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
 * \file tests/casock/proactor/asio/SocketSession1.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_SESSION1_H_
#define __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_SESSION1_H_

#include <sstream>
#include <boost/bind.hpp>

#include "casock/util/Logger.h"
#include "casock/util/Buffer.h"
#include "casock/proactor/asio/server/SocketSession.h"

namespace tests {
  namespace casock {
    namespace proactor {
      namespace asio {
        class SocketSession1 : public ::casock::proactor::asio::server::SocketSession
        {
          public:
            SocketSession1 (
                ::casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor,
                ::casock::proactor::asio::server::SocketServer& rSocketServer)
              : ::casock::proactor::asio::server::SocketSession (rAsyncProcessor, rSocketServer)
            {
              LOGMSG (MAX_LEVEL, "SocketSession1::SocketSession1 ()\n");
              mMyID = ++SocketSession1::mID;
            }

          private:
            void onConnect ()
            {
              LOGMSG (MEDIUM_LEVEL, "SocketSession1::%s ()\n", __FUNCTION__);
              readsome (buffer.buff (), buffer.size (), ::boost::bind (&SocketSession1::onReadBuffer, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
            }

            void onReadBuffer (const ::asio::error_code& error, const size_t& bytes_transferred)
            {
              LOGMSG (LOW_LEVEL, "SocketSession1::%s () - mMyID [%04u], bytes_transferred [%zu], buffer [%s]\n", __FUNCTION__, mMyID, bytes_transferred, buffer.data ());
              std::stringstream ss;
              ss << "message received [" << buffer.data () << "]";
              buffer.clear ();
              write (ss.str ().c_str (), ss.str ().size (), ::boost::bind (&SocketSession1::onWriteBuffer, this, ::asio::placeholders::error));
            }

            void onWriteBuffer (const ::asio::error_code& error)
            {
              if (! error)
              {
                LOGMSG (MEDIUM_LEVEL, "SocketSession1::%s () - NO ERROR!\n", __FUNCTION__);
                readsome (buffer.buff (), buffer.size (), ::boost::bind (&SocketSession1::onReadBuffer, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
              }
              else
              {
                LOGMSG (LOW_LEVEL, "SocketSession1::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
                close ();
              }
            }

          private:
            ::casock::util::Buffer buffer;

            uint32 mMyID;

            static uint32 mID;
        };

        uint32 SocketSession1::mID = 0;
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_SESSION1_H_
