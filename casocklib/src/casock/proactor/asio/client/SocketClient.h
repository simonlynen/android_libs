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
 * \file casock/proactor/asio/client/SocketClient.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_PROACTOR_ASIO_CLIENT__SOCKET_CLIENT_H_
#define __CASOCKLIB__CASOCK_PROACTOR_ASIO_CLIENT__SOCKET_CLIENT_H_

#include <string>

#include "casock/proactor/asio/base/SocketChannel.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace client {
        class SocketClient : protected casock::proactor::asio::base::SocketChannel
        {
          public:
            SocketClient (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor, const std::string& host, const std::string& port);

          private:
            void handle_resolve (const ::asio::error_code& error, ::asio::ip::tcp::resolver::iterator it_endpoint);
            void handle_connect (const ::asio::error_code& error, ::asio::ip::tcp::resolver::iterator it_endpoint);

          protected:
            virtual void onConnect () = 0;
            virtual void onConnectionFailure () = 0;

          public:
            void syncConnect ();
            void asyncConnect ();
            using casock::proactor::asio::base::SocketChannel::close;

          private:
            ::asio::ip::tcp::resolver         m_resolver;
            ::asio::ip::tcp::resolver::query  m_query;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_PROACTOR_ASIO_CLIENT__SOCKET_CLIENT_H_
