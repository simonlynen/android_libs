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
 * \file examples/proactor/asio/MySocketClient.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__EXAMPLES_PROACTOR_ASIO__MY_SOCKET_CLIENT_H_
#define __CASOCKLIB__EXAMPLES_PROACTOR_ASIO__MY_SOCKET_CLIENT_H_

#include <boost/bind.hpp>

#include "casock/util/Logger.h"
#include "casock/util/Buffer.h"
#include "casock/proactor/asio/base/Communicator.h"
#include "casock/proactor/asio/client/SocketClient.h"

namespace examples {
  namespace proactor {
    namespace asio {
      class MySocketClient : public casock::proactor::asio::client::SocketClient
      {
        public:
          MySocketClient (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const std::string& host, const std::string& port)
            : casock::proactor::asio::client::SocketClient (rAsyncProcessor, host, port), mCommunicator (this)
          {
            LOGMSG (LOW_LEVEL, "MySocketClient::MySocketClient () - host [%s], port [%s]\n", host.c_str (), port.c_str ());
          }

        protected:
          void onConnect ()
          {
            LOGMSG (LOW_LEVEL, "MySocketClient::%s ()\n", __FUNCTION__);
            mCommunicator.write ("HELLO", 6, ::boost::bind (&MySocketClient::onSentBuffer, this, ::asio::placeholders::error));
          }

          void onConnectionFailure ()
          {
            LOGMSG (LOW_LEVEL, "MySocketClient::%s ()\n", __FUNCTION__);
          }

          void onSentBuffer (const ::asio::error_code& error)
          {
            if (! error)
            {
              LOGMSG (LOW_LEVEL, "MySocketClient::%s () - NO ERROR!\n", __FUNCTION__);
              mCommunicator.readsome (mBuffer.buff (), mBuffer.size (), ::boost::bind (&MySocketClient::onReadBuffer, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
            }
            else
            {
              LOGMSG (LOW_LEVEL, "MySocketClient::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              close ();
            }
          }

          void onReadBuffer (const ::asio::error_code& error, const size_t& bytes_transferred)
          {
            LOGMSG (LOW_LEVEL, "MySocketClient::%s () - bytes_transferred [%zu], mBuffer [%s]\n", __FUNCTION__, bytes_transferred, mBuffer.data ());
            mCommunicator.write ("shutdown", 8, ::boost::bind(&MySocketClient::onSentShutdown, this, ::asio::placeholders::error));
          }

          void onSentShutdown (const ::asio::error_code& error)
          {
            if (! error)
            {
              LOGMSG (LOW_LEVEL, "MySocketClient::%s () - NO ERROR!\n", __FUNCTION__);
              mCommunicator.readsome (mBuffer.buff (), mBuffer.size (), ::boost::bind (&MySocketClient::onReadShutdownResponse, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
            }
            else
            {
              LOGMSG (LOW_LEVEL, "MySocketClient::%s () - error [%s]\n", __FUNCTION__, error.message ().c_str ());
              close ();
            }
          }

          void onReadShutdownResponse (const ::asio::error_code& error, const size_t& bytes_transferred)
          {
            LOGMSG (LOW_LEVEL, "MySocketClient::%s () - bytes_transferred [%zu], mBuffer [%s]\n", __FUNCTION__, bytes_transferred, mBuffer.data ());
            close ();
          }

        private:
          casock::util::Buffer                        mBuffer;
          casock::proactor::asio::base::Communicator  mCommunicator;
      };
    }
  }
}

#endif // __CASOCKLIB__EXAMPLES_PROACTOR_ASIO__MY_SOCKET_CLIENT_H_
