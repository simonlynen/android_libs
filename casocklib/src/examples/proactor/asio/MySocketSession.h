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
 * \file examples/proactor/asio/MySocketSession.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__EXAMPLES_PROACTOR_ASIO__MY_SOCKET_SESSION_H_
#define __CASOCKLIB__EXAMPLES_PROACTOR_ASIO__MY_SOCKET_SESSION_H_

#include <sstream>
#include <boost/bind.hpp>

#include "casock/util/Logger.h"
#include "casock/util/Buffer.h"
#include "casock/proactor/asio/server/SocketSession.h"

namespace examples {
  namespace proactor {
    namespace asio {
      class MySocketSession : public casock::proactor::asio::server::SocketSession
      {
        public:
          MySocketSession (
              casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor,
              casock::proactor::asio::server::SocketServer& rSocketServer)
            : casock::proactor::asio::server::SocketSession (rAsyncProcessor, rSocketServer)
          {
            LOGMSG (LOW_LEVEL, "MySocketSession::MySocketSession ()\n");
            mShutdown = false;
          }

        private:
          void onConnect ()
          {
            LOGMSG (LOW_LEVEL, "MySocketSession::%s ()\n", __FUNCTION__);
            readsome (buffer.buff (), buffer.size (), ::boost::bind (&MySocketSession::onReadBuffer, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
          }

          void onReadBuffer (const ::asio::error_code& error, const size_t& bytes_transferred)
          {
            LOGMSG (LOW_LEVEL, "MySocketSession::%s () - bytes_transferred [%zu], buffer [%s]\n", __FUNCTION__, bytes_transferred, buffer.data ());
            std::stringstream ss;
            ss << "message received [" << buffer.data () << "]";
            write (ss.str ().c_str (), ss.str ().size (), ::boost::bind (&MySocketSession::onWriteBuffer, this, ::asio::placeholders::error));

            /*
            if (buffer == "shutdown")
            {
              close ();
              mrSocketServer.close ();
            }
            else
              buffer.clear ();
              */

            if (buffer == "shutdown")
              mShutdown = true;

            buffer.clear ();
          }

          void onWriteBuffer (const ::asio::error_code& error)
          {
            if (! error)
            {
              LOGMSG (LOW_LEVEL, "MySocketSession::%s () - NO ERROR!\n", __FUNCTION__);

              if (mShutdown)
              {
                close ();
                //mrSocketServer.close ();
              }
              else
                readsome (buffer.buff (), buffer.size (), ::boost::bind (&MySocketSession::onReadBuffer, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
            }
            else
            {
              LOGMSG (LOW_LEVEL, "MySocketSession::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              close ();
            }
          }

        private:
          casock::util::Buffer buffer;
          bool mShutdown;
      };
    }
  }
}

#endif // __CASOCKLIB__EXAMPLES_PROACTOR_ASIO__MY_SOCKET_SESSION_H_
