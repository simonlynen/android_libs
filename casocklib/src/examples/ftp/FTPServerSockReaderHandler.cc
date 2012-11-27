#include "FTPServerSockReaderHandler.h"

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
  namespace ftp {
    unsigned int FTPServerSockReaderHandler::counter = 0;

    FTPServerSockReaderHandler::FTPServerSockReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const int& fd) : Handler (rDispatcher, new casock::sigio::base::FileDescriptor (fd)), mCommunicator (mpFileDescriptor)
    {
      LOGMSG (LOW_LEVEL, "FTPServerSockReaderHandler::FTPServerSockReaderHandler () - begin\n");

      received = 0;

      string msg1 = "CONNECTED!";
      mCommunicator.write (msg1.c_str (), msg1.size ());
    };

    void FTPServerSockReaderHandler::handle ()
    {
      LOGMSG (MEDIUM_LEVEL, "FTPServerSockReaderHandler::%s () - treating request...\n", __FUNCTION__);

      try
      {
        FTPFile* pFile = mCommunicator.getFile (counter);
        LOGMSG (LOW_LEVEL, "FTPServerSockReaderHandler::%s () - file [%s]\n", __FUNCTION__, pFile->toString ().c_str ());
        pFile->save ();
        counter++;
      }
      catch (casock::base::CASClosedConnectionException& e1)
      {
        LOGMSG (LOW_LEVEL, "FTPServerSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
        unregister ();
        destroy ();
      }
      catch (casock::base::CASException& e2)
      {
        LOGMSG (LOW_LEVEL, "FTPServerSockReaderHandler::%s () - read [%u/%u]\n", __FUNCTION__, mCommunicator.getBuffSize (), mCommunicator.getSize ());
      }
    }
  }
}
