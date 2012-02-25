#include "options.hh"
#include <vector>

options::options( int argc, char const ** argv ) 
: m_generic_options("Generic options")
, m_network_options("Network options")
, m_configuration_options("Configuration options")
, m_values_map()
{
	initialize_generic_options();
	initialize_network_options();
	initialize_configuration_options();
	parse(argc, argv);
}

boost::program_options::variables_map const & 
	options::values() const {
	return m_values_map;
}


void options::initialize_generic_options() {
	boost::program_options::options_description & desc = m_generic_options;
	desc.add_options()
		( "version", /*"v",*/ "print version string" )
		( "help", /*"h",*/ "produce help message" )
	;
}

void options::initialize_network_options() {
	boost::program_options::options_description & desc = m_network_options;
	desc.add_options()
		( "port4" , "port to listen on for IPv4" )
		( "address4", "ip address to listen on for IPv4" )
		( "port6" , "port to listen on for IPv6" )
		( "address6", "ip address to listen on for IPv6" )
	;
}

void options::initialize_configuration_options() {
	boost::program_options::options_description & desc = m_configuration_options;
	desc.add_options()
		( "debug", "enables debug mode" )
	;
}

void options::parse( int argc, char const ** argv ) {
	namespace bpo = boost::program_options;
	bpo::options_description all_desc;
	all_desc
		.add( m_generic_options )
		.add( m_network_options )
		.add( m_configuration_options )
	;

	bpo::store( bpo::command_line_parser( std::vector<std::string>(argv, argv+argc) ).options( all_desc ).run(),  m_values_map );
	bpo::notify( m_values_map );
}
