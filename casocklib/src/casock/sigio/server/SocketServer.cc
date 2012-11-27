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
 * \file casock/sigio/server/SocketServer.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/server/SocketServer.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>

#include "casock/util/Logger.h"
#include "casock/server/CASServerException.h"

namespace casock {
  namespace sigio {
    namespace server {
      SocketServer::SocketServer (casock::sigio::base::Dispatcher& rDispatcher, const unsigned int& port) : casock::sigio::base::Socket (rDispatcher, port)
      {
        m_addr.sin_addr.s_addr  = INADDR_ANY;
        m_listening             = false;
      }

      void SocketServer::listen ()
      {
        LOGMSG (HIGH_LEVEL, "SocketServer::%s ()\n", __FUNCTION__);

        if (m_fd > 0)
        {
          if (bind (m_fd, (struct sockaddr *) &m_addr, sizeof(struct sockaddr_in)) == 0) 
          {
            if (::listen (m_fd, SOMAXCONN) == 0)
              m_listening = true;
            else
              throw (casock::server::CASServerException (strerror (errno)));
          }
          else
            throw (casock::server::CASServerException (strerror (errno)));
        }
        else
          throw (casock::server::CASServerException ("invalid file descriptor"));
      }

      void SocketServer::close ()
      {
        if (m_listening)
        {
          FileDescriptor::close ();
          m_listening = false;
        }
      }
    }
  }
}
