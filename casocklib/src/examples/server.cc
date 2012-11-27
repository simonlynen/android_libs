#include "casock/util/Logger.h"
#include "casock/sigio/base/Dispatcher.h"
#include "casock/base/CASException.h"
#include "casock/sigio/server/SocketServer.h"
#include "casock/server/CASServerException.h"
#include "ServerSockAcceptorHandler.h"

using casock::sigio::base::Dispatcher;
using examples::ServerSockAcceptorHandler;

int main ()
{
  LOGGER->setDebugLevel (MAX_LEVEL);
  LOGMSG (LOW_LEVEL, "main () - start\n");

  Dispatcher::initialize ();
  Dispatcher* pDispatcher = Dispatcher::getInstance ();

  try
  {
    casock::sigio::server::SocketServer server (*pDispatcher, 2000);

    server.listen ();

    ServerSockAcceptorHandler handler (*pDispatcher, &server);
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
