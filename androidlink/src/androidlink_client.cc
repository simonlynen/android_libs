
#include "androidlink_client.h"
#include "packedmessage.h"
#include "androidlink.pb.h"
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
namespace asio = boost::asio;
using asio::ip::tcp;
using boost::uint8_t;
typedef boost::shared_ptr<androidlink::Request> RequestPointer;
typedef boost::shared_ptr<androidlink::Response> ResponsePointer;


#define DEBUG false

struct AndroidLinkClient::AndroidLinkClientImpl:public boost::enable_shared_from_this<AndroidLinkClientImpl>
{

	AndroidLinkClientImpl(asio::io_service& io_service, std::string host, unsigned port):io_service_(io_service),socket_(io_service),
			m_packed_response(boost::shared_ptr<androidlink::Response>(new androidlink::Response()))
			{
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(host, boost::lexical_cast<std::string>(port));
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::endpoint endpoint = *endpoint_iterator;
		socket_.async_connect(endpoint,
				boost::bind(&AndroidLinkClientImpl::handle_connect, this,
						boost::asio::placeholders::error));
			}


	void requestDistoMeas()
	{
		RequestPointer req(new androidlink::Request);
		req->set_type(androidlink::Request_RequestType_GETDISTOMEAS);
		vector<uint8_t> writebuf;
		PackedMessage<androidlink::Request> req_msg(req);
		req_msg.pack(writebuf);
		asio::write(socket_, asio::buffer(writebuf));
	}


private:

	void handle_connect(const boost::system::error_code& error)
	{
		if (!error)
		{
			start_read_header(); //handle responses
		}
	}

	void handle_read_header(const boost::system::error_code& error)
	{
		DEBUG && (cerr << "handle read " << error.message() << '\n');
		if (!error) {
			DEBUG && (cerr << "Got header!\n");
			DEBUG && (cerr << show_hex(m_readbuf) << endl);
			unsigned msg_len = m_packed_response.decode_header(m_readbuf);
			DEBUG && (cerr << msg_len << " bytes\n");
			start_read_body(msg_len);
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		DEBUG && (cerr << "handle body " << error << '\n');
		if (!error) {
			DEBUG && (cerr << "Got body!\n");
			DEBUG && (cerr << show_hex(m_readbuf) << endl);
			handle_response();
			start_read_header();
		}
	}

	// Called when enough data was read into m_readbuf for a complete request
	// message.
	// Parse the request, execute it and send back a response.
	//
	void handle_response()
	{
		if (m_packed_response.unpack(m_readbuf)) {
			ResponsePointer res = m_packed_response.get_msg();
			switch (res->type())
			{
			case androidlink::Response::ACK:
				std::cout<<"got ack"<<std::endl;
				break;
			case androidlink::Response::DISTOMEAS :
				std::cout<<"got disto msg"<<std::endl;
				break;
			case androidlink::Response::POSE :
				std::cout<<"got pose msg"<<std::endl;
				break;
			case androidlink::Response::STATE :
				std::cout<<"got state msg"<<std::endl;
				break;
			case androidlink::Response::POINT :
				std::cout<<"got point msg"<<std::endl;
				break;
			case androidlink::Response::PLANE :
				std::cout<<"got plane msg"<<std::endl;
				break;
			default:
				std::cout<<"got unknown response type!"<<std::endl;
				break;
			}
		}
	}

	void start_read_header()
	{
		m_readbuf.resize(HEADER_SIZE);
		asio::async_read(socket_, asio::buffer(m_readbuf),
				boost::bind(&AndroidLinkClientImpl::handle_read_header, this,
						asio::placeholders::error));
	}

	void start_read_body(unsigned msg_len)
	{
		// m_readbuf already contains the header in its first HEADER_SIZE
		// bytes. Expand it to fit in the body as well, and start async
		// read into the body.
		//
		m_readbuf.resize(HEADER_SIZE + msg_len);
		asio::mutable_buffers_1 buf = asio::buffer(&m_readbuf[HEADER_SIZE], msg_len);
		asio::async_read(socket_, buf,
				boost::bind(&AndroidLinkClientImpl::handle_read_body, this,
						asio::placeholders::error));
	}
private:

	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	vector<uint8_t> m_readbuf;
	PackedMessage<androidlink::Response> m_packed_response;

};


AndroidLinkClient::AndroidLinkClient(asio::io_service& io_service, std::string host, unsigned port)
: d(new AndroidLinkClientImpl(io_service, host, port))
{
}

void AndroidLinkClient::requestDistoMeas(){
	d->requestDistoMeas();
}

AndroidLinkClient::~AndroidLinkClient()
{
}


