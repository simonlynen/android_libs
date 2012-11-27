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
 * \file casock/sigio/base/FileDescriptor.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/base/FileDescriptor.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "casock/base/CASException.h"
#include "casock/util/SafeLock.h"
#include "casock/util/Logger.h"

namespace casock {
  namespace sigio {
    namespace base {
      FileDescriptor::FileDescriptor (const int& fd) : m_fd (fd)
      {
        if (m_fd == -1)
          throw (casock::base::CASException (strerror (errno)));
      }

      void FileDescriptor::write (const char* buff, const size_t& len) const
      {
        casock::util::SafeLock lock (*this);
        LOGMSG (MEDIUM_LEVEL, "FileDescriptor::%s () - len [%zu]\n", __FUNCTION__, len);
        ::write (m_fd, buff, len);
        ::fsync (m_fd);
      }

      const ssize_t FileDescriptor::read (char* buff, const size_t& len) const
      {
        casock::util::SafeLock lock (*this);
        ssize_t s = ::read (m_fd, buff, len);
        LOGMSG (MEDIUM_LEVEL, "FileDescriptor::%s () - len [%zu], s [%zd]\n", __FUNCTION__, len, s);
        return s;
      }

      void FileDescriptor::close () const
      {
        casock::util::SafeLock lock (*this);
        LOGMSG (LOW_LEVEL, "FileDescriptor::%s ()\n", __FUNCTION__);
        ::close (m_fd);
      }
    }
  }
}
