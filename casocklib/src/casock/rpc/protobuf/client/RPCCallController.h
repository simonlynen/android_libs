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
 * \file casock/rpc/protobuf/client/RPCCallController.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_CONTROLLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_CONTROLLER_H_

#include <string>
#include <list>

#include <google/protobuf/service.h>

#include "casock/util/TimeoutConfigurable.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCCallController : public google::protobuf::RpcController, public casock::util::TimeoutConfigurable
        {
          public:
            RPCCallController ()
            {
              Reset ();
            }

          public:
            void Reset() // from google::protobuf::RpcController
            {
              failed = false;
              reason = "";
              canceled = false;
              cancelListeners.clear ();
            }

            bool Failed() const // from google::protobuf::RpcController
            {
              return failed;
            }

            std::string ErrorText() const // from google::protobuf::RpcController
            {
              return reason;
            }

            void StartCancel() // from google::protobuf::RpcController
            {
              canceled = true;

              std::list<google::protobuf::Closure*>::const_iterator it;
              std::list<google::protobuf::Closure*>::const_iterator itEnd = cancelListeners.end ();

              for (it = cancelListeners.begin (); it != itEnd; ++it)
                (*it)->Run ();
            }

            void SetFailed(const std::string& reason) // from google::protobuf::RpcController
            {
              failed = true;
              this->reason = reason;
            }

            bool IsCanceled() const // from google::protobuf::RpcController
            {
              return canceled;
            }

            void NotifyOnCancel(google::protobuf::Closure* callback) // from google::protobuf::RpcController
            {
              cancelListeners.push_back (callback);
            }

          private:
            bool failed;
            std::string reason;
            bool canceled;
            std::list<google::protobuf::Closure*> cancelListeners;

          //private:
            //struct timeval m_timeout;
            //casock::util::Timeout mTimeout;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_CALL_CONTROLLER_H_
