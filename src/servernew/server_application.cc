// #include "server_application.hh"
#include "server.hh"
#include <boost/bind.hpp>

server_application::server_application( int argc, char const ** argv ) 
: m_service()
, m_options( argc, argv )
{

}

server_application::~server_application() {
}

int 
server_application::run(
) {
	server s( *this, boost::asio::ip::udp::v4(), 1234 );
	m_service.post( boost::bind( &server::start, &s ) );
	m_service.run();
	return 0;
}

boost::asio::io_service &
server_application::io_service(
) {
	return m_service;
}

