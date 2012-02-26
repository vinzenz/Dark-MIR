#ifndef GUARD_DARK_MIR_SERVER_APPLICATION_HH_INCLUDED
#define GUARD_DARK_MIR_SERVER_APPLICATION_HH_INCLUDED

#include <boost/asio.hpp>
#include "options.hh"

class server_application {
	boost::asio::io_service m_service;
	options m_options;
public:
	server_application( int argc, char const ** argv );
	~server_application();

	options const & configuration();
	boost::asio::io_service & io_service();

	int run();
};

#endif //GUARD_DARK_MIR_SERVER_APPLICATION_HH_INCLUDED

