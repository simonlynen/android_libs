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
 * \file casock/util/RWLockable.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/util/RWLockable.h"

#ifdef USE_MEM_SIZE
#include "casock/util/Logger.h"
#endif

namespace casock {
  namespace util {
    RWLockable::RWLockable ()
      : m_rwlock ()
    {
      pthread_rwlock_init (&m_rwlock, NULL) ;
    }

    RWLockable::~RWLockable ()
    {
      pthread_rwlock_destroy (&m_rwlock) ;
    }

    void RWLockable::readLock () const
    {
      pthread_rwlock_rdlock (&m_rwlock);
    }

    void RWLockable::readUnlock () const
    {
      pthread_rwlock_unlock (&m_rwlock);
    }

    bool RWLockable::readTryLock () const
    {
      return (pthread_rwlock_tryrdlock (&m_rwlock) == 0);
    }

    void RWLockable::writeLock () const
    {
      pthread_rwlock_wrlock (&m_rwlock);
    }

    void RWLockable::writeUnlock () const
    {
      pthread_rwlock_unlock (&m_rwlock);
    }

    bool RWLockable::writeTryLock () const
    {
      return (pthread_rwlock_trywrlock (&m_rwlock) == 0);
    }

#ifdef USE_MEM_SIZE
    const uint64 RWLockable::getMemSize () const
    {
      LOGMSG (MEDIUM_LEVEL, "RWLockable::%s () - [%p]\n", __FUNCTION__, this);
      uint64 size = sizeof (pthread_rwlock_t);
      LOGMSG (MEDIUM_LEVEL, "RWLockable::%s () - [%u]\n", __FUNCTION__, size);

      return size;
    }
#endif
  }
}
