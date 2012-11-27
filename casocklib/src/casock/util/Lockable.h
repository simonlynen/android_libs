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
 * \file casock/util/Lockable.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_UTIL__LOCKABLE_H_
#define __CASOCKLIB__CASOCK_UTIL__LOCKABLE_H_

#include <pthread.h>
#include <sys/time.h>

#include "casock/util/types.h"

namespace casock {
  namespace util {
    class Lockable
    {
      protected:
        Lockable (const int& type = PTHREAD_MUTEX_DEFAULT);
        virtual ~Lockable ();

      public:
        void lock () const;
        void unlock () const;
        bool tryLock () const;

        int cond_wait (const uint32& timeout = 0) const;
        int cond_wait (const struct timeval& timeout) const;
        int cond_wait (const struct timespec& timeout) const;
        void cond_broadcast () const;
        void cond_signal () const;

#ifdef USE_MEM_SIZE
      public:
        virtual const uint64 getMemSize () const;
#endif

      private:
        pthread_mutexattr_t     m_mutex_attr;
        mutable pthread_mutex_t m_mutex;
        mutable pthread_cond_t  m_cond;
    };
  }
}


#endif // __CASOCKLIB__CASOCK_UTIL__LOCKABLE_H_
