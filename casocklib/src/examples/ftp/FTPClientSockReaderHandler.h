#ifndef __CASOCKLIB__EXAMPLES_FTP__FTP_CLIENT_SOCK_READER_HANDLER_H_
#define __CASOCKLIB__EXAMPLES_FTP__FTP_CLIENT_SOCK_READER_HANDLER_H_

#include "casock/sigio/base/Handler.h"
#include "FTPCommunicator.h"

namespace casock {
  namespace base {
    class Dispatcher;
    class FileDescriptor;
  }
}

namespace examples {
  namespace ftp {
    class FTPClientSockReaderHandler : public casock::sigio::base::Handler
    {
      public:
        FTPClientSockReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const casock::sigio::base::FileDescriptor* const pFileDescriptor) : Handler (rDispatcher, pFileDescriptor), mCommunicator (mpFileDescriptor) { }

      public:
        void handle ();
        FTPCommunicator& communicator () { return mCommunicator; }

      private:
        FTPCommunicator mCommunicator;
    };
  }
}


#endif // __CASOCKLIB__EXAMPLES_FTP__FTP_CLIENT_SOCK_READER_HANDLER_H_
