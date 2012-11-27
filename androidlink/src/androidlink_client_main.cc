
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "androidlink_client.h"
#include "packedmessage.h"
#include "androidlink.pb.h"


using namespace std;
namespace asio = boost::asio;


int main(int argc, const char* argv[])
{
	unsigned port = 4050;
	std::string addr = "localhost";
	if (argc > 1)
		addr = argv[1];
	if (argc > 2)
		port = atoi(argv[2]);
	cout << "Client connecting to: "<<addr<< ":" << port << endl;

	try {
		asio::io_service io_service;
		AndroidLinkClient client(io_service, addr, port);

		client.requestDistoMeas();

		io_service.run();
	}
	catch (std::exception& e) {
		cerr << e.what() << endl;
	}

	return 0;
}
