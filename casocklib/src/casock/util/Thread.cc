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
 * \file casock/util/Thread.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/util/Thread.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <unistd.h>
#include <signal.h>

#ifdef HAVE_SYS_SYSCALL_H
#include <sys/syscall.h>
#endif

#include <glog/logging.h>

#include "casock/util/Logger.h"

namespace casock {
  namespace util {
    uint32	Thread::ms_sleep_secs	= Thread::SLEEP_SECS;


    Thread::Thread ()
			: m_pthread (0), m_pthread_attr ()
    {
      m_tid = 0;

      pthread_attr_init (&m_pthread_attr);
      pthread_attr_setdetachstate(&m_pthread_attr, PTHREAD_CREATE_JOINABLE);
    }

    Thread::~Thread ()
    {
      LOGMSG (HIGH_LEVEL, "Thread::~Thread () - p [%p]\n", this);

      pthread_attr_destroy (&m_pthread_attr);
    }

    void* Thread::runThread (void *p)
    {
      LOGMSG (HIGH_LEVEL, "Thread::%s ()\n", __FUNCTION__);

      Thread *pThread = static_cast<Thread *>(p);

#ifdef HAVE_SYS_SYSCALL_H
      pThread->setTID (syscall (__NR_gettid));
#else
      pThread->setTID (syscall (Logger::GETTID_SYSCALL_ID));
#endif

      pThread->run ();

      pthread_exit (0);

      return NULL;
    }

    /*
    void Thread::run ()
    {
      LOGMSG (NO_DEBUG, "Thread::%s - p [%p]\n", __FUNCTION__, this);
    }
    */

    void Thread::setTID (const uint64 &tid)
    {
      m_tid = tid;

      LOGMSG (HIGH_LEVEL, "Thread::%s (%ld)\n", __FUNCTION__, m_tid);
    }

    void Thread::sleep (const uint32 &sleep_secs) const
    {
      LOGMSG (HIGH_LEVEL, "Thread::%s () - p[%p]\n", __FUNCTION__, this);

      int oldstate = Thread::setCancelState (PTHREAD_CANCEL_DISABLE);

      if (sleep_secs)
        sleep (sleep_secs);
      else
        sleep (Thread::ms_sleep_secs);

      Thread::setCancelState (oldstate);
    }

    const int Thread::setCancelState (const int &state)
    {
      int oldstate;

      switch (state)
      {
        case PTHREAD_CANCEL_ENABLE:
          pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, &oldstate);
          pthread_testcancel ();
          break;

        case PTHREAD_CANCEL_DISABLE:
          pthread_testcancel ();
          pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &oldstate);
          break;

        default:
          break;
      }

      return oldstate;
    }

    const int Thread::disableCancel ()
    {
      pthread_testcancel ();
      int oldstate = pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &oldstate);

      return oldstate;
    }

    void Thread::cancellationPoint () const
    {
      pthread_testcancel ();
    }

    void Thread::start ()
    {
      LOGMSG (HIGH_LEVEL, "Thread::%s () - [%p]\n", __FUNCTION__, this);

      pthread_create (&m_pthread, &m_pthread_attr, Thread::runThread, this);
    }

    void Thread::join () const
    {
      LOGMSG (HIGH_LEVEL, "Thread::%s () - [%p]\n", __FUNCTION__, this);

      pthread_join (m_pthread, NULL);
    }

    void Thread::cancel () const
    {
      LOGMSG (HIGH_LEVEL, "Thread::%s () - [%p]\n", __FUNCTION__, this);

      pthread_cancel (m_pthread);
    }

    void Thread::kill (int32 &signal) const
    {
      LOGMSG (HIGH_LEVEL, "Thread::%s () - [%p]\n", __FUNCTION__, this);

      pthread_kill (m_pthread, signal);
    }

    void Thread::setSleepSecs (const uint32 &sleep_secs)
    {
      LOGMSG (HIGH_LEVEL, "Thread::%s () - [%u]\n", __FUNCTION__, sleep_secs);

      Thread::ms_sleep_secs = sleep_secs;
    }

#ifdef USE_MEM_SIZE
    const uint64 Thread::getMemSize () const
    {
      uint64 size = 0;

      size += sizeof (pthread_t);
      size += sizeof (pthread_attr_t);
      size += sizeof (uint64);
      size += sizeof (uint32);

      LOGMSG (HIGH_LEVEL, "Thread::%s () - [%u]\n", __FUNCTION__, size);

      return size;
    }
#endif
  }
}
