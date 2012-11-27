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
 * \file casock/rpc/protobuf/base/RPCProxy.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_BASE__RPC_PROXY_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_BASE__RPC_PROXY_H_

#include <vector>
#include "casock/util/types.h"

namespace casock {
  namespace util {
    class Thread;
  }

  namespace rpc {
    namespace protobuf {
      namespace base {
        class RPCProxy
        {
          public:
            virtual ~RPCProxy ();

          public:
            void addCallHandlers (const uint32& n);
            void removeCallHandlers (const uint32& n);
            void setNumCallHandlers (const uint32& n);

          protected:
            virtual casock::util::Thread* buildCallHandler () = 0;

          protected:
            std::vector<casock::util::Thread*>  mCallHandlers; /*!< Handlers responsible for aquire requests from queue, execute RPC operation and callback */

          public:
            static uint32 DEFAULT_NUM_CALL_HANDLERS;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_BASE__RPC_PROXY_H_
