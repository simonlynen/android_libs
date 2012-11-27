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
 * \file casock/sigio/base/SockReaderHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef _SOCK_READER_HANDLER_H_
#define _SOCK_READER_HANDLER_H_

#include <stdlib.h>

#include "Handler.h"

class Communicator;

class SockReaderHandler : public Handler
{
  private:
    static const size_t BUFFER_SIZE = 1024;

  public:
    SockReaderHandler (const int& fd, Communicator* pCommunicator);

  protected:
    void destroy () { delete this; }

  public:
    virtual void handle ();

  protected:
    char          m_buffer[BUFFER_SIZE];
    unsigned int  m_offset;

  protected:
    Communicator* mpCommunicator;
};


#endif // _SOCK_READER_HANDLER_H_
