#include "ServerSockReaderHandler.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <string>
using std::string;

#include "casock/util/Logger.h"
#include "casock/sigio/base/FileDescriptor.h"
#include "casock/base/CASClosedConnectionException.h"

namespace examples {
  ServerSockReaderHandler::ServerSockReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const int& fd) : Handler (rDispatcher, new casock::sigio::base::FileDescriptor (fd)), mCommunicator (mpFileDescriptor)
  {
    LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::ServerSockReaderHandler () - begin\n");

    received = 0;

    string msg1 = "CONNECTED!";
    mCommunicator.write (msg1.c_str (), msg1.size ());
  };

  void ServerSockReaderHandler::handle ()
  {
    LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - treating request...\n", __FUNCTION__);

    try
    {
      stringstream request;
      ssize_t s = mCommunicator.read (request);

      if (s)
      {
        stringstream response;
        response << "received " << request.str ().size () << " bytes";
        received += request.str ().size ();
        LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - response[%s], received: %Zu bytes\n", __FUNCTION__, response.str ().c_str (), received);
        mCommunicator.write (response);
      }
    }
    catch (casock::base::CASClosedConnectionException& e)
    {
      LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
      unregister ();
      destroy ();
    }
  }
}
