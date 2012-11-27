#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <fstream>
#include <iostream>

#include "casock/util/Logger.h"
#include "casock/sigio/base/Dispatcher.h"
#include "casock/base/CASException.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/sigio/client/SocketClient.h"
#include "casock/client/CASClientException.h"
#include "FTPClientSockReaderHandler.h"
#include "FTPCommunicator.h"
#include "FTPFile.h"

using std::string;
using std::ifstream;
using casock::sigio::base::Dispatcher;
using examples::ftp::FTPFile;
using examples::ftp::FTPClientSockReaderHandler;
using examples::ftp::FTPCommunicator;

FTPFile* readfile (string& filename);
void sendfile (const string& server, const unsigned short& port, const FTPFile& rFile);

int main (int argc, char* argv[])
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "main () - start\n");

  if (argc == 4)
  {
    string server = argv[1];
    unsigned short port = atoi (argv[2]);
    string filename = argv[3];

    LOGMSG (LOW_LEVEL, "main () - server [%s], port [%hd], filename [%s]\n", server.c_str (), port, filename.c_str ());
    FTPFile* pFile = readfile (filename);
    LOGMSG (LOW_LEVEL, "main () - file size [%u]\n", pFile->getSize ());
    sendfile (server, port, *pFile);
  }
  else
  {
    LOGMSG (LOW_LEVEL, "main () - run: ./ftpclient <server> <port> <file>\n");
  }
}

FTPFile* readfile (string& filename)
{
  FTPFile* pFile = new FTPFile (filename);

  ifstream is;
  is.open (filename.c_str (), std::ios::binary);

  // get length of file:
  is.seekg (0, std::ios::end);
  size_t length = is.tellg ();
  is.seekg (0, std::ios::beg);

  // allocate memory:
  char* buffer = new char [length];

  // read data as a block:
  is.read (buffer,length);

  pFile->setSize (length);
  pFile->setBuffer (buffer);

  is.close ();

  return pFile;
}

void sendfile (const string& server, const unsigned short& port, const FTPFile& rFile)
{
  Dispatcher::initialize ();
  Dispatcher* pDispatcher = Dispatcher::getInstance ();

  try
  {
    casock::sigio::client::SocketClient client (*pDispatcher, "localhost", 2000);
    client.connect ();
    FTPClientSockReaderHandler handler (*pDispatcher, &client);
    FTPCommunicator& communicator = handler.communicator ();

    if (client.connected ())
    {
      communicator.sendFile (rFile);

      do
      {
        pDispatcher->wait (10);
      } while (false);

      client.close ();
      handler.unregister ();
    }
    else
      printf ("client not connected!\n");

  }
  catch (casock::base::CASClosedConnectionException& e)
  {
    printf ("main () - CASClosedConnectionException [%s]\n", e.what ());
  }
  catch (casock::client::CASClientException& e)
  {
    printf ("main () - casock::client::CASClientException [%s]\n", e.what ());
  }
  catch (casock::base::CASException& e)
  {
    printf ("main () - casock::base::CASException [%s]\n", e.what ());
  }

  Dispatcher::destroy ();
}
