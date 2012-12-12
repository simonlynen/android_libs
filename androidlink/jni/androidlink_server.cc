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

#include "androidlink/androidlink_server.h"
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


//slynen{
#include <ros/publisher.h>
#include <ros/subscriber.h>
#include <android_ros_helpers.h>
#include <android_ros_node_handle.h>
//}

using namespace std;
namespace asio = boost::asio;
using asio::ip::tcp;
using boost::uint8_t;

#define DEBUG false

typedef boost::shared_ptr<androidlink::Request> RequestPointer;
typedef boost::shared_ptr<androidlink::Response> ResponsePointer;

#include <android/log.h>

#ifdef LOGI
#undef LOGI
#endif
#ifdef LOGD
#undef LOGD
#endif
#ifdef TAG
#undef TAG
#endif

#define TAG "ANDROIDLINKSERVER"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

// Database connection - handles a connection with a single client.
// Create only through the DbConnection::create factory.
//
class requestHandler : public boost::enable_shared_from_this<requestHandler>
{
public:
	typedef boost::shared_ptr<requestHandler> Pointer;

	static Pointer create(asio::io_service& io_service, AndroidLinkServer::AndroidLinkServerImpl& sh)
	{
		return Pointer(new requestHandler(io_service, sh));
	}

	tcp::socket& get_socket()
	{
		return m_socket;
	}

	void start()
	{
		LOGD("ANDROIDLINK starting to read messages in handler");
		start_read_header();
	}


	void stop()
	{
		LOGD("ANDROIDLINK stopping to read messages in handler");
		m_socket.close();
	}

	//put the message on the wire
	void publish(ResponsePointer resp){
//		LOGD("ANDROIDLINK putting message on the wire");
		vector<uint8_t> writebuf;
		PackedMessage<androidlink::Response> resp_msg(resp);
		resp_msg.pack(writebuf);
		asio::write(m_socket, asio::buffer(writebuf));
	}

private:
	tcp::socket m_socket;
	AndroidLinkServer::AndroidLinkServerImpl& m_sh_ref;
	vector<uint8_t> m_readbuf;
	PackedMessage<androidlink::Request> m_packed_request;

	requestHandler(asio::io_service& io_service, AndroidLinkServer::AndroidLinkServerImpl& sh)
	: m_socket(io_service), m_sh_ref(sh),
	  m_packed_request(boost::shared_ptr<androidlink::Request>(new androidlink::Request()))
	{
	}

