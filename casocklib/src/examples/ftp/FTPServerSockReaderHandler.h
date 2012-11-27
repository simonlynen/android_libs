#ifndef __CASOCKLIB__EXAMPLES_FTP__FTP_SERVER_SOCK_READER_HANDLER_H_
#define __CASOCKLIB__EXAMPLES_FTP__FTP_SERVER_SOCK_READER_HANDLER_H_

#include <stdlib.h>

#include "casock/sigio/base/Handler.h"
#include "FTPCommunicator.h"

namespace casock {
  namespace base {
    class Dispatcher;
  }
}

namespace examples {
  namespace ftp {
    class FTPServerSockReaderHandler : public casock::sigio::base::Handler
    {
      public:
        FTPServerSockReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const int& fd);

      private:
        void destroy () { delete this; }

      public:
        void handle ();

      private:
        FTPCommunicator mCommunicator;
        size_t received;

        static unsigned int counter;
    };
  }
}


#endif // __CASOCKLIB__EXAMPLES_FTP__FTP_SERVER_SOCK_READER_HANDLER_H_
