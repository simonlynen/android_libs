#include <unistd.h>

#include <stdio.h>
#include <string>

#include "casock/util/Logger.h"
#include "casock/sigio/base/Dispatcher.h"
#include "casock/sigio/base/Communicator.h"
#include "casock/base/CASException.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/sigio/client/SocketClient.h"
#include "casock/client/CASClientException.h"
#include "ClientSockReaderHandler.h"

using std::string;
using casock::sigio::base::Dispatcher;
using examples::ClientSockReaderHandler;

int main ()
{
  LOGGER->setDebugLevel (MAX_LEVEL);
  LOGMSG (LOW_LEVEL, "main () - start\n");

  Dispatcher::initialize ();
  Dispatcher* pDispatcher = Dispatcher::getInstance ();

  try
  {
    casock::sigio::client::SocketClient client (*pDispatcher, "localhost", 2000);
    client.connect ();
    ClientSockReaderHandler handler (*pDispatcher, &client);
    casock::sigio::base::Communicator& communicator = handler.communicator ();

    if (client.connected ())
    {
      size_t sent = 0;

      while (true)
      {
        string s (10 * BUFSIZ, 'a');
        communicator.write (s.c_str (), s.size ());
        sent += s.size ();

        printf ("main () - sent: %Zu\n", sent);

        pDispatcher->wait (10);
      }

      client.close ();
      handler.unregister ();
    }
    else
      printf ("client not connected!\n");

  }
  catch (casock::base::CASClosedConnectionException& e)
  {
    printf ("main () - CASClosedConnectionException [%s]\n", e.what ());
  }
  catch (casock::client::CASClientException& e)
  {
    printf ("main () - CASClientException [%s]\n", e.what ());
  }
  catch (casock::base::CASException& e)
  {
    printf ("main () - CASException [%s]\n", e.what ());
  }

  Dispatcher::destroy ();
}
