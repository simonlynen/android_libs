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
 * \file casock/rpc/sigio/protobuf/client/RPCChannel.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/sigio/protobuf/client/RPCChannel.h"

#include <google/protobuf/message.h>

#include "casock/util/Logger.h"
#include "casock/rpc/sigio/protobuf/base/RPCCommunicator.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"

namespace casock {
  namespace rpc {
    namespace sigio {
      namespace protobuf {
        namespace client {
          RPCChannel::RPCChannel (casock::rpc::sigio::protobuf::base::RPCCommunicator* pCommunicator) : mpCommunicator (pCommunicator)
          {
            LOGMSG (HIGH_LEVEL, "RPCChannel::RPCChannel ()\n");
          }

          void RPCChannel::RpcCall (const casock::rpc::protobuf::api::RpcRequest& request)
          {
            mpCommunicator->write (&request);
          }
        }
      }
    }
  }
}
