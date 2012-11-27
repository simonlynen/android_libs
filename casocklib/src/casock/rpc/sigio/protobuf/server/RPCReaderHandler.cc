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
 * \file casock/rpc/sigio/protobuf/server/RPCReaderHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/sigio/protobuf/server/RPCReaderHandler.h"

#include "casock/sigio/base/FileDescriptor.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/util/Logger.h"
#include "casock/rpc/base/CASRPCUnfinishedMessageException.h"
#include "casock/rpc/protobuf/server/RPCCall.h"
#include "casock/rpc/protobuf/server/RPCCallQueue.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"

namespace casock {
  namespace rpc {
    namespace sigio {
      namespace protobuf {
        namespace server {
          RPCReaderHandler::RPCReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const int& fd, RPCCallQueue& rCallQueue) : Handler (rDispatcher, new casock::sigio::base::FileDescriptor (fd)), mCommunicator (mpFileDescriptor), mrCallQueue (rCallQueue)
          {
            //len = 0;
          };

          void RPCReaderHandler::handle ()
          {
            LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - treating request...\n", __FUNCTION__);

            try
            {
              casock::rpc::protobuf::api::RpcRequest* request = static_cast<casock::rpc::protobuf::api::RpcRequest *>(mCommunicator.read ());
              LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - request received: %d bytes - id [%u], operation [%s]\n", __FUNCTION__, request->ByteSize (), request->id (), request->operation ().c_str ());

              mrCallQueue.push (new casock::rpc::protobuf::server::RPCCall (this, request));
            }
            catch (casock::base::CASClosedConnectionException& e)
            {
              LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - catch CASClosedCConnectionException\n", __FUNCTION__);

              invalidateCalls ();
              unregister ();
              destroy ();
            }
            catch (casock::rpc::base::CASRPCUnfinishedMessageException& e)
            {
              LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - catch CASRPCUnfinishedMessageException\n", __FUNCTION__);
            }
          }

          void RPCReaderHandler::callback (const RpcResponse& response)
          {
            mCommunicator.write (&response);
          }
        }
      }
    }
  }
}
