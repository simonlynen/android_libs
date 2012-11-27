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
 * \file casock/proactor/asio/base/AsyncProcessor.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "casock/util/Logger.h"

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        AsyncProcessor* AsyncProcessor::mpAsyncProcessor = NULL;

        AsyncProcessor* AsyncProcessor::getInstance ()
        {
          LOGMSG (HIGH_LEVEL, "AsyncProcessor::%s ()\n", __FUNCTION__);

          return mpAsyncProcessor;
        }

        void AsyncProcessor::initialize ()
        {
          LOGMSG (HIGH_LEVEL, "AsyncProcessor::%s ()\n", __FUNCTION__);

          if (! mpAsyncProcessor)
            mpAsyncProcessor = new AsyncProcessor ();
        }

        void AsyncProcessor::destroy ()
        {
          LOGMSG (HIGH_LEVEL, "AsyncProcessor::%s ()\n", __FUNCTION__);

          if (mpAsyncProcessor)
            delete mpAsyncProcessor;

          mpAsyncProcessor = NULL;
        }

        void AsyncProcessor::run ()
        {
          LOGMSG (LOW_LEVEL, "%s\n", __PRETTY_FUNCTION__);
          m_service.run ();
          LOGMSG (LOW_LEVEL, "%s - end\n", __PRETTY_FUNCTION__);
        }
      }
    }
  }
}
