#include "FTPClientSockReaderHandler.h"

#include <stdio.h>
#include <strings.h>

#include <string>
using std::string;

#include "casock/util/Logger.h"
#include "casock/sigio/base/Communicator.h"
#include "casock/base/CASClosedConnectionException.h"

namespace examples {
  namespace ftp {
    void FTPClientSockReaderHandler::handle ()
    {
      try
      {
        stringstream sstream;
        ssize_t s = mCommunicator.read (sstream);

        if (s)
          LOGMSG (LOW_LEVEL, "FTPClientSockReaderHandler::%s () - sstream [%s]\n", __FUNCTION__, sstream.str ().c_str ());
      }
      catch (casock::base::CASClosedConnectionException& e)
      {
        LOGMSG (LOW_LEVEL, "FTPClientSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
        unregister ();
        throw (e);
      }
    }
  }
}
