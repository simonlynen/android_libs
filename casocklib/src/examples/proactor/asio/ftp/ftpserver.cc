#include <cstdlib>

#include "casock/util/Logger.h"
#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "examples/proactor/asio/ftp/FTPSocketServer.h"

using casock::proactor::asio::base::AsyncProcessor;

void waitforfiles (const unsigned short& port);

int main (int argc, char* argv[])
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  if (argc == 2)
  {
    unsigned short port = atoi (argv[1]);
    waitforfiles (port);
  }
  else
  {
    LOGMSG (LOW_LEVEL, "%s () - run: ./ftpserver <port>\n", __FUNCTION__);
  }
}


void waitforfiles (const unsigned short& port)
{
  AsyncProcessor::initialize ();
  AsyncProcessor* pAsyncProcessor = AsyncProcessor::getInstance ();

  try
  {
    examples::proactor::asio::ftp::FTPSocketServer server (*pAsyncProcessor, port);
    server.start ();
    pAsyncProcessor->run ();
  }
  catch (std::exception& e)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (std::exception&) [%s]\n", __FUNCTION__, e.what ());
  }
  catch (...)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (...)\n", __FUNCTION__);
  }

  AsyncProcessor::destroy ();
}
