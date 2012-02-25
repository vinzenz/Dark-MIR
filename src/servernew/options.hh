#ifndef GUARD_DARK_MIR_OPTIONS_HH_INCLUDED
#define GUARD_DARK_MIR_OPTIONS_HH_INCLUDED

#include <boost/program_options.hpp>

class options {
	boost::program_options::options_description 
		m_generic_options,
		m_network_options, 
		m_configuration_options;

	boost::program_options::variables_map m_values_map;
public:
	options( int argc, char const ** argv );
	
	boost::program_options::variables_map const &
		values() const;
private:
	// Initialization functions
	void initialize_generic_options();
	void initialize_network_options();
	void initialize_configuration_options();
private:
	void parse( int argc, char const ** argv );
};

#endif //GUARD_DARK_MIR_OPTIONS_HH_INCLUDED

