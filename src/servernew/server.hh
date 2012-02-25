#ifndef GUARD_DARK_MIR_SERVER_HH_INCLUDED
#define GUARD_DARK_MIR_SERVER_HH_INCLUDED

#include "server_application.hh"

enum server_constants {
	MIR_SRV_MAX_PACKET_SIZE = 0x80;
};

typedef boost::array< boost::uint8_t, MIR_SRV_PACKET_SIZE > packet_buffer;

class server {
	server_application & m_application;
	boost::asio::udp::socket m_socket;
private: // Not copyable
	server(server const &);
	server & operator=(server);
public:
	server( server_application & app );

	void start();
	void stop();
private:
	void 
	on_packet_received( 
		boost::system::error_code const & error, 
		packet_buffer buffer,
		boost::asio::udp::endpoint remote_endpoint
	) {
		if( !error || error == boost::asio::error::message_size ) {
			m_application.service().post(
				boost::bind(
					&server::on_handle_message,
					this,
					buffer,
					remote
					boost::bind(
						&server::send_reply,
						this,
						remote_endpoint,
						boost::placeholders::_1
					)	
				)
			);
		}
	}

	void
	on_handle_message( 
		packet_buffer buffer, 
		answer_callback answer
	) {
		// TODO: Process message
		// pass packet buffer to processing function
		// and send answer to cb
	}

	void 
	send_reply( 
		boost::asio::udp::endpoint remote_endpoint,
		packet_buffer buffer
	)
	{
		m_socket.async_send_to( 
			boost::asio::buffer(buffer), 
			remote_endpoint, 
			boost::bind( 
				&on_message_sent, 
				this, 
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	}
};


#endif // GUARD_DARK_MIR_SERVER_HH_INCLUDED

