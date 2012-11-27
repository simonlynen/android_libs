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
 * \file casock/sigio/base/Communicator.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/base/Communicator.h"

#include <arpa/inet.h>

#include <string>
using std::string;

#include "casock/util/Logger.h"
#include "casock/sigio/base/FileDescriptor.h"
#include "casock/base/CASClosedConnectionException.h"

namespace casock {
  namespace sigio {
    namespace base {
      const ssize_t Communicator::read (char* buffer, const size_t& len)
      {
        LOGMSG (HIGH_LEVEL, "Communicator::%s () - len [%Zu]\n", __FUNCTION__, len);
        return mpFD->read (buffer, len);
      }

      const ssize_t Communicator::read (stringstream& buffer)
      {
        LOGMSG (HIGH_LEVEL, "Communicator::%s ()\n", __FUNCTION__);

        ssize_t received = 0;

        char buff[BUFSIZ];

        ssize_t s = read (buff, BUFSIZ);
        LOGMSG (HIGH_LEVEL, "Communicator::%s () - read (stringstream&): ssize_t [%ld]\n", __FUNCTION__, s);

        if (s == 0)
          throw (casock::base::CASClosedConnectionException ());

        while (s > 0)
        {
          received += s;
          buffer << string (buff, s);

          s = read (buff, BUFSIZ);
          //warning: format ‘%d’ expects type ‘int’, but argument 3 has type ‘ssize_t’
          LOGMSG (HIGH_LEVEL, "Communicator::%s () - read (stringstream&): ssize_t [%ld]\n", __FUNCTION__, s);
        }

        return received;
      }

      const ssize_t Communicator::read (stringstream& buffer, const size_t& len)
      {
        LOGMSG (HIGH_LEVEL, "Communicator::%s (stringstream&, const size_t&) - len [%ld]\n", __FUNCTION__, len);

        ssize_t received = 0;

        char buff [len];

        ssize_t s = read (buff, len);

        if (s == 0)
          throw (casock::base::CASClosedConnectionException ());

        while (s > 0 && buffer.str ().size () < len)
        {
          LOGMSG (HIGH_LEVEL, "Communicator::%s (stringstream&, const size_t&) - read %ld bytes\n", __FUNCTION__, s);

          received += s;
          buffer << string (buff, s);

          if (received < (ssize_t) len)
            s = read (&(buff [received]), len - received);
        }

        return received;
      }

      void Communicator::write (const char* buffer, const size_t& len)
      {
        LOGMSG (HIGH_LEVEL, "Communicator::%s () - writing (const stringstream&): ssize_t [%ld]\n", __FUNCTION__, len);
        mpFD->write (buffer, len);
      }

      void Communicator::write (const stringstream& buffer)
      {
        LOGMSG (HIGH_LEVEL, "Communicator::%s () - writing (const stringstream&): ssize_t [%ld]\n", __FUNCTION__, buffer.str ().size ());
        mpFD->write (buffer.str ().c_str (), buffer.str ().size ());
      }

      void Communicator::write (const int& buffer)
      {
        LOGMSG (HIGH_LEVEL, "Communicator::%s () - writing int [%d]\n", __FUNCTION__, buffer);
        int buff = htonl (buffer);
        mpFD->write (reinterpret_cast<char *>(&buff), sizeof (int));
      }

      void Communicator::write (const size_t& buffer)
      {
        LOGMSG (HIGH_LEVEL, "Communicator::%s () - writing size_t [%d]\n", __FUNCTION__, buffer);
        size_t buff = htonl (buffer);
        mpFD->write (reinterpret_cast<char *>(&buff), sizeof (size_t));
      }
    }
  }
}
