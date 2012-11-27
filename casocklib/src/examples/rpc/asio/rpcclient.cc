#include "casock/util/Logger.h"
#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "casock/rpc/protobuf/client/RPCCallController.h"
#include "casock/rpc/protobuf/client/RPCCallHandlerFactoryImpl.h"
#include "casock/rpc/asio/protobuf/client/RPCClientProxy.h"
#include "casock/rpc/asio/protobuf/client/RPCSocketClientFactoryImpl.h"
#include "casock/rpc/protobuf/client/RPCResponseHandler.h"
#include "casock/base/CASClosedConnectionException.h"
#include "examples/rpc/protobuf/api/rpc_hello.pb.h"

void Done ();
void Done (casock::rpc::protobuf::client::RPCCallController* pController, HelloResponse* pResponse);

casock::rpc::asio::protobuf::client::RPCClientProxy* proxy;
HelloService* service;
HelloRequest request;
HelloRequest request2;

class HelloHandler : public casock::rpc::protobuf::client::RPCResponseHandler
{
  public:
    HelloHandler (casock::rpc::protobuf::client::RPCCallController* pController, HelloResponse* pResponse)
      //: casock::rpc::protobuf::client::RPCResponseHandler (pController), mpResponse (pResponse)
      : mpController (pController), mpResponse (pResponse)
    { }

  public:
    void callback ()
    {
      LOGMSG (NO_DEBUG, "HelloHandler::%s ()\n", __FUNCTION__);

      if (! mpController->Failed () && mpResponse->id () < 2)
      {
        LOGMSG (NO_DEBUG, "HelloHandler::%s () - message [%s]\n", __FUNCTION__, mpResponse->message ().c_str ());

//        // using the same request and controller to send the next messages
//        request.set_id (request.id () + 1);
//        request.set_message (request.message () + " / " + "Hello!");
//        service->HelloCall (mpController, &request, mpResponse, closure ());
      }
      else
      {
        LOGMSG (NO_DEBUG, "HelloHandler::%s () - message [%s]\n", __FUNCTION__, mpResponse->message ().c_str ());

        request.set_id (3);
        request.set_message ("shutdown");
        HelloResponse* response = new HelloResponse ();
        casock::rpc::protobuf::client::RPCCallController* controller = proxy->buildRPCCallController ();

        service->HelloCall (controller, &request, response, ::google::protobuf::NewCallback (&Done, controller, response));

//        delete mpController;
//        delete mpResponse;
      }

      delete mpController;
      delete mpResponse;
    }

  private:
    casock::rpc::protobuf::client::RPCCallController* mpController;
    HelloResponse* mpResponse;
};

int main ()
{
  LOGGER->setDebugLevel (SILENT);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  casock::proactor::asio::base::AsyncProcessor::initialize ();

  try
  {
    casock::proactor::asio::base::AsyncProcessor* pAsyncProcessor = casock::proactor::asio::base::AsyncProcessor::getInstance ();
    casock::rpc::asio::protobuf::client::RPCSocketClientFactoryImpl clientSocketFactory (*pAsyncProcessor, "localhost", "2000");
    casock::rpc::protobuf::client::RPCCallHandlerFactoryImpl callHandlerFactory;

    proxy = new casock::rpc::asio::protobuf::client::RPCClientProxy (clientSocketFactory, callHandlerFactory);
    proxy->setNumCallHandlers (1);

    service = new HelloService::Stub (proxy);

    HelloResponse* response = new HelloResponse ();
    HelloResponse* response2 = new HelloResponse ();
    casock::rpc::protobuf::client::RPCCallController* controller = proxy->buildRPCCallController ();
    casock::rpc::protobuf::client::RPCCallController* controller2 = proxy->buildRPCCallController ();

    request.set_id (1);
    request.set_message ("Hello!");

    request2.set_id (2);
    request2.set_message ("Hello again!");

    HelloHandler handler (controller, response);
    HelloHandler handler2 (controller2, response2);
    LOGMSG (NO_DEBUG, "%s () - service->HelloCall (...)\n", __FUNCTION__);

    try
    {
      service->HelloCall (controller, &request, response, handler.closure ());
      service->HelloCall (controller2, &request2, response2, handler2.closure ());
    }
    catch (casock::base::CASClosedConnectionException& e)
    {
      LOGMSG (NO_DEBUG, "%s () - casock::base::CASClosedConnectionException [%s]\n", __FUNCTION__, e.what ());
    }

    pAsyncProcessor->run ();

    delete service;
  }
  catch (...)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (...)\n", __FUNCTION__);
  }

  delete proxy;
  casock::proactor::asio::base::AsyncProcessor::destroy ();
}

void Done ()
{
  LOGMSG (NO_DEBUG, "Done ()\n");
}

void Done (casock::rpc::protobuf::client::RPCCallController* pController, HelloResponse* pResponse)
{
  LOGMSG (NO_DEBUG, "%s ()\n", __FUNCTION__);

  if (! pController->Failed ())
    LOGMSG (NO_DEBUG, "%s () - message [%s]\n", __FUNCTION__, pResponse->message ().c_str ());

  delete pController;
  delete pResponse;
}
