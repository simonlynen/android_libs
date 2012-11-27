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
 * \file casock/sigio/server/SockAcceptorHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/server/SockAcceptorHandler.h"

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "casock/util/Logger.h"
#include "casock/sigio/base/FileDescriptor.h"

namespace casock {
  namespace sigio {
    namespace server {
      void SockAcceptorHandler::handle ()
      {
        LOGMSG (HIGH_LEVEL, "SockAcceptorHandler::%s () - begin\n", __FUNCTION__);

        struct sockaddr_in addr;
        socklen_t s = sizeof (addr);
        int fd = accept (mpFileDescriptor->fd (), (struct sockaddr *) &addr, &s);

        createHandler (fd);

        LOGMSG (HIGH_LEVEL, "SockAcceptorHandler::%s () - end\n", __FUNCTION__);
      }
    }
  }
}
