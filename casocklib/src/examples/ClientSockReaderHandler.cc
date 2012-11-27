#include "ClientSockReaderHandler.h"

#include <cstdio>
#include <strings.h>

#include <string>

#include "casock/util/Logger.h"
#include "casock/sigio/base/Communicator.h"
#include "casock/base/CASClosedConnectionException.h"

using std::string;

namespace examples {
  void ClientSockReaderHandler::handle ()
  {
    try
    {
      stringstream sstream;
      ssize_t s = mCommunicator.read (sstream);

      if (s)
        LOGMSG (LOW_LEVEL, "ClientSockReaderHandler::%s () - sstream [%s]\n", __FUNCTION__, sstream.str ().c_str ());
    }
    catch (casock::base::CASClosedConnectionException& e)
    {
      LOGMSG (LOW_LEVEL, "ClientSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
      unregister ();
      //    destroy ();
      throw (e);
    }
  }
}
