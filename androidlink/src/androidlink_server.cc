#include "androidlink_server.h"
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

using namespace std;
namespace asio = boost::asio;
using asio::ip::tcp;
using boost::uint8_t;


struct SensorHandler{

};

#define DEBUG false

// Database connection - handles a connection with a single client.
// Create only through the DbConnection::create factory.
//
class requestHandler : public boost::enable_shared_from_this<requestHandler>
{
public:
    typedef boost::shared_ptr<requestHandler> Pointer;
    typedef boost::shared_ptr<androidlink::Request> RequestPointer;
    typedef boost::shared_ptr<androidlink::Response> ResponsePointer;

    static Pointer create(asio::io_service& io_service, SensorHandler& sh)
    {
        return Pointer(new requestHandler(io_service, sh));
    }

    tcp::socket& get_socket()
    {
        return m_socket;
    }

    void start()
    {
        start_read_header();
    }

private:
    tcp::socket m_socket;
    SensorHandler& m_sh_ref;
    vector<uint8_t> m_readbuf;
    PackedMessage<androidlink::Request> m_packed_request;

    requestHandler(asio::io_service& io_service, SensorHandler& sh)
        : m_socket(io_service), m_sh_ref(sh),
        m_packed_request(boost::shared_ptr<androidlink::Request>(new androidlink::Request()))
    {
    }
    
    void handle_read_header(const boost::system::error_code& error)
    {
        DEBUG && (cerr << "handle read " << error.message() << '\n');
        if (!error) {
            DEBUG && (cerr << "Got header!\n");
            DEBUG && (cerr << show_hex(m_readbuf) << endl);
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
            DEBUG && (cerr << show_hex(m_readbuf) << endl);
            handle_request();
            start_read_header();
        }
    }

    // Called when enough data was read into m_readbuf for a complete request
    // message. 
    // Parse the request, execute it and send back a response.
    //
    void handle_request()
    {
        if (m_packed_request.unpack(m_readbuf)) {
            RequestPointer req = m_packed_request.get_msg();
            ResponsePointer resp = prepare_response(req);
            
            vector<uint8_t> writebuf;
            PackedMessage<androidlink::Response> resp_msg(resp);
            resp_msg.pack(writebuf);
            asio::write(m_socket, asio::buffer(writebuf));
        }
    }

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

    ResponsePointer prepare_response(RequestPointer req)
    {
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
//                value = req->request_set_value().value();
//                m_db_ref[req->request_set_value().key()] = value;
//                std::cout<<"req was set with key: "<<req->request_set_value().key()<<" and value "<<value<<std::endl;
                resp->set_stamp(0);
                resp->set_type(androidlink::Response::ACK);
                break;
            case androidlink::Request::GETSTATE:
            {
//                stringstream sstr;
//                sstr << m_db_ref.size();
//                value = sstr.str();
                resp->set_stamp(0);
                resp->set_type(androidlink::Response::ACK);
                break;
            }
            default:
                assert(0 && "Whoops, bad request!");
                break;
        }
        return resp;
    }
};



struct AndroidLinkServer::AndroidLinkServerImpl
{
    tcp::acceptor acceptor;
    SensorHandler sensorHandler_;

    AndroidLinkServerImpl(asio::io_service& io_service, unsigned port)
        : acceptor(io_service, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

    void start_accept()
    {
        // Create a new connection to handle a client. Passing a reference
        // to db to each connection poses no problem since the server is 
        // single-threaded.
        //
        requestHandler::Pointer new_connection =
            requestHandler::create(acceptor.io_service(), sensorHandler_);

        // Asynchronously wait to accept a new client
        //
        acceptor.async_accept(new_connection->get_socket(),
            boost::bind(&AndroidLinkServerImpl::handle_accept, this, new_connection,
                asio::placeholders::error));
    }

    void handle_accept(requestHandler::Pointer connection,
            const boost::system::error_code& error)
    {
        // A new client has connected
        //
        if (!error) {
            // Start the connection
            //
            connection->start();

            // Accept another client
            //
            start_accept();
        }
    }
};


AndroidLinkServer::AndroidLinkServer(asio::io_service& io_service, unsigned port)
    : d(new AndroidLinkServerImpl(io_service, port))
{
}


AndroidLinkServer::~AndroidLinkServer()
{
}


