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
 * \file casock/rpc/sigio/protobuf/client/RPCClientProxy.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "RPCClientProxy.h"

#include <sstream>
using std::stringstream;

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

#include "casock/util/Logger.h"
#include "casock/sigio/client/SocketClient.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"
#include "casock/rpc/protobuf/client/RPCCallHandler.h"
#include "casock/rpc/sigio/protobuf/client/RPCReaderHandler.h"

namespace casock {
  namespace rpc {
    namespace sigio {
      namespace protobuf {
        namespace client {
          RPCClientProxy::RPCClientProxy (casock::sigio::base::Dispatcher& rDispatcher, const string& host, const unsigned int& port, const RPCCallHandlerFactory& rCallHandlerFactory)
            : casock::rpc::protobuf::client::RPCClientProxy (rCallHandlerFactory)
          {
            LOGMSG (HIGH_LEVEL, "RPCClientProxy::RPCClientProxy ()\n");

            mpSocketClient = new SocketClient (rDispatcher, host, port);
            mpSocketClient->connect ();
            mpReaderHandler = new RPCReaderHandler (rDispatcher, mpSocketClient, *mpCallHash, *mpCallQueue);
          }

          void RPCClientProxy::sendRpcRequest (const casock::rpc::protobuf::api::RpcRequest& request, casock::rpc::protobuf::client::RPCCall* pCall)
          {
            try
            {
              mpReaderHandler->communicator ().write (&request);
              registerRPCCall (request.id (), pCall);
            }
            catch (std::exception& e)
            {
              pCall->controller ()->SetFailed (string ("Impossible to send request [") + e.what () + "]");
              mpCallQueue->push (pCall);
            }
            catch (...)
            {
              pCall->controller ()->SetFailed ("Impossible to send request");
              mpCallQueue->push (pCall);
            }
          }
        }
      }
    }
  }
}
