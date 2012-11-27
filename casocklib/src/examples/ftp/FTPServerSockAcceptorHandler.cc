#include "FTPServerSockAcceptorHandler.h"

#include <stdio.h>

#include "FTPServerSockReaderHandler.h"
#include "casock/sigio/base/Communicator.h"
#include "casock/sigio/base/FileDescriptor.h"

namespace examples {
  namespace ftp {
    void FTPServerSockAcceptorHandler::createHandler (const int& fd)
    {
      printf ("FTPServerSockAcceptorHandler::%s () - begin\n", __FUNCTION__);
      new examples::ftp::FTPServerSockReaderHandler (mrDispatcher, fd);
    }
  }
}
