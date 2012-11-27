#include "casock/util/Logger.h"
#include "casock/sigio/base/Dispatcher.h"
#include "casock/server/CASServerException.h"
#include "casock/rpc/protobuf/server/RPCCallHandlerFactoryImpl.h"
#include "casock/rpc/sigio/protobuf/server/RPCServerProxy.h"

#include "examples/rpc/protobuf/api/rpc_hello.pb.h"

using casock::sigio::base::Dispatcher;

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
    }
};

int main ()
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  Dispatcher::initialize ();
  Dispatcher* pDispatcher = Dispatcher::getInstance ();

  HelloServiceImpl service;
  casock::rpc::protobuf::server::RPCCallHandlerFactoryImpl callHandlerFactory (&service);

  try
  {
    casock::rpc::sigio::protobuf::server::RPCServerProxy proxy (callHandlerFactory, *pDispatcher, 2000);
    proxy.setNumCallHandlers (1);
    proxy.start ();

    pDispatcher->waitForever ();
  }
  catch (casock::server::CASServerException& e)
  {
    LOGMSG (NO_DEBUG, "%s () - CASServerException [%s]\n", __FUNCTION__, e.what ());
  }
  catch (casock::base::CASException& e)
  {
    LOGMSG (NO_DEBUG, "%s () - CASException [%s]\n", __FUNCTION__, e.what ());
  }

  Dispatcher::destroy ();
}
