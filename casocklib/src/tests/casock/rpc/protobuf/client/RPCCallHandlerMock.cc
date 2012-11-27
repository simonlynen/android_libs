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
 * \file tests/casock/rpc/protobuf/client/RPCCallHandlerMock.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "tests/casock/rpc/protobuf/client/RPCCallHandlerMock.h"
#include "tests/casock/rpc/protobuf/client/RPCCallHandlerFactoryMock.h"
//#include "casock/util/Logger.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace protobuf {
        namespace client {
          RPCCallHandlerMock::~RPCCallHandlerMock ()
          {
            RPCCallHandlerFactoryMock::handlers.remove (this);
          }

          void RPCCallHandlerMock::run ()
          {
            //LOGMSG (NO_DEBUG, "%s\n", __PRETTY_FUNCTION__);
            //RPCCallHandlerFactoryMock::handlers.push_back (this);
          }

          void RPCCallHandlerMock::start ()
          {
            //LOGMSG (NO_DEBUG, "%s\n", __PRETTY_FUNCTION__);
            RPCCallHandlerFactoryMock::handlers.push_back (this);
          }

          void RPCCallHandlerMock::cancel () const
          {
            //LOGMSG (NO_DEBUG, "%s\n", __PRETTY_FUNCTION__);
          }
        }
      }
    }
  }
}
