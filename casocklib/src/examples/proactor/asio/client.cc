#include "casock/util/Logger.h"
#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "examples/proactor/asio/MySocketClient.h"

int main ()
{
  LOGGER->setDebugLevel (MAX_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  casock::proactor::asio::base::AsyncProcessor::initialize ();
  casock::proactor::asio::base::AsyncProcessor* pAsyncProcessor = casock::proactor::asio::base::AsyncProcessor::getInstance ();

  try
  {
    LOGMSG (LOW_LEVEL, "%s () - creating client...\n", __FUNCTION__);
    examples::proactor::asio::MySocketClient client (*pAsyncProcessor, "localhost", "2000");

    LOGMSG (LOW_LEVEL, "%s () - asynchronously connecting...\n", __FUNCTION__);
    client.asyncConnect ();

    LOGMSG (LOW_LEVEL, "%s () - running async processor...\n", __FUNCTION__);
    pAsyncProcessor->run ();
  }
  catch (std::exception& e)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (std::exception&) - e [%s]\n", __FUNCTION__, e.what ());
  }
  catch (...)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (...)\n", __FUNCTION__);
  }

  casock::proactor::asio::base::AsyncProcessor::destroy ();
  LOGGER->finalize ();
}