	void handle_read_header(const boost::system::error_code& error)
	{
		DEBUG && (cerr << "handle read " << error.message() << '\n');
		if (!error) {
			DEBUG && (cerr << "Got header!\n");
			unsigned msg_len = m_packed_request.decode_header(m_readbuf);
			DEBUG && (cerr << msg_len << " bytes\n");
			start_read_body(msg_len);
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		DEBUG && (cerr << "handle body " << error << '\n');
		if (!error) {
			DEBUG && (cerr << "Got body!\n");
			handle_request();
			start_read_header();
		}
	}

	// Called when enough data was read into m_readbuf for a complete request
	// message.
	// Parse the request, execute it and send back a response.
	//
	void handle_request();


	void start_read_header()
	{
		m_readbuf.resize(HEADER_SIZE);
		asio::async_read(m_socket, asio::buffer(m_readbuf),
				boost::bind(&requestHandler::handle_read_header, shared_from_this(),
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
		asio::async_read(m_socket, buf,
				boost::bind(&requestHandler::handle_read_body, shared_from_this(),
						asio::placeholders::error));
	}

};



struct AndroidLinkServer::AndroidLinkServerImpl
{
	tcp::acceptor acceptor;

	std::map<int, std::vector<requestHandler::Pointer> > callbacks_;

	AndroidLinkServerImpl(boost::asio::io_service& io_service, unsigned port)
	: acceptor(io_service, tcp::endpoint(tcp::v4(), port))
	{
		std::stringstream ss;
		ss<<"ANDROIDLINK server is up at "<<port;
		D(ss.str().c_str());
		start_accept();
	}

	void start_accept()
	{
		// Create a new connection to handle a client. Passing a reference
		// to db to each connection poses no problem since the server is
		// single-threaded.
		//

		requestHandler::Pointer new_connection =
				requestHandler::create(acceptor.io_service(), *this);

		D("ANDROIDLINK created new conn");
		// Asynchronously wait to accept a new client
		//
		acceptor.async_accept(new_connection->get_socket(),
				boost::bind(&AndroidLinkServerImpl::handle_accept, this, new_connection,
						asio::placeholders::error));
	}

	void registerCallback(int type, requestHandler::Pointer handler){
		callbacks_[type].push_back(handler);
	}

	void publish_pose(geometry_msgs::PoseWithCovarianceStamped& msg){
//		LOGD("ANDROIDLINK publishing pose");
		//make a protobuf pose message from ros message
		ResponsePointer resp(new androidlink::Response);
		resp->set_type(androidlink::Response::POSE);
		resp->set_stamp(msg.header.stamp.toSec());
		resp->mutable_pose()->mutable_pose()->set_stamp(msg.header.stamp.toSec());
		resp->mutable_pose()->mutable_pose()->mutable_pose()->mutable_orientation()->set_w(msg.pose.pose.orientation.w);
		resp->mutable_pose()->mutable_pose()->mutable_pose()->mutable_orientation()->set_x(msg.pose.pose.orientation.x);
		resp->mutable_pose()->mutable_pose()->mutable_pose()->mutable_orientation()->set_y(msg.pose.pose.orientation.y);
		resp->mutable_pose()->mutable_pose()->mutable_pose()->mutable_orientation()->set_z(msg.pose.pose.orientation.z);
		resp->mutable_pose()->mutable_pose()->mutable_pose()->mutable_origin()->set_x(msg.pose.pose.position.x);
		resp->mutable_pose()->mutable_pose()->mutable_pose()->mutable_origin()->set_y(msg.pose.pose.position.y);
		resp->mutable_pose()->mutable_pose()->mutable_pose()->mutable_origin()->set_z(msg.pose.pose.position.z);

		//TODO fill covariance

//		LOGD("ANDROIDLINK calling callbacks");
		//for all registered callbacks
		for(size_t i = 0;i<callbacks_[androidlink::Request::GETPOSE].size();++i){
			callbacks_[androidlink::Request::GETPOSE].at(i)->publish(resp);
		}
	}
	void publish_point(geometry_msgs::PointStamped& point){
//TODO impl
	}
	void publish_state(ssf_core::DoubleArrayStamped& state){
		//TODO impl
	}
	void publish_plane(geometry_msgs::PointStamped& point, geometry_msgs::PointStamped& normal){
		//TODO impl
	}
	void publish_distomeas(geometry_msgs::PointStamped& point){
		//TODO impl
	}
	void handle_accept(requestHandler::Pointer connection,
			const boost::system::error_code& error)
	{
		LOGD("ANDROIDLINK got new client connection");
		// A new client has connected
		//
		if (!error) {
			// Start the connection
			//
			connection->start();
			LOGD("ANDROIDLINK started new client connection");

			// Accept another client
			//
			start_accept();
		}
	}
};


AndroidLinkServer::AndroidLinkServer(boost::asio::io_service& io_service, unsigned port)
: d(new AndroidLinkServerImpl(io_service, port))
{
}


void AndroidLinkServer::publish_pose(geometry_msgs::PoseWithCovarianceStamped& pose){
	d->publish_pose(pose);
}
void AndroidLinkServer::publish_point(geometry_msgs::PointStamped& point){
	d->publish_point(point);
}
void AndroidLinkServer::publish_state(ssf_core::DoubleArrayStamped& state){
	d->publish_state(state);
}
void AndroidLinkServer::publish_distomeas(geometry_msgs::PointStamped& point){
	d->publish_distomeas(point);
}
void AndroidLinkServer::publish_plane(geometry_msgs::PointStamped& point, geometry_msgs::PointStamped& normal){
	d->publish_plane(point, normal);
}
AndroidLinkServer::~AndroidLinkServer()
{
}

void requestHandler::handle_request()
{
	if (m_packed_request.unpack(m_readbuf)) {
		RequestPointer req = m_packed_request.get_msg();
		string value;
		ResponsePointer resp(new androidlink::Response);
		switch (req->type())
		{
		case androidlink::Request::GETDISTOMEAS:
		{
			//                StringDatabase::iterator i = m_db_ref.find(req->request_get_value().key());
			//                value = i == m_db_ref.end() ? "" : i->second;
			resp->set_stamp(0);
			resp->set_type(androidlink::Response::ACK);
			break;
		}
		case androidlink::Request::GETPOSE:
			m_sh_ref.registerCallback(androidlink::Request::GETPOSE, shared_from_this());
			resp->set_stamp(0);
			resp->set_type(androidlink::Response::ACK);
			break;
		case androidlink::Request::GETSTATE:
		{
			m_sh_ref.registerCallback(androidlink::Request::GETSTATE, shared_from_this());
			resp->set_stamp(0);
			resp->set_type(androidlink::Response::ACK);
			break;
		}
		default:
			assert(0 && "Whoops, bad request!");
			break;
		}

		vector<uint8_t> writebuf;
		PackedMessage<androidlink::Response> resp_msg(resp);
		resp_msg.pack(writebuf);
		asio::write(m_socket, asio::buffer(writebuf));
	}
}

