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
 * \file casock/sigio/base/SockReaderHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/sigio/base/SockReaderHandler.h"

//#include <stdio.h>
//#include <strings.h>
//#include <sys/types.h>
//#include <sys/socket.h>

#include "casock/util/Logger.h"
#include "casock/sigio/base/Communicator.h"

SockReaderHandler::SockReaderHandler (const int& fd, Communicator* pCommunicator)
  : Handler (fd), m_offset (0), mpCommunicator (pCommunicator)
{
  bzero (m_buffer, BUFFER_SIZE);
}

void SockReaderHandler::handle ()
{
  LOGMSG (HIGH_LEVEL, "SockReaderHandler::%s ()\n", __FUNCTION__);

  ssize_t s = mpCommunicator->read (&(m_buffer [m_offset]), BUFFER_SIZE - m_offset);

  if (s == 0)
    LOGMSG (HIGH_LEVEL, "SockReaderHandler::%s () - connection closed\n", __FUNCTION__);
  else
    LOGMSG (HIGH_LEVEL, "SockReaderHandler::%s () - read [%d]\n", __FUNCTION__, s);

  m_offset += s;

  /*
  ssize_t s = recv (m_fd, &(m_buffer[m_offset]), BUFFER_SIZE - m_offset, 0);
  LOGMSG (HIGH_LEVEL, "SockReaderHandler::%s () - recv [%d]\n", __FUNCTION__, s);

  if (s == 0)
    LOGMSG (HIGH_LEVEL, "SockReaderHandler::%s () - connection closed\n", __FUNCTION__);
  else
  {
    while (s > 0)
    {
      m_offset += s;
      s = recv (m_fd, &(m_buffer[m_offset]), BUFFER_SIZE, 0);
      LOGMSG (HIGH_LEVEL, "SockReaderHandler::%s () - recv [%d]\n", __FUNCTION__, s);
    }

    LOGMSG (HIGH_LEVEL, "SockReaderHandler::%s () - read [%u]\n", __FUNCTION__, m_offset);
  }
  */
}
