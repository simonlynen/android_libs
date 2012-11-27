#ifndef __CASOCKLIB__EXAMPLES_FTP__FTP_COMMUNICATOR_H_
#define __CASOCKLIB__EXAMPLES_FTP__FTP_COMMUNICATOR_H_

#include <string.h>
#include <arpa/inet.h>

#include <sstream>
using std::stringstream;

#include "casock/sigio/base/Communicator.h"
#include "casock/base/CASException.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/util/Logger.h"
#include "FTPFile.h"

namespace examples {
  namespace ftp {
    class FTPCommunicator : public casock::sigio::base::Communicator
    {
      public:
        FTPCommunicator (const casock::sigio::base::FileDescriptor* const pFD) : casock::sigio::base::Communicator (pFD) { }

      public:
        void sendFile (const FTPFile& rFile)
        {
          const size_t size = rFile.getSize ();
          const char* buffer = rFile.getBuffer ();

          write (size);

          //write (buffer, size);

          unsigned int i = 0;

          for (i = 0; i+BUFSIZ <= size; i += BUFSIZ)
          {
            LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - sending [%u/%u]\n", __FUNCTION__, i+BUFSIZ, size);
            write (&(buffer [i]), BUFSIZ);
            sleep(1);
          }

          if (i < size)
          {
            LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - sending [%u/%u]\n", __FUNCTION__, size, size);
            write (&(buffer [i]), size-i);
          }
        };

        FTPFile* getFile (const unsigned int& counter)
        {
          ssize_t s = 0;

          if (! size)
          {
            LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - ! size\n", __FUNCTION__);
            s = Communicator::read (reinterpret_cast<char *>(&size), sizeof (size_t));
            LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - s [%zd]\n", __FUNCTION__, s);

            if (! s)
              throw (casock::base::CASClosedConnectionException ());
            else if (s < 0)
              throw (casock::base::CASException ("Unfinished message!"));

            size = ntohl (size);

            LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - receiving message with %Zu bytes\n", __FUNCTION__, size);
          }

          do
          {
            s = Communicator::read (buffer, size - buffer.str ().size ());
            LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - s [%zd]\n", __FUNCTION__, s);
          } while (s > 0 && buffer.str ().size () < size);

          LOGMSG (LOW_LEVEL, "FTPCommunicator::%s () - received %zu/%zu bytes\n", __FUNCTION__, buffer.str ().size (), size);

          if (buffer.str ().size () < (size_t) size)
            throw (casock::base::CASException ("Unfinished message!"));

          char* ftpbuff = new char [size];
          strncpy (ftpbuff, buffer.str ().c_str (), size);

          stringstream ss;
          ss << "file_";
          ss << counter;
          ss << ".ftp";

          std::string filename = ss.str ();

          FTPFile* pFile = new FTPFile (filename);
          pFile->setSize (size);
          pFile->setBuffer (ftpbuff);

          size = 0;

          return pFile;
        }

        const size_t& getSize () { return size; }
        const size_t getBuffSize () { return buffer.str ().size (); }

      private:
        size_t size;
        stringstream buffer;
    };
  }
}

#endif // __CASOCKLIB__EXAMPLES_FTP__FTP_COMMUNICATOR_H_
