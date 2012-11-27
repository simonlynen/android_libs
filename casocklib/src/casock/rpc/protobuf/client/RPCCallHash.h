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
 * \file casock/rpc/protobuf/client/RPCCallHash.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_HASH_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_HASH_H_

#include "casock/util/LockableHash.h"

namespace casock {
  namespace util {
    class SafeLock;
  }

  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCCall;
        class RPCCallHash : private casock::util::LockableHash<uint32, RPCCall*>
        {
          private:
            friend class SafeLock;

          public:
            void push (const uint32& id, RPCCall* pCall);
            RPCCall* pop (const uint32& id);
            using casock::util::LockableHash<uint32, RPCCall*>::empty;
            using casock::util::LockableHash<uint32, RPCCall*>::size;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_HASH_H_
