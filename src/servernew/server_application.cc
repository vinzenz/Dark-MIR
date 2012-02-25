#include "server_application.hh"

server_application::server_application( int argc, char const ** argv ) 
: m_options( argc, argv )
{

}

server_application::~server_application() {
}

int server_application::run() {
	return 0;
}
