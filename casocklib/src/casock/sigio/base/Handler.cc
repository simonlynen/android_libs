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
 * \file casock/sigio/base/Handler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/base/Handler.h"

#include <unistd.h>
#include <fcntl.h>

#include "casock/sigio/base/FileDescriptor.h"
#include "casock/sigio/base/Dispatcher.h"

namespace casock {
  namespace sigio {
    namespace base {
      Handler::Handler (Dispatcher& rDispatcher, const FileDescriptor* const pFileDescriptor) : mrDispatcher (rDispatcher), mpFileDescriptor (pFileDescriptor)
      {
        registerOnDispatcher ();
      }

      void Handler::registerOnDispatcher ()
      {
        const int& fd = mpFileDescriptor->fd ();

        fcntl (fd, F_SETOWN, getpid ());
        fcntl (fd, F_SETSIG, SIGIO);
        //      fcntl (fd, F_SETSIG, SIGURG);
        fcntl (fd, F_SETFL, fcntl (fd, F_GETFL) | O_NONBLOCK | O_ASYNC);

        mrDispatcher.registerHandler (fd, this);
      }

      void Handler::unregister ()
      {
        mrDispatcher.unregisterHandler (mpFileDescriptor->fd ());
      }
    }
  }
}
