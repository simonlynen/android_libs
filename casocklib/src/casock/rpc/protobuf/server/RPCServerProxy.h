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
 * \file casock/rpc/protobuf/server/RPCServerProxy.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_

#include "casock/rpc/protobuf/base/RPCProxy.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        class RPCCallQueue;
        class RPCCallHandlerFactory;

        /*!
         * This is the RPC server proxy interface for a protobuf based RPC service.
         *
         * To implement a RPC server it's necessary to extend this class defining
         * a communication channel (a socket server, for example) and the methods
         * start () and stop (). The attributre.
         *
         * When a request is received by the communication channel it is enqueued
         * into mpCallQueue, that is a queue of RPCCalls. The RPCCall is an object
         * with a pointer to the response handler (responsable for send the response
         * to the client) and a pointer to the request.
         *
         * The RPCCallHandler is responsible for get the RPCCalls from the queue and
         * execute the operation using the service. The class RPCCallHanlder defines
         * a RPCCallEntry, that is an object that contains all the informations
         * necessary to return a response to the client. This callback is invocated
         * since the operation is fihisned. This callback is responsible to create
         * a response object with the return of the operation and send it to the
         * client using the callback that is registered in RPCCall.
         *
         * So we have two objects that control the status of an RPC call: the RPCCall,
         * that represents a call received by the communication channel and the RPCCallEntry,
         * that represents a call being treated by the RPC service. The RPCCall is created
         * since a request is received by the RPC server, and is destroyed since a response
         * is returned to the client, and the RPCCallEntry is created since a request start
         * to be treated as an operation and is destroyed since the operation finishes.
         */

        class RPCServerProxy : public casock::rpc::protobuf::base::RPCProxy
        {
          protected:
            RPCServerProxy (const RPCCallHandlerFactory& rCallHandlerFactory);
            virtual ~RPCServerProxy ();

          private:
            casock::util::Thread* buildCallHandler ();

          protected:
            virtual void start () = 0;
            virtual void stop () = 0;

          protected:
            RPCCallQueue* const mpCallQueue; /*!< Maintain a queue of requests received from all clients */
            const RPCCallHandlerFactory& mrCallHandlerFactory;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_SERVER_PROXY_H_
