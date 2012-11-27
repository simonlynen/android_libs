#include "ServerSockAcceptorHandler.h"

#include <stdio.h>

#include "ServerSockReaderHandler.h"
#include "casock/sigio/base/Communicator.h"
#include "casock/sigio/base/FileDescriptor.h"

namespace examples {
  void ServerSockAcceptorHandler::createHandler (const int& fd)
  {
    printf ("ServerSockAcceptorHandler::%s () - begin\n", __FUNCTION__);
    new ServerSockReaderHandler (mrDispatcher, fd);
  }
}
