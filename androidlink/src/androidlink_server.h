#ifndef ANDROIDLINK_SERVER_H
#define ANDROIDLINK_SERVER_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class AndroidLinkServer 
{
public:
    AndroidLinkServer(boost::asio::io_service& io_service, unsigned port);
    ~AndroidLinkServer();

private:
    AndroidLinkServer();
    void start_accept();

    struct AndroidLinkServerImpl;
    boost::scoped_ptr<AndroidLinkServerImpl> d;
};

#endif /* DB_SERVER_H */

