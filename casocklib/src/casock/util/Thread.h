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
 * \file casock/util/Thread.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_UTIL_THREAD_H_
#define __CASOCKLIB__CASOCK_UTIL_THREAD_H_

#include <pthread.h>

#include "casock/util/types.h"

namespace casock {
  namespace util {
    class Thread
    {
      public:
        Thread ();
        virtual ~Thread ();

      private:
        static void* runThread (void *p);

      public:
        static const int setCancelState (const int &state);
        static const int disableCancel ();
        static void setSleepSecs (const uint32 &sleep_secs);

      private:
        void setTID (const uint64 &tid);
        virtual void run () = 0;

      protected:
        void sleep (const uint32 &sleep_secs = 0) const;
        void cancellationPoint () const;

      public:
        virtual void start ();
        void join () const;
        virtual void cancel () const;
        void kill (int32 &signal) const;
#ifdef USE_MEM_SIZE
        virtual const uint64 getMemSize () const;
#endif

      private:
        static uint32 ms_sleep_secs;

      private:
        pthread_t m_pthread;
        pthread_attr_t m_pthread_attr;
        uint64 m_tid;

      public:
        static const uint8 SLEEP_SECS = 1;
    };
  }
}


#endif // __CASOCKLIB__CASOCK_UTIL_THREAD_H_
