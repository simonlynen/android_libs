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
 * \file casock/sigio/base/SocketReader.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef _SOCKET_READER_HANDLER_H_
#define _SOCKET_READER_HANDLER_H_

#include <stdlib.h>
#include <sstream>

using std::stringstream;

class Communicator;

class SocketReader
{
  public:
    SocketReader (Communicator* pCommunicator) : mpCommunicator (pCommunicator) { };

  public:
    const ssize_t read (stringstream& sstream);

  private:
    Communicator* mpCommunicator;

  private:
    static const size_t BUFFER_SIZE = 1024;
};


#endif // _SOCKET_READER_HANDLER_H_
