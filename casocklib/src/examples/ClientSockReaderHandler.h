#ifndef __CASOCKLIB__EXAMPLES__CLIENT_SOCK_READER_HANDLER_H_
#define __CASOCKLIB__EXAMPLES__CLIENT_SOCK_READER_HANDLER_H_

#include "casock/sigio/base/Handler.h"
#include "casock/sigio/base/Communicator.h"

namespace casock {
  namespace base {
    class Dispatcher;
    class FileDescriptor;
  }
}

namespace examples {
  class ClientSockReaderHandler : public casock::sigio::base::Handler
  {
    public:
      ClientSockReaderHandler (casock::sigio::base::Dispatcher& rDispatcher, const casock::sigio::base::FileDescriptor* const pFileDescriptor) : Handler (rDispatcher, pFileDescriptor), mCommunicator (mpFileDescriptor) { }

      //  private:
      //    void destroy () { delete this; }

    public:
      void handle ();
      casock::sigio::base::Communicator& communicator () { return mCommunicator; }

    private:
      casock::sigio::base::Communicator mCommunicator;
  };
}


#endif // __CASOCKLIB__EXAMPLES__CLIENT_SOCK_READER_HANDLER_H_
