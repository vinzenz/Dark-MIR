#ifndef GUARD_DARK_MIR_DEBUG_BUFFER_PRINTER_HH_INCLUDED
#define GUARD_DARK_MIR_DEBUG_BUFFER_PRINTER_HH_INCLUDED

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

namespace mir {
namespace dbg {

namespace detail {

inline void
format_print_char( 
	std::ostream & os,		// The output stream to write to
	std::uint8_t const c,		// Character to print
	std::size_t const counter,	// number of character to be printed (buffer index)
	std::size_t const group,	// number of characters per group
	bool const line_ended,		// whether or not the current character is on a new line
	bool const to_hex = true	// print as hex?
) {	
	if( counter > 0 && !line_ended ) {
		if( ( counter % group ) == 0 ) {
			os << " |";
		}
	}
	
	if ( to_hex ) {
		os << " " << std::setw(2);
		os << std::setfill('0') << std::hex << unsigned(c);
		os << std::setfill(' ');
	}
	else {
		os << " " << char(c) << char(c);
	}
}

}

inline std::string 
format_buffer( 
	std::uint8_t const * bufferStart,	// pointer to the beginning of the data range
	std::uint8_t const * bufferEnd,		// pointer + buffer size
	std::size_t const group = 8,		// bytes per group
	std::size_t const groups_per_line = 2	// groups per line
) {
	std::ostringstream ostr;
	std::size_t const line_max = group * groups_per_line;
	std::size_t counter = 0;
	for( counter = 0; bufferStart != bufferEnd; ++bufferStart, ++counter ) {
		bool const line_ended = (counter % line_max) == 0;

		// Line processing
		if ( counter > 0 ) {		// Only if this is not the beginning
			if( line_ended ) { 	// Line end reached
				ostr << "\n";	// Append new line
			}
		}

		// Print Line Number if the previous line ended, or if it is the first line
		if ( line_ended ) {
			ostr << std::setw(3) << size_t(counter / line_max)
			     << " |";
		}

		mir::dbg::detail::format_print_char( ostr, *bufferStart, counter, group, line_ended, true );
	}

	size_t empty_columns = line_max - ( counter % line_max );
	if( empty_columns != line_max ) { // if the line end was not reached yet
		for( size_t i = 0; i < empty_columns; ++i ) {
			mir::dbg::detail::format_print_char( ostr, std::uint8_t('-'), counter + i, group, false, false );
		}
	}

	ostr << std::endl;
	return ostr.str();
}

}}

#endif //GUARD_DARK_MIR_DEBUG_BUFFER_PRINTER_HH_INCLUDED

