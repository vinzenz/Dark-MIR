#include "server_application.hh"

int main( int argc, char const ** argv ) {
	
	server_application app(argc, argv);
	return app.run();
}


