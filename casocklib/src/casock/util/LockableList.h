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
 * \file casock/util/LockableList.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_UTIL__LOCKABLE_LIST_H_
#define __CASOCKLIB__CASOCK_UTIL__LOCKABLE_LIST_H_

#include <list>

#include "casock/util/Lockable.h"
#include "casock/util/SafeLock.h"

namespace casock {
  namespace util {
    template<typename _Tp>
      class LockableList : private std::list<_Tp>, private Lockable
      {
        public:
          const bool empty () const
          {
            SafeLock lock (*this);
            return std::list<_Tp>::empty ();
          }

          const size_t size () const
          {
            SafeLock lock (*this);
            return std::list<_Tp>::size ();
          }

          void push_back (const _Tp& _value)
          {
            SafeLock lock (*this);
            std::list<_Tp>::push_back (_value);
          }

          void remove (const _Tp& _value)
          {
            SafeLock lock (*this);
            std::list<_Tp>::remove (_value);
          }
      };
  }
}

#endif // __CASOCKLIB__CASOCK_UTIL__LOCKABLE_LIST_H_
