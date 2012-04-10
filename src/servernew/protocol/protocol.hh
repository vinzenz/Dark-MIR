#ifndef GUARD_DARK_MIR_PROTOCOL_PROTOCOL_HH_INCLUDED
#define GUARD_DARK_MIR_PROTOCOL_PROTOCOL_HH_INCLUDED

#include <cstdint>

namespace protocol {
	
	static std::uint8_t const kStart = 0;
	static std::uint8_t const kStop  = 1;
	
	static std::size_t const  kNicknameMaxLength = 32;
	static std::size_t const  kHostnameMaxLength = 256;
	
	static std::size_t const  kServerTimeInterval = 20;
	
	namespace opcode {
		enum type {
			new_player 		= 0x01,
			list_players	= 0x0A,

			logout 			= 0xFE,

			rotate_right	= 0x11,
			rotate_left		= 0x12,
			speed_up		= 0x13,
			slow_down		= 0x14,
			shift_right		= 0x15,
			shift_left		= 0x16,
			turbo			= 0x17,

			position		= 0x21,
			state			= 0x22,
			ship_state		= 0x23,
			weapon_state	= 0x26,
			object_state	= 0x27,

			fire_min		= 0x40,
			fire_0			= fire_min | 0x0,
			fire_1			= fire_min | 0x1,
			fire_2			= fire_min | 0x2,
			fire_3			= fire_min | 0x3,
			fire_4			= fire_min | 0x4,
			fire_5			= fire_min | 0x5,
			fire_6			= fire_min | 0x6,
			fire_7			= fire_min | 0x7,
			fire_8			= fire_min | 0x8,
			fire_9			= fire_min | 0x9,
			fire_a			= fire_min | 0xA,
			fire_b			= fire_min | 0xB,
			fire_c			= fire_min | 0xC,
			fire_d			= fire_min | 0xD,
			fire_e			= fire_min | 0xE,
			fire_f			= fire_min | 0xF,
			fire_max		= fire_f

			stop_mask			= 0x80
			stop_rotate_right	= rotate_right 	| stop_mask,
			stop_rotate_left	= rotate_left 	| stop_mask,
			stop_speed_up		= speed_up 		| stop_mask,
			stop_slow_down		= slow_down 	| stop_mask,
			stop_shift_right	= shift_right 	| stop_mask,
			stop_shift_left		= shift_left 	| stop_mask,
			stop_turbo			= turbo 		| stop_mask
		};
	}
	
	namespace subtype {
		enum type {
			red		= 0x01,
			blue	= 0x02
		};
	}
}

#endif //GUARD_DARK_MIR_PROTOCOL_PROTOCOL_HH_INCLUDED
