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
 * \file casock/sigio/base/Dispatcher.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_SIGIO_BASE__DISPATCHER_H_
#define __CASOCKLIB__CASOCK_SIGIO_BASE__DISPATCHER_H_

#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "casock/sigio/base/FDHandlerHash.h"

namespace casock {
  namespace sigio {
    namespace base {
      class Handler;

      class Dispatcher
      {
        protected:
          Dispatcher () : m_active (false) { }
          virtual ~Dispatcher ();

        public:
          static Dispatcher* getInstance ();
          static void initialize ();
          static void destroy ();

        public:
          static void func_sigaction (int signum, siginfo_t* p_siginfo, void* p_data);
          static void func_handler (int signum);

        private:
          void handle (int signum, siginfo_t* p_siginfo, void* p_data);

        public:
          void registerHandler (const int& fd, Handler* pHandler);
          void unregisterHandler (const int& fd);
          void deactivate () { m_active = false; }

        public:
          void wait (const time_t& timeout = 0);
          void waitForever ();

        private:
          bool m_active;

        protected:
          static Dispatcher*  mpDispatcher;
          FDHandlerHash       mFDHandlerHash;

        private:
          static sigset_t m_mask;
          static sigset_t m_oldmask;
      };
    }
  }
}

#endif // __CASOCKLIB__CASOCK_SIGIO_BASE__DISPATCHER_H_
