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
 * \file casock/rpc/sigio/protobuf/client/RPCReaderHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/sigio/protobuf/client/RPCReaderHandler.h"

#include "casock/util/Logger.h"
#include "casock/sigio/base/FileDescriptor.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/rpc/base/CASRPCUnfinishedMessageException.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallHash.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"

namespace casock {
  namespace rpc {
    namespace sigio {
      namespace protobuf {
        namespace client {
          RPCReaderHandler::RPCReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const casock::sigio::base::FileDescriptor* const pFileDescriptor, RPCCallHash& rCallHash, RPCCallQueue& rCallQueue)
            : Handler (rDispatcher, pFileDescriptor), mCommunicator (pFileDescriptor), mrCallHash (rCallHash), mrCallQueue (rCallQueue)
          {
          }

          void RPCReaderHandler::handle ()
          {
            LOGMSG (LOW_LEVEL, "RPCReaderHandler::%s ()\n", __FUNCTION__);

            try
            {
              casock::rpc::protobuf::api::RpcResponse* response = mCommunicator.read ();
              LOGMSG (LOW_LEVEL, "RPCReaderHandler::%s () - response received: %d bytes - id [%u]\n", __FUNCTION__, response->ByteSize (), response->id ());

							RPCCall* pCall = mrCallHash.pop (response->id ());

              if (pCall)
              {
                pCall->setRpcResponse (response);
                mrCallQueue.push (pCall);
              }
            }
            catch (casock::base::CASClosedConnectionException& e)
            {
              LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - CASClosedCConnectionException [%s]\n", __FUNCTION__, e.what());
              unregister ();
              destroy ();
            }
            catch (casock::rpc::base::CASRPCUnfinishedMessageException& e)
            {
              LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - CASRPCUnfinishedMessageException\n", __FUNCTION__);
            }
          }
        }
      }
    }
  }
}
