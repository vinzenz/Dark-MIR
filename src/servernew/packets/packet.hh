#ifndef GUARD_DARK_MIR_PACKETS_PACKET_HH_INCLUDED
#define GUARD_DARK_MIR_PACKETS_PACKET_HH_INCLUDED

#include <cstdint>
#include <array>

namespace packets {

typedef std::array<char,16> identifier_t;

struct packet {
	std::uint8_t 	detection_byte;	// detection byte 0 in   		1 	Byte
	std::uint8_t 	major_version;	// protocol major version		1 	Byte
	std::uint8_t 	minor_version;	// protocol minor version		1 	Byte
	identifier_t 	session;		// session id					16 	Bytes
	std::uint64_t 	sequence;		// sequence						8	Bytes
	std::uint32_t	acks;			// acks							4	Bytes
	std::int32_t	id; 			// packet id					4	Bytes
	std::uint8_t	reserved[25];	// reserved bytes  				2	Bytes
	std::uint32_t 	data_size;		// Size of the data following	4	Bytes
};									// Sum							64	Bytes

// Detection Byte: non 0 if old protocol
// Detection Byte = OpCode
// DATA block[]

// Major Version: 	1
// Minor Version:   0
// Session: 	UUID session value as string
// Sequence: 	Message number sent
// Acks:		Number of packets received previously. Each bit is 1 ack
// ID:			Packet message ID ( session + sequence + id has to be seen as 1 unique message (duplicate detection) )
// Reserved:	26 Bytes for future use
// DataSize:	Number of bytes following in the body

}

#endif //GUARD_DARK_MIR_PACKETS_PACKET_HH_INCLUDED


