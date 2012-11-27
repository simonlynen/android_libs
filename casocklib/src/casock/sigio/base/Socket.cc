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
 * \file casock/sigio/base/Socket.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/base/Socket.h"

#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace casock {
  namespace sigio {
    namespace base {
      Socket::Socket (Dispatcher& rDispatcher, const unsigned int& port)
        : FileDescriptor (socket (AF_INET, SOCK_STREAM, 0)), m_port (port)
      {
        bzero (&m_addr, sizeof (struct sockaddr_in));

        m_addr.sin_family = AF_INET;
        m_addr.sin_port   = htons (m_port);
      }
    }
  }
}
