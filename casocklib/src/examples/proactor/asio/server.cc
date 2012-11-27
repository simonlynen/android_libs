#include "casock/util/Logger.h"
#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "examples/proactor/asio/MySocketServer.h"

int main ()
{
  LOGGER->setDebugLevel (MAX_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  casock::proactor::asio::base::AsyncProcessor::initialize ();
  casock::proactor::asio::base::AsyncProcessor* pAsyncProcessor = casock::proactor::asio::base::AsyncProcessor::getInstance ();

  try
  {
    LOGMSG (LOW_LEVEL, "%s () - creating server...\n", __FUNCTION__);
    examples::proactor::asio::MySocketServer server (*pAsyncProcessor, 2000);

    LOGMSG (LOW_LEVEL, "%s () - running server start...\n", __FUNCTION__);
    server.start ();

    LOGMSG (LOW_LEVEL, "%s () - running async processor...\n", __FUNCTION__);
    pAsyncProcessor->run ();
  }
  catch (...)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (...)\n", __FUNCTION__);
  }

  casock::proactor::asio::base::AsyncProcessor::destroy ();
  LOGGER->finalize ();
}
