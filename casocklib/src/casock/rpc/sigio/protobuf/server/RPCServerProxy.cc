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
 * \file casock/rpc/sigio/protobuf/server/RPCServerProxy.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/sigio/protobuf/server/RPCServerProxy.h"

#include "casock/util/types.h"
#include "casock/util/Logger.h"
#include "casock/sigio/server/SocketServer.h"
#include "casock/rpc/sigio/protobuf/server/RPCAcceptorHandler.h"
//#include "casock/rpc/protobuf/server/RPCCallQueue.h"
//#include "casock/rpc/protobuf/server/RPCCallHandler.h"
//#include "casock/rpc/protobuf/server/RPCCallResponseHandler.h"

namespace casock {
  namespace rpc {
    namespace sigio {
      namespace protobuf {
        namespace server {
          RPCServerProxy::RPCServerProxy (
              RPCCallHandlerFactory& rCallHandlerFactory,
              casock::sigio::base::Dispatcher& rDispatcher,
              const uint32& port)
            : casock::rpc::protobuf::server::RPCServerProxy (rCallHandlerFactory), mrDispatcher (rDispatcher)
          {
            LOGMSG (HIGH_LEVEL, "RPCServerProxy::RPCServerProxy (const uint32&) - port [%u]\n", port);

            mpSocketServer = new casock::sigio::server::SocketServer (mrDispatcher, port);
            mpAcceptorHandler = NULL;
          }

          RPCServerProxy::~RPCServerProxy ()
          {
            //if (m_running)
            //  stop ();

            delete mpSocketServer;
          }

          void RPCServerProxy::start ()
          {
            mpSocketServer->listen ();
            //mpCallHandler->start ();

            if (! mpAcceptorHandler)
              mpAcceptorHandler = new RPCAcceptorHandler (mrDispatcher, mpSocketServer, *mpCallQueue);

            //m_running = true;
          }

          void RPCServerProxy::stop ()
          {
            if (mpAcceptorHandler)
            {
              mpAcceptorHandler->unregister ();
              delete mpAcceptorHandler;
              mpAcceptorHandler = NULL;
            }

            mpSocketServer->close ();
            //mpCallHandler->cancel ();

            //m_running = false;
          }
        }
      }
    }
  }
}
