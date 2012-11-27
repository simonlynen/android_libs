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
 * \file casock/rpc/sigio/protobuf/base/RPCCommunicator.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/sigio/protobuf/base/RPCCommunicator.h"

#include <arpa/inet.h>

#include <google/protobuf/message.h>

#include "casock/util/Logger.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/base/CASRPCException.h"
#include "casock/rpc/base/CASRPCUnfinishedMessageException.h"

namespace casock {
  namespace rpc {
    namespace sigio {
      namespace protobuf {
        namespace base {
          RPCCommunicator::RPCCommunicator (const casock::sigio::base::FileDescriptor* const pFD) : casock::sigio::base::Communicator (pFD)
          {
            size = 0;
          }

          ::google::protobuf::Message* RPCCommunicator::read ()
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s ()\n", __FUNCTION__);

            ::google::protobuf::Message* message = NULL;

            ssize_t s = 0;

            if (! size)
            {
              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - ! size\n", __FUNCTION__);
              s = Communicator::read (reinterpret_cast<char *>(&size), sizeof (int));
              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - s [%zd]\n", __FUNCTION__, s);

              if (! s)
                throw (casock::base::CASClosedConnectionException ());
              else if (s < 0)
                throw (casock::rpc::base::CASRPCUnfinishedMessageException ());

              size = ntohl (size);

              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - receiving message with %Zu bytes\n", __FUNCTION__, size);
            }

            do
            {
              s = Communicator::read (buffer, size - buffer.str ().size ());
              LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - s [%d]\n", __FUNCTION__, s);
            } while (s > 0 && buffer.str ().size () < size);

            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - received %Zu/%Zu bytes\n", __FUNCTION__, buffer.str ().size (), size);

            if (buffer.str ().size () < (size_t) size)
              throw (casock::rpc::base::CASRPCUnfinishedMessageException ());

            message = createRequest ();
            message->ParseFromIstream (&buffer);
            buffer.clear ();
            size = 0;

            return message;
          }

          void RPCCommunicator::write (const ::google::protobuf::Message* const message)
          {
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - begin\n", __FUNCTION__);

            Communicator::write (message->ByteSize ());
            stringstream buffer;
            message->SerializeToOstream (&buffer);
            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - sending message with %d bytes\n", __FUNCTION__, message->ByteSize ());
            Communicator::write (buffer);

            LOGMSG (LOW_LEVEL, "RPCCommunicator::%s () - end\n", __FUNCTION__);
          }
        }
      }
    }
  }
}
