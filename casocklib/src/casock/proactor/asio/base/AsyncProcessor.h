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
 * \file casock/proactor/asio/base/AsyncProcessor.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__ASYNC_PROCESSOR_H_
#define __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__ASYNC_PROCESSOR_H_

#include <asio.hpp>

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        class AsyncProcessor
        {
          public:
            static AsyncProcessor* getInstance ();
            static void initialize ();
            static void destroy ();

          public:
            ::asio::io_service& service () { return m_service; }

          public:
            void run ();

          private:
            static AsyncProcessor* mpAsyncProcessor;

          private:
            ::asio::io_service m_service;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_PROACTOR_ASIO_BASE__ASYNC_PROCESSOR_H_
