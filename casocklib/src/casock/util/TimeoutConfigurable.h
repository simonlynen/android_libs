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
 * \file casock/util/TimeoutConfigurable.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_UTIL__TIMEOUT_CONFIGURABLE_H_
#define __CASOCKLIB__CASOCK_UTIL__TIMEOUT_CONFIGURABLE_H_

#include <sys/time.h>

namespace casock {
  namespace util {
    class TimeoutConfigurable
    {
      public:
        TimeoutConfigurable ()
          : m_timeout ()
        {
          m_timeout.tv_sec = 0;
          m_timeout.tv_usec = 0;
        }

      public:
        inline void setTimeout (const struct timeval& timeout)
        {
          m_timeout = timeout;
        }

        inline const struct timeval& timeout () const
        {
          return m_timeout;
        }

        inline void setTimeoutInSeconds (const time_t& seconds)
        {
          m_timeout.tv_sec = seconds;
          m_timeout.tv_usec = 0;
        };

        inline void setTimeoutInUSeconds (const suseconds_t& useconds)
        {
          m_timeout.tv_sec = useconds / 1000000;
          m_timeout.tv_usec = useconds % 1000000;
        };

        inline const time_t timeoutInSeconds () const
        {
          return m_timeout.tv_sec;
        }

        inline const suseconds_t timeoutInUSeconds () const
        {
          return m_timeout.tv_usec + 1000000 * m_timeout.tv_sec;
        }

      private:
        struct timeval m_timeout;
    };
  }
}


#endif // __CASOCKLIB__CASOCK_UTIL__TIMEOUT_CONFIGURABLE_H_
