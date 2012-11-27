#ifndef __CASOCKLIB__EXAMPLES__SERVER_SOCK_READER_HANDLER_H_
#define __CASOCKLIB__EXAMPLES__SERVER_SOCK_READER_HANDLER_H_

#include <stdlib.h>

#include "casock/sigio/base/Handler.h"
#include "casock/sigio/base/Communicator.h"

namespace casock {
  namespace base {
    class Dispatcher;
  }
}

namespace examples {
  class ServerSockReaderHandler : public casock::sigio::base::Handler
  {
    public:
      ServerSockReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const int& fd);

    private:
      void destroy () { delete this; }

    public:
      void handle ();

    private:
      casock::sigio::base::Communicator mCommunicator;
      size_t received;
  };
}

#endif // __CASOCKLIB__EXAMPLES__SERVER_SOCK_READER_HANDLER_H_
