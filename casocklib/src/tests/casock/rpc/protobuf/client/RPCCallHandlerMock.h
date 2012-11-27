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
 * \file tests/casock/rpc/protobuf/client/RPCCallHandlerMock.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CALL_HANDLER_MOCK_H_
#define __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CALL_HANDLER_MOCK_H_

#include "casock/rpc/protobuf/client/RPCCallHandler.h"

namespace tests {
  namespace casock {
    namespace rpc {
      namespace protobuf {
        namespace client {
          class RPCCallHandlerMock : public ::casock::rpc::protobuf::client::RPCCallHandler
          {
            public:
              virtual ~RPCCallHandlerMock ();

            public:
              void run ();
              void start ();
              void cancel () const;
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_PROTOBUF_CLIENT__RPC_CALL_HANDLER_MOCK_H_
