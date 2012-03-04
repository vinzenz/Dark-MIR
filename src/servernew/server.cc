#include "server.hh"
#include "debug/buffer_printer.hh"
#include <boost/bind.hpp>
#include <iostream>

namespace bap = boost::asio::placeholders;

server::server( 
	server_application & application, 
	boost::asio::ip::udp const & protocol, 
	boost::uint16_t port 
)
: m_application( application )
, m_socket( application.io_service(), endpoint( protocol, port ) )
, m_available() 
, m_running( false )
, m_counter( 0 ) {
}

// Start network subsystem
void 
server::start(
) {
	m_running = true;
	schedule_next();
	schedule_next();
	schedule_next();
}

// Stop network subsystem
void 
server::stop(
) {
	m_running = false;
}

void
server::schedule_next(
) {
	size_t current_count = size_t(m_counter);
	if( current_count < 10 || bool(m_running) ) {
		++m_counter;
		message_data_ptr data;
		if( !m_available.pop(data) ) {
			data.reset( new message_data() );
		}

		m_socket.async_receive_from(
			boost::asio::buffer( data->buffer ),
			data->remote_endpoint,
			boost::bind(
				&server::on_message_received,
				this,
				bap::error,
				bap::bytes_transferred,
				data
			)
		);
	}
}

// message received
void 
server::on_message_received( 
	error_code const & error,	// success/failure
	size_t bytes_received,		// number of bytes received
	message_data_ptr data		// endpoint and buffer pointer
) {
	// TODO: udpate transfer statistics
	if( !error && bytes_received > 0 ) {	
		data->bytes_used = bytes_received;
		m_application.io_service().post(
			boost::bind(
				&server::on_handle_message,
				this,
				data
			)
		);
	}
	else {
		// TODO: handle error
		--m_counter;
		schedule_next();
	}
}

// trigger message handling
void
server::on_handle_message(
	message_data_ptr data		// endpoint and buffer pointer
) {
	std::cout << "Packet received: " << data->bytes_used << " Bytes - Endpoint: " << data->remote_endpoint << "\n";
	std::cout << mir::dbg::format_buffer( data->buffer.data(), data->buffer.data() + data->bytes_used );
	
	// Currently simple ECHO UDP server
	send_reply( data );
}
	
// Called to send a reply
void 
server::send_reply( 
	message_data_ptr data		// endpoint and buffer pointer
) {
	m_socket.async_send_to(
		boost::asio::buffer( data->buffer, data->bytes_used ),
		data->remote_endpoint,		
		boost::bind(
			&server::on_message_sent,
			this,
			data,
			bap::bytes_transferred,
			bap::error
		)
	);
}

// Called once a message has been successfully sent
void 
server::on_message_sent( 
	message_data_ptr data,		// endpoint and buffer pointer
	size_t bytes,			// number of bytes sent
	error_code const & error	// success/failure
) {
	(*data) = message_data(); // reset values
	m_available.push( data );
	// TODO: udpate byte transfer stats
	// TODO: handle errors
	--m_counter;
	m_application.io_service().post(
		boost::bind(
			&server::schedule_next,
			this
		)
	);
}


