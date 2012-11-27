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
 * \file casock/sigio/base/FileDescriptor.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_SIGIO_BASE__FILE_DESCRIPTOR_H_
#define __CASOCKLIB__CASOCK_SIGIO_BASE__FILE_DESCRIPTOR_H_

#include <unistd.h>

#include "casock/util/Lockable.h"

namespace casock {
  namespace sigio {
    namespace base {
      class FileDescriptor : private casock::util::Lockable
      {
        public:
          FileDescriptor (const int& fd = -1);

        public:
          const int& fd () const { return m_fd; }
          virtual void write (const char* buff, const size_t& len) const;
          const ssize_t read (char* buff, const size_t& len) const;
          virtual void close () const;

        protected:
          int m_fd;
      };
    }
  }
}

#endif // __CASOCKLIB__CASOCK_SIGIO_BASE__FILE_DESCRIPTOR_H_
