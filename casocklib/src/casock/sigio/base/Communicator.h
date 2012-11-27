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
 * \file casock/sigio/base/Communicator.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_SIGIO_BASE__COMMUNICATOR_H_
#define __CASOCKLIB__CASOCK_SIGIO_BASE__COMMUNICATOR_H_

#include <unistd.h>

#include <sstream>
using std::stringstream;

namespace casock {
  namespace sigio {
    namespace base {
      class FileDescriptor;

      class Communicator
      {
        public:
          Communicator (const FileDescriptor* const pFD) : mpFD (pFD) { };

        public:
          virtual const ssize_t read (char* buffer, const size_t& len);
          virtual const ssize_t read (stringstream& buffer);
          virtual const ssize_t read (stringstream& buffer, const size_t& len);

          virtual void write (const char* buffer, const size_t& len);
          virtual void write (const stringstream& buffer);
          virtual void write (const int& buffer);
          virtual void write (const size_t& buffer);

        private:
          const FileDescriptor* const mpFD;
      };
    }
  }
}

#endif // __CASOCKLIB__CASOCK_SIGIO_BASE__COMMUNICATOR_H_
