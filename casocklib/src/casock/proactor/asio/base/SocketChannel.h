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
 * \file casock/proactor/asio/base/SocketChannel.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__SOCKET_CHANNEL_H_
#define __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__SOCKET_CHANNEL_H_

#include <asio.hpp>
#include "casock/base/CASClosedConnectionException.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        class AsyncProcessor;

        class SocketChannel
        {
          protected:
            SocketChannel (casock::proactor::asio::base::AsyncProcessor& rAsyncProcessor);
            virtual ~SocketChannel ()
            {
              close ();
            }

          private:
            /*!
             * asynchronous read:
             *
             * ReadHandler is a handler in the same format expected by ::asio::async_read,
             * i.e., ::boost::bind (&Class::method, object, param1, param2, ...),
             * ex.: ::boost::bind (&MySocketChannel::my_handle, this, ::asio::placeholders::error)
             */

            template<typename ReadHandler>
              void asyncRead (char* buffer, const size_t& size, ReadHandler handler);

            /*!
             * asynchronous read some:
             *
             * ReadHandler is a handler in the same format expected by ::asio::ip::tcp::socket::async_read_some
             * i.e., ::boost::bind (&Class::method, object, param1, param2, ...),
             * ex.: ::boost::bind (&MySocketChannel::my_handle, this, ::asio::placeholders::error, ::asio::placeholders::bytes_transferred)
             */

            template<typename ReadHandler>
              void asyncReadSome (char* buffer, const size_t& size, ReadHandler handler);

            /*!
             * asynchronous write:
             *
             * WriteHandler is a handler in the same format expected by ::asio::async_write,
             * i.e., ::boost::bind (&Class::method, object, param1, param2, ...),
             * ex.: ::boost::bind (&MySocketChannel::my_handle, this, ::asio::placeholders::error)
             */

            template<typename WriteHandler>
              void asyncWrite (const char* buffer, const size_t& size, WriteHandler handler);

          public:
            /*!
             * read data of specific type
             */

            template<typename _Type, typename ReadHandler>
              void read (_Type& buffer, ReadHandler handler);

            /*!
             * read raw data of specific size
             */

            template<typename ReadHandler>
              void read (char* buffer, const size_t& size, ReadHandler handler);

            /*!
             * read some raw data into a maximum size buffer
             */

            template<typename ReadHandler>
              void readsome (char* buffer, const size_t& size, ReadHandler handler);

            /*!
             * write data of specific type
             */

            template<typename _Type, typename WriteHandler>
              void write (const _Type& buffer, WriteHandler handler);

            /*!
             * write raw data of specific size
             */

            template<typename WriteHandler>
              void write (const char* buffer, const size_t& size, WriteHandler handler);

          protected:
            virtual void close () { m_socket.close (); }

          protected:
            ::asio::ip::tcp::socket& socket () { return m_socket; }

          public:
            const bool isConnected () const { return m_socket.is_open (); }

          protected:
            ::asio::ip::tcp::socket m_socket;
        };

        /*
         * template definitions
         */

        template<typename ReadHandler>
          void SocketChannel::asyncRead (char* buffer, const size_t& size, ReadHandler handler)
          {
            if (m_socket.is_open ())
            {
              ::asio::async_read (
                  m_socket, ::asio::buffer (buffer, size),
                  ::asio::transfer_at_least (size),
                  handler
                  );
            }
            else
            {
              throw (casock::base::CASClosedConnectionException ("socket is not open"));
            }
          }

        template<typename ReadHandler>
          void SocketChannel::asyncReadSome (char* buffer, const size_t& size, ReadHandler handler)
          {
            if (m_socket.is_open ())
            {
              m_socket.async_read_some (
                  ::asio::buffer (buffer, size),
                  handler
                  );
            }
            else
            {
              throw (casock::base::CASClosedConnectionException ("socket is not open"));
            }
          }

        template<typename WriteHandler>
          void SocketChannel::asyncWrite (const char* buffer, const size_t& size, WriteHandler handler)
          {
            if (m_socket.is_open ())
            {
              ::asio::async_write (
                  m_socket,
                  ::asio::buffer (buffer, size),
                  handler
                  );
            }
            else
            {
              throw (casock::base::CASClosedConnectionException ("socket is not open"));
            }
          }

        template<typename _Type, typename ReadHandler>
          void SocketChannel::read (_Type& buffer, ReadHandler handler)
          {
            asyncRead (reinterpret_cast<char*> (&buffer), sizeof (_Type), handler);
          }

        template<typename ReadHandler>
          void SocketChannel::read (char* buffer, const size_t& size, ReadHandler handler)
          {
            asyncRead (buffer, size, handler);
          }

        template<typename ReadHandler>
          void SocketChannel::readsome (char* buffer, const size_t& size, ReadHandler handler)
          {
            asyncReadSome (buffer, size, handler);
          }

        template<typename _Type, typename WriteHandler>
          void SocketChannel::write (const _Type& buffer, WriteHandler handler)
          {
            asyncWrite (reinterpret_cast<const char*> (&buffer), sizeof (_Type), handler);
          }

        template<typename WriteHandler>
          void SocketChannel::write (const char* buffer, const size_t& size, WriteHandler handler)
          {
            asyncWrite (buffer, size, handler);
          }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__SOCKET_CHANNEL_H_
