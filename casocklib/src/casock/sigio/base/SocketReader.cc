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
 * \file casock/sigio/base/SocketReader.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "SocketReader.h"

#include <string>
using std::string;

#include "Communicator.h"

const ssize_t SocketReader::read (stringstream& sstream)
{
  ssize_t len = 0;

  char buffer[BUFFER_SIZE];

  ssize_t s = mpCommunicator->read (buffer, BUFFER_SIZE);

  len += s;
  sstream << string (buffer, s);

  while (s > 0)
  {
    s = mpCommunicator->read (buffer, BUFFER_SIZE);

    len += s;
    sstream << string (buffer, s);
  }

  return len;
}
