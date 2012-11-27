#include "casock/util/Logger.h"
#include "casock/sigio/base/Dispatcher.h"
#include "casock/base/CASException.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/client/CASClientException.h"
#include "casock/rpc/protobuf/client/RPCCallHandlerFactoryImpl.h"
#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "casock/rpc/sigio/protobuf/client/RPCClientProxy.h"
#include "casock/rpc/protobuf/client/RPCResponseHandler.h"
#include "examples/rpc/protobuf/api/rpc_hello.pb.h"

using casock::sigio::base::Dispatcher;

void Done ();
void Done (HelloResponse* pResponse);

class HelloHandler : public casock::rpc::protobuf::client::RPCResponseHandler
{
  public:
		HelloHandler (casock::rpc::protobuf::client::RPCCallController* pController, HelloResponse* pResponse)
			//: casock::rpc::protobuf::client::RPCResponseHandler (pController), mpResponse (pResponse)
			: mpResponse (pResponse)
		{ }

  public:
    void callback ()
    {
      LOGMSG (NO_DEBUG, "HelloHandler::%s () - message [%s]\n", __FUNCTION__, mpResponse->message ().c_str ());
    }

  private:
    HelloResponse* mpResponse;
};

int main ()
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  Dispatcher::initialize ();
  Dispatcher* pDispatcher = Dispatcher::getInstance ();

  try
  {
    casock::rpc::protobuf::client::RPCCallHandlerFactoryImpl callHandlerFactory;
    casock::rpc::sigio::protobuf::client::RPCClientProxy proxy (*pDispatcher, "localhost", 2000, callHandlerFactory);
    casock::rpc::protobuf::client::RPCCallController* controller = proxy.buildRPCCallController ();
    proxy.setNumCallHandlers (1);

    HelloService* service = new HelloService::Stub (&proxy);

    HelloRequest request;
    HelloResponse response;

    request.set_id (1);
    request.set_message ("Hello!");

    HelloHandler handler (controller, &response);
    //service->HelloCall (&controller, &request, &response, google::protobuf::NewCallback (&Done, &response));
    service->HelloCall (controller, &request, &response, handler.closure ());

    //Dispatcher::getInstance ()->wait (1);
    pDispatcher->waitForever ();

    delete service;
    delete controller;
  }
  catch (casock::base::CASClosedConnectionException& e)
  {
    LOGMSG (NO_DEBUG ,"%s () - CASClosedConnectionException [%s]\n", __FUNCTION__, e.what ());
  }
  catch (casock::client::CASClientException& e)
  {
    LOGMSG (NO_DEBUG, "%s () - CASClientException [%s]\n", __FUNCTION__, e.what ());
  }
  catch (casock::base::CASException& e)
  {
    LOGMSG (NO_DEBUG, "%s () - CASException [%s]\n", __FUNCTION__, e.what ());
  }

  Dispatcher::destroy ();
}

void Done ()
{
  LOGMSG (NO_DEBUG, "Done ()\n");
}

void Done (HelloResponse* pResponse)
{
  LOGMSG (NO_DEBUG, "Done () - message [%s]\n", pResponse->message ().c_str ());
}
