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
 * \file casock/proactor/asio/base/Communicator.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__COMMUNICATOR_H_
#define __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__COMMUNICATOR_H_

#include <sstream>
using std::stringstream;

#include "casock/proactor/asio/base/SocketChannel.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        class Communicator
        {
          public:
            Communicator (SocketChannel* const pChannel)
             : mpChannel (pChannel)
            { };

          public:
            template<typename ReadHandler>
              void read (char* buffer, const size_t& size, ReadHandler handler)
              {
                mpChannel->read (buffer, size, handler);
              }

            template<typename ReadHandler>
              void readsome (char* buffer, const size_t& size, ReadHandler handler)
              {
                mpChannel->readsome (buffer, size, handler);
              }

            template<typename _Type, typename ReadHandler>
              void read (_Type& buffer, ReadHandler handler)
              {
                mpChannel->read (buffer, handler);
              }


            template<typename _WriteHandler>
              void write (const char* buffer, const size_t& size, _WriteHandler handler)
              {
                mpChannel->write (buffer, size, handler);
              }

            template<typename _WriteHandler>
              void write (const stringstream& buffer, _WriteHandler handler)
              {
                mpChannel->write (buffer.str ().c_str (), buffer.str ().size (), handler);
              }

            template<typename _Type, typename WriteHandler>
              void write (const _Type& buffer, WriteHandler handler)
              {
                mpChannel->write (buffer, handler);
              }

          private:
            SocketChannel* const mpChannel;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__COMMUNICATOR_H_
