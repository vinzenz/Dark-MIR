#ifndef GUARD_DARK_MIR_SERVER_APPLICATION_HH_INCLUDED
#define GUARD_DARK_MIR_SERVER_APPLICATION_HH_INCLUDED

#include "options.hh"

class server_application {
	options m_options;
public:
	server_application( int argc, char const ** argv );
	~server_application();

	int run();
};

#endif //GUARD_DARK_MIR_SERVER_APPLICATION_HH_INCLUDED

