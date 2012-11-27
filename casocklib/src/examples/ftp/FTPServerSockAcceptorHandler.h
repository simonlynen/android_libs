#ifndef __CASOCKLIB__EXAMPLES_FTP__FTP_SERVER_SOCK_ACCEPTOR_HANDLER_H_
#define __CASOCKLIB__EXAMPLES_FTP__FTP_SERVER_SOCK_ACCEPTOR_HANDLER_H_

#include "casock/sigio/server/SockAcceptorHandler.h"

namespace casock {
  namespace base {
    class Dispatcher;
    class FileDescriptor;
  }
}

namespace examples {
  namespace ftp {
    class FTPServerSockAcceptorHandler : public casock::sigio::server::SockAcceptorHandler
    {
      public:
        FTPServerSockAcceptorHandler (casock::sigio::base::Dispatcher& rDispatcher, const casock::sigio::base::FileDescriptor* const pFileDescriptor) : casock::sigio::server::SockAcceptorHandler (rDispatcher, pFileDescriptor), mrDispatcher (rDispatcher) { }

      private:
        //    void createHandler (const FileDescriptor* const pFileDescriptor);
        void createHandler (const int& fd);

      private:
        casock::sigio::base::Dispatcher& mrDispatcher;
    };
  }
}

#endif // __CASOCKLIB__EXAMPLES_FTP__FTP_SERVER_SOCK_ACCEPTOR_HANDLER_H_
