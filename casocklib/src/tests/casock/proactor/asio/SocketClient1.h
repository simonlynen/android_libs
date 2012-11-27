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
 * \file tests/casock/proactor/asio/SocketClient1.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_CLIENT1_H_
#define __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_CLIENT1_H_

#include <boost/bind.hpp>
#include <sstream>
#include <iomanip>

#include "casock/util/Logger.h"
#include "casock/util/Buffer.h"
#include "casock/proactor/asio/base/Communicator.h"
#include "casock/proactor/asio/client/SocketClient.h"

namespace tests {
  namespace casock {
    namespace proactor {
      namespace asio {
        class SocketClient1 : public ::casock::proactor::asio::client::SocketClient
        {
          public:
            SocketClient1 (::casock::proactor::asio::base::AsyncProcessor* pAsyncProcessor, const std::string& host, const std::string& port, SocketClient* pParent = NULL)
              : ::casock::proactor::asio::client::SocketClient (*pAsyncProcessor, host, port), mpAsyncProcessor (pAsyncProcessor), mCommunicator (this), mpParent (pParent)
            {
              mMyID       = ++SocketClient1::mID;
              mMessageID  = 0;
            }

            virtual ~SocketClient1 ()
            {
              close ();

              if (mpParent)
                delete mpParent;
            }

          protected:
            void onConnect ()
            {
              std::stringstream ss;
              ss << "HELLO, my ID is " << std::setfill ('0') << std::setw (4) << mMyID << " and the message ID is " << std::setfill ('0') << std::setw (4) << ++mMessageID;
              mCommunicator.write (ss.str ().c_str (), ss.str ().size (), ::boost::bind (&SocketClient1::onSentBuffer, this, ::asio::placeholders::error));
              SocketClient1* pClient = new SocketClient1 (mpAsyncProcessor, "localhost", "2000", this);
              pClient->asyncConnect ();
              usleep (100000);
            }

            void onConnectionFailure ()
            {
              LOGMSG (LOW_LEVEL, "SocketClient1::%s () - mMyID [%04u]\n", __FUNCTION__, mMyID);
              close ();
              delete this;
            }

            void onSentBuffer (const ::asio::error_code& error)
            {
              if (! error)
              {
                LOGMSG (LOW_LEVEL, "SocketClient1::%s () - mMyID [%04u], NO ERROR!\n", __FUNCTION__, mMyID);
                mCommunicator.readsome (mBuffer.buff (), mBuffer.size (), ::boost::bind (&SocketClient1::onReadBuffer, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
              }
              else
              {
                LOGMSG (LOW_LEVEL, "SocketClient1::%s () - mMyID [%04u], error [%s]\n", __FUNCTION__, mMyID, error.message ().c_str ());
                close ();
                delete this;
              }
            }

            void onReadBuffer (const ::asio::error_code& error, const size_t& bytes_transferred)
            {
              std::stringstream ss;
              ss << "HELLO, my ID is " << std::setfill ('0') << std::setw (4) << mMyID << " and the message ID is " << std::setfill ('0') << std::setw (4) << ++mMessageID;
              mCommunicator.write (ss.str ().c_str (), ss.str ().size (), ::boost::bind (&SocketClient1::onSentBuffer, this, ::asio::placeholders::error));
            }

          private:
            ::casock::proactor::asio::base::AsyncProcessor* mpAsyncProcessor;
            ::casock::proactor::asio::base::Communicator    mCommunicator;
            ::casock::util::Buffer                          mBuffer;
            SocketClient*                                 mpParent;

            uint32 mMyID;
            uint32 mMessageID;

            static uint32 mID;
        };

        uint32 SocketClient1::mID = 0;
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_PROACTOR_ASIO__SOCKET_CLIENT1_H_
