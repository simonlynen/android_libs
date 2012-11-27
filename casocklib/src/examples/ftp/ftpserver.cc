#include <stdlib.h>

#include "casock/util/Logger.h"
#include "casock/sigio/base/Dispatcher.h"
#include "casock/base/CASException.h"
#include "casock/sigio/server/SocketServer.h"
#include "casock/server/CASServerException.h"
#include "FTPServerSockAcceptorHandler.h"

using casock::sigio::base::Dispatcher;

void waitforfiles (const unsigned short& port);

int main (int argc, char* argv[])
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "main () - start\n");

  if (argc == 2)
  {
    unsigned short port = atoi (argv[1]);
    waitforfiles (port);
  }
  else
  {
    LOGMSG (LOW_LEVEL, "main () - run: ./ftpserver <port>\n");
  }
}


void waitforfiles (const unsigned short& port)
{
  Dispatcher::initialize ();
  Dispatcher* pDispatcher = Dispatcher::getInstance ();

  try
  {
    casock::sigio::server::SocketServer server (*pDispatcher, port);

    server.listen ();

    examples::ftp::FTPServerSockAcceptorHandler handler (*pDispatcher, &server);
    pDispatcher->waitForever ();

    server.close ();
    handler.unregister ();
  }
  catch (casock::server::CASServerException& e)
  {
    LOGMSG (NO_DEBUG, "main () - CASServerException [%s]\n", e.what ());
  }
  catch (casock::base::CASException& e)
  {
    LOGMSG (NO_DEBUG, "main () - CASException [%s]\n", e.what ());
  }

  Dispatcher::destroy ();
}
