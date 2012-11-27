#ifndef ANDROIDLINK_CLIENT_H
#define ANDROIDLINK_CLIENT_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class AndroidLinkClient
{
public:
	AndroidLinkClient(boost::asio::io_service& io_service, std::string host, unsigned port);
    ~AndroidLinkClient();
    void requestDistoMeas();

private:
    AndroidLinkClient();

    struct AndroidLinkClientImpl;
    boost::scoped_ptr<AndroidLinkClientImpl> d;
};

#endif

