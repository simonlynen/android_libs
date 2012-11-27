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
 * \file casock/util/LockableQueue.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_UTIL__LOCKABLE_QUEUE_H_
#define __CASOCKLIB__CASOCK_UTIL__LOCKABLE_QUEUE_H_

#include <queue>

#include "casock/util/Lockable.h"
#include "casock/util/SafeLock.h"

namespace casock {
  namespace util {
    template<typename _Tp>
      class LockableQueue : private std::queue<_Tp>, private Lockable
      {
        public:
          const bool empty () const
          {
            SafeLock lock (*this);
            return std::queue<_Tp>::empty ();
          }

          const size_t size () const
          {
            SafeLock lock (*this);
            return std::queue<_Tp>::size ();
          }

          void push (const _Tp& _value)
          {
            SafeLock lock (*this);
            std::queue<_Tp>::push (_value);
            cond_signal ();
          }

          _Tp pop ()
          {
            SafeLock lock (*this);

            while (std::queue<_Tp>::empty ())
              cond_wait ();

            _Tp _value = std::queue<_Tp>::front ();
            std::queue<_Tp>::pop ();

            return _value;
          }

          /*
          _Tp& front ()
          {
            SafeRLock lock (*this);
            return std::queue<_Tp>::front ();
          }

          _Tp& back ()
          {
            SafeRLock lock (*this);
            return std::queue<_Tp>::back ();
          }

          void pop ()
          {
            SafeLock lock (*this);
            std::queue<_Tp>::pop ();
          }
          */
      };
  }
}

#endif // __CASOCKLIB__CASOCK_UTIL__LOCKABLE_QUEUE_H_
