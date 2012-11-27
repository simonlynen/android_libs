#include <glog/logging.h>
#include <gflags/gflags.h>

#include "casock/util/Logger.h"
#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "casock/rpc/protobuf/server/RPCCallHandlerFactoryImpl.h"
#include "casock/rpc/asio/protobuf/server/RPCSocketServerFactoryImpl.h"
#include "casock/rpc/asio/protobuf/server/RPCServerProxy.h"

#include "examples/rpc/protobuf/api/rpc_hello.pb.h"

casock::rpc::asio::protobuf::server::RPCServerProxy* proxy;

class HelloServiceImpl : public  HelloService
{
  public:
    void HelloCall(::google::protobuf::RpcController* controller,
        const ::HelloRequest* request,
        ::HelloResponse* response,
        ::google::protobuf::Closure* done)
    {
      LOGMSG (LOW_LEVEL, "HelloServiceImpl::%s () - request->message () [%s]\n", __FUNCTION__, request->message ().c_str ());

      response->set_id (request->id ());
      response->set_message ("I'm the server. You sent me: " + request->message ());
      done->Run ();

      if (request->message () == "shutdown")
      {
        sleep (1);
        proxy->stop ();
      }
    }
};

int main (int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags (&argc, &argv, true);

	DLOG(INFO) << __PRETTY_FUNCTION__;

  LOGGER->setDebugLevel (SILENT);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  casock::proactor::asio::base::AsyncProcessor::initialize ();

  HelloServiceImpl service;

  try
  {
    casock::proactor::asio::base::AsyncProcessor* pAsyncProcessor = casock::proactor::asio::base::AsyncProcessor::getInstance ();
    casock::rpc::asio::protobuf::server::RPCSocketServerFactoryImpl serverSocketFactory (*pAsyncProcessor, 2000);
    casock::rpc::protobuf::server::RPCCallHandlerFactoryImpl callHandlerFactory (&service);

    proxy = new casock::rpc::asio::protobuf::server::RPCServerProxy (serverSocketFactory, callHandlerFactory);
    proxy->setNumCallHandlers (1);
    proxy->start ();

    pAsyncProcessor->run ();
  }
  catch (...)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (...)\n", __FUNCTION__);
  }

  delete proxy;
  casock::proactor::asio::base::AsyncProcessor::destroy ();
  LOGGER->finalize ();
}
