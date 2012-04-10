#ifndef GUARD_DARK_MIR_SERVER_HH_INCLUDED
#define GUARD_DARK_MIR_SERVER_HH_INCLUDED

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "server_application.hh"
#include "lockfree_queue.hh"

#include <memory>
#include <functional>


typedef std::function<void()> answer_callback;

enum server_constants {
	MIR_SRV_MAX_PACKET_SIZE = 0x80
};

typedef boost::array< boost::uint8_t, MIR_SRV_MAX_PACKET_SIZE > packet_buffer;

struct default_protocol_handler {
	typedef std::function<void(packet_buffer const &)> reply_function;
	typedef boost::asio::ip::udp::endpoint endpoint;
	typedef boost::system::error_code error_code;
	
	// message received
	inline
	void 
	on_message_received(
		error_code const & error,			// success/failure
		size_t bytes_received,				// number of bytes received
		endpoint remote_endpoint,			// client endpoint
		packet_buffer const & data			// endpoint and buffer pointer
	){}

	// trigger message handling
	inline
	void
	on_handle_message(
		reply_function reply_fun,			// Callback to send a reply
		endpoint remote_endpoint,			// client endpoint
		packet_buffer & data				// endpoint and buffer pointer
	){}

	// Called once a message has been successfully sent
	inline
	void
	on_message_sent(
		size_t bytes,						// number of bytes sent
		error_code const & error,			// success/failure
		endpoint remote_endpoint,			// client endpoint
		packet_buffer const & data			// endpoint and buffer pointer
	){}
};

template< typename ProtocolHandler = default_protocol_handler >
class server {
	// Typedefs
	typedef boost::asio::ip::udp::endpoint endpoint;
	typedef boost::system::error_code error_code;

	// Types
	struct message_data {
		endpoint 	remote_endpoint;	// Where did we get the message from
		packet_buffer 	buffer;			// Message receiving and sending buffer
		size_t		bytes_used;		// Number of bytes used in the buffer
	};
	typedef std::shared_ptr<message_data> message_data_ptr;
public:
	typedef ProtocolHandler protocol_handler_type;

private: // Variables 
	server_application & 					m_application;
	std::auto_ptr<protocol_handler_type> 	m_protocol_instance;
	protocol_handler_type &					m_protocol;
	boost::asio::ip::udp::socket 			m_socket;
	lock_free_queue<message_data_ptr> 		m_available;
	std::atomic<bool> 						m_running;
	std::atomic<size_t> 					m_counter;

private: // Not copyable
	server(server const &);
	server & operator=(server);
public:
	// Constructor
	// @param app reference to server_application instance
	// @param protocol protocol to use boost::asio::ip::udp::v6() or boost::asio::ip::udp::v4()
	// @param port port to listen to
	// @param protocol_handler reference to the protocol handler
	server( 
		server_application & app, 
		boost::asio::ip::udp const & protocol, 
		boost::uint16_t port,
		protocol_handler_type & protocol_handler
	);

	// Constructor
	// @param app reference to server_application instance
	// @param protocol protocol to use boost::asio::ip::udp::v6() or boost::asio::ip::udp::v4()
	// @param port port to listen to
	server( 
		server_application & app, 
		boost::asio::ip::udp const & protocol, 
		boost::uint16_t port
	);

	// Start network subsystem
	void start(
	);

	// Stop network subsystem
	void stop(
	);

private:
	void
	schedule_next(
	);

	// message received
	void 
	on_message_received( 
		error_code const & error,	// success/failure
		size_t bytes_received,		// number of bytes received
		message_data_ptr data		// endpoint and buffer pointer
	);

	// trigger message handling
	void
	on_handle_message(
		message_data_ptr data		// endpoint and buffer pointer
	);
	
	// Called to send a reply
	void 
	send_reply( 
		message_data_ptr data		// endpoint and buffer pointer
	);

	// Called once a message has been successfully sent
	void
	on_message_sent( 
		message_data_ptr data,		// endpoint and buffer pointer
		size_t bytes,			// number of bytes sent
		error_code const & error	// success/failure
	);
};


#endif // GUARD_DARK_MIR_SERVER_HH_INCLUDED

