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
 * \file tests/casock/proactor/asio/client1.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/util/Logger.h"
#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "tests/casock/proactor/asio/SocketClient1.h"

using casock::proactor::asio::base::AsyncProcessor;

int main ()
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  AsyncProcessor::initialize ();
  AsyncProcessor* pAsyncProcessor = AsyncProcessor::getInstance ();

  try
  {
    LOGMSG (LOW_LEVEL, "%s () - creating client...\n", __FUNCTION__);
    tests::casock::proactor::asio::SocketClient1 client (pAsyncProcessor, "localhost", "2000");

    LOGMSG (LOW_LEVEL, "%s () - asynchronously connecting...\n", __FUNCTION__);
    client.asyncConnect ();

    LOGMSG (LOW_LEVEL, "%s () - running async processor...\n", __FUNCTION__);
    pAsyncProcessor->run ();
  }
  catch (std::exception& e)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (std::exception&) - e [%s]\n", __FUNCTION__, e.what ());
  }
  catch (...)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (...)\n", __FUNCTION__);
  }

  AsyncProcessor::destroy ();
}
