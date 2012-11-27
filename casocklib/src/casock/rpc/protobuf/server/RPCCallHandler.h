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
 * \file casock/rpc/protobuf/server/RPCCallHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_HANDLER_H_

#include "casock/util/Thread.h"

namespace google {
  namespace protobuf {
    class Message;
  }
}

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        class RPCCall;
        class RPCCallQueue;

        class RPCCallHandler : public casock::util::Thread
        {
          protected:
            class RPCCallEntry
            {
              public:
                RPCCallEntry (RPCCall* pCall, ::google::protobuf::Message* pResponse);
                  /*
                  : mpCall (pCall), mpResponse (pResponse)
                { }
                */

                virtual ~RPCCallEntry ();
                  /*
                {
                  delete mpCall;
                  delete mpResponse;
                }
                */

              public:
                inline RPCCall* call () { return mpCall; }
                inline ::google::protobuf::Message* response () { return mpResponse; }

              private:
                RPCCall*                      mpCall;
                ::google::protobuf::Message*  mpResponse;
            };

          public:
            virtual ~RPCCallHandler () { }

          public:
            static void callback (RPCCallEntry* pCallEntry);

          public:
            virtual void run () = 0;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_HANDLER_H_
