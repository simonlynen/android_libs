/*
 * Copyright (C) 2012 Simon Lynen, Autonomous Systems Lab ETH Zürich
 *
 * All rights reserved.
 *
 * simon.lynen@mavt.ethz.ch
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "androidlink/androidlink_client.h"
#include "androidlink/packedmessage.h"
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

	void subscribePose()
	{
		RequestPointer req(new androidlink::Request);
		req->set_type(androidlink::Request_RequestType_GETPOSE);
		vector<uint8_t> writebuf;
		PackedMessage<androidlink::Request> req_msg(req);
		req_msg.pack(writebuf);
		asio::write(socket_, asio::buffer(writebuf));
	}

	void subscribeState()
	{
		RequestPointer req(new androidlink::Request);
		req->set_type(androidlink::Request_RequestType_GETSTATE);
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
				std::cout<<"got ack for registration"<<std::endl;
				break;
			case androidlink::Response::DISTOMEAS :
			{
				static bool gotmsg = false;
				if(!gotmsg){
					gotmsg = true;
					std::cout<<"got first disto msg"<<std::endl;
				}
			}
			assert(res->has_point());
			double point[3];

			point[0] = res->point().x();
			point[1] = res->point().y();
			point[2] = res->point().z();

			std::cout<<"got disto measurement(x,y,z) =  ["<<point[0]<<" "<<point[1]<<" "<<point[2]<<"]"<<std::endl;

			//TODO: process the data
			break;
			case androidlink::Response::POSE :
			{
				static bool gotmsg = false;
				if(!gotmsg){
					gotmsg = true;
					std::cout<<"got first pose msg"<<std::endl;
				}
			}

			assert(res->has_pose());

			double orientation[4]; //Eigen Quaterniond convention: w + xi + yj + zk see: http://eigen.tuxfamily.org/dox/classEigen_1_1Quaternion.html#details
			orientation[0] = res->pose().pose().pose().orientation().x();
			orientation[1] = res->pose().pose().pose().orientation().y();
			orientation[2] = res->pose().pose().pose().orientation().z();
			orientation[3] = res->pose().pose().pose().orientation().w();

			double origin[3];
			origin[0] = res->pose().pose().pose().origin().x();
			origin[1] = res->pose().pose().pose().origin().y();
			origin[2] = res->pose().pose().pose().origin().z();

			//TODO: process the data

			std::cout<<"position(x,y,z) = ["<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<"]"<<std::endl;
			std::cout<<"orientation(w,x,y,z) = ["<<orientation[3]<<" "<<orientation[0]<<" "<<orientation[1]<<" "<<orientation[2]<<"]"<<std::endl;

			break;
			case androidlink::Response::STATE :
			{
				static bool gotmsg = false;
				if(!gotmsg){
					gotmsg = true;
					std::cout<<"got first state msg"<<std::endl;
				}
			}
			//TODO: process the data
			break;
			case androidlink::Response::POINT :
			{
				static bool gotmsg = false;
				if(!gotmsg){
					gotmsg = true;
					std::cout<<"got first point msg"<<std::endl;
				}
			}
			//TODO: process the data
			break;
			case androidlink::Response::PLANE :
			{
				static bool gotmsg = false;
				if(!gotmsg){
					gotmsg = true;
					std::cout<<"got first plane msg"<<std::endl;
				}
			}
			//TODO: process the data
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
void AndroidLinkClient::subscribePose(){
	d->subscribePose();
}
void AndroidLinkClient::subscribeState(){
	d->subscribeState();
}

AndroidLinkClient::~AndroidLinkClient()
{
}


