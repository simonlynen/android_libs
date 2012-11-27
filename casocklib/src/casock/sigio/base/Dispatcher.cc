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
 * \file casock/sigio/base/Dispatcher.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/base/Dispatcher.h"

#include "casock/util/Logger.h"
#include "casock/sigio/base/Handler.h"
#include "casock/base/CASException.h"

namespace casock {
  namespace sigio {
    namespace base {
      //    struct sigaction Dispatcher::m_sigaction;
      //    struct sigaction Dispatcher::m_sigaction2;
      Dispatcher* Dispatcher::mpDispatcher = NULL;

      sigset_t Dispatcher::m_mask;
      sigset_t Dispatcher::m_oldmask;

      Dispatcher::~Dispatcher ()
      {
        unordered_map<int, Handler*>::const_iterator it;
        unordered_map<int, Handler*>::const_iterator itEnd = mFDHandlerHash.end ();

        for (it = mFDHandlerHash.begin (); it != itEnd; ++it)
        {
          close (it->first);
          delete it->second;
        }

        mFDHandlerHash.clear ();
      }

      Dispatcher* Dispatcher::getInstance ()
      {
        if (! mpDispatcher)
          mpDispatcher = new Dispatcher ();

        return mpDispatcher;
      }

      void Dispatcher::initialize ()
      {
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s ()\n", __FUNCTION__);

        struct sigaction act_SIGIO;

        /*
         * If SA_SIGINFO is specified in sa_flags, then sa_sigaction (instead of sa_handler) specifies the signal-handling function for signum.
         * This function receives the signal number as its first argument, a pointer to a siginfo_t as its second argument and a pointer to a ucontext_t (cast to void *) as its third argument.
         */
        act_SIGIO.sa_sigaction  = Dispatcher::func_sigaction;

        /*
         * sa_flags specifies a set of flags which modify the behavior of the signal
         * SA_SIGINFO (since Linux 2.2):
         *   The signal handler takes 3 arguments, not one.
         *   In this case, sa_sigaction should be set instead of sa_handler.
         *   This flag is only meaningful when establishing a signal handler.
         */
        act_SIGIO.sa_flags      = SA_SIGINFO;

        /*
         * sa_mask specifies a mask of signals which should be blocked (i.e., added to the signal mask of the thread in which the signal handler is invoked) during execution of the signal handler.
         * In addition, the signal which triggered the handler will be blocked, unless the SA_NODEFER flag is used.
         * sigemptyset() initializes the signal set given by set to empty, with all signals excluded from the set.
         */
        sigemptyset (&(act_SIGIO.sa_mask));

        /*
         * The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.
         * SIGIO: I/O now possible (4.2BSD)
         */
        sigaction (SIGIO, &act_SIGIO, NULL);
        //      sigaction (SIGURG, &act_SIGIO, NULL);

        struct sigaction act_SIGALARM;
        act_SIGALARM.sa_handler = Dispatcher::func_handler;
        act_SIGALARM.sa_flags   = 0;
        sigemptyset (&(act_SIGALARM.sa_mask));
        sigaction (SIGALRM, &act_SIGALARM, NULL);

        sigemptyset (&m_mask);
        sigaddset (&m_mask, SIGIO);
        sigprocmask (SIG_BLOCK, &m_mask, &m_oldmask);
      }

      void Dispatcher::destroy ()
      {
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s ()\n", __FUNCTION__);

        if (mpDispatcher)
          delete mpDispatcher;

        mpDispatcher = NULL;
      }

      void Dispatcher::func_sigaction (int signum, siginfo_t* p_siginfo, void* p_data)
      {
        LOGMSG (MEDIUM_LEVEL, "Dispatcher::%s () - signum [%d], fd [%d]\n", __FUNCTION__, signum, p_siginfo->si_fd);
        Dispatcher::getInstance ()->handle (signum, p_siginfo, p_data);
      }

      void Dispatcher::func_handler (int signum)
      {
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - signum [%d]\n", __FUNCTION__, signum);
        Dispatcher::getInstance ()->deactivate ();
      }

      void Dispatcher::handle (int signum, siginfo_t* p_siginfo, void* p_data)
      {
        int& fd = p_siginfo->si_fd;

        if (mFDHandlerHash.find (fd) != mFDHandlerHash.end ())
        {
          if (mFDHandlerHash [fd])
            mFDHandlerHash [fd]->handle ();
          else
            LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - pHandler of fd [%d] not found!\n", __FUNCTION__, fd);
        }
        else
          LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - fd [%d] not found!\n", __FUNCTION__, fd);
      }

      void Dispatcher::registerHandler (const int& fd, Handler* pHandler)
      {
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - fd [%d]\n", __FUNCTION__, fd);

        if (mFDHandlerHash.find (fd) != mFDHandlerHash.end ())
          throw (casock::base::CASException ("file descriptor already in use"));

        mFDHandlerHash [fd] = pHandler;
      }

      void Dispatcher::unregisterHandler (const int& fd)
      {
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - fd [%d]\n", __FUNCTION__, fd);

        if (mFDHandlerHash.find (fd) == mFDHandlerHash.end ())
          throw (casock::base::CASException ("file descriptor not found"));

        mFDHandlerHash.erase (fd);
      }

      void Dispatcher::wait (const time_t& timeout)
      {
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - begin\n", __FUNCTION__);

        m_active = true;

        /*
           sigset_t mask, oldmask;
           sigemptyset (&mask);
           sigaddset (&mask, SIGIO);
           sigprocmask (SIG_BLOCK, &mask, &oldmask);
         */

        while (m_active)
        {
          LOGMSG (MEDIUM_LEVEL, "Dispatcher::%s () - pause...\n", __FUNCTION__);
          alarm (timeout);

          /*
             sigset_t sigio_set;
             sigemptyset(&sigio_set);
             sigaddset(&sigio_set, SIGIO);
             sigprocmask (SIG_UNBLOCK, &sigio_set, NULL);

             pause ();
           */
          sigsuspend (&m_oldmask);
          LOGMSG (MEDIUM_LEVEL, "Dispatcher::%s () - returning from pause!\n", __FUNCTION__);
        }

        //      sigprocmask (SIG_UNBLOCK, &mask, NULL);

        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - end\n", __FUNCTION__);
      }

      void Dispatcher::waitForever ()
      {
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - begin\n", __FUNCTION__);

        m_active = true;

        /*
           sigset_t mask, oldmask;
           sigemptyset (&mask);
           sigaddset (&mask, SIGIO);
           sigprocmask (SIG_BLOCK, &mask, &oldmask);
         */

        while (m_active)
        {
          LOGMSG (MEDIUM_LEVEL, "Dispatcher::%s () - pause...\n", __FUNCTION__);

          /*
             sigset_t sigio_set;
             sigemptyset(&sigio_set);
             sigaddset(&sigio_set, SIGIO);
             sigprocmask (SIG_UNBLOCK, &sigio_set, NULL);
          //raise (SIGIO);

          pause ();
           */
          sigsuspend (&m_oldmask);
          LOGMSG (MEDIUM_LEVEL, "Dispatcher::%s () - returning from pause!\n", __FUNCTION__);
        }

        //      sigprocmask (SIG_UNBLOCK, &mask, NULL);

        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - end\n", __FUNCTION__);
      }
    }
  }
}
