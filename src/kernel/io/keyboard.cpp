#pragma once

#include "keyboard.h"
#include "graphics/vga.h"

using namespace gfx;

namespace io {
	void kb::key_event_handler(byte scan_code, byte chr){
		switch(scan_code) {
			case 0x2A:	// left shift down
				modifiers_down |= 1;
				break;
			case 0xAA:	// left shift up
				modifiers_down &= 0xFF - 1;
				break;	
			case 0x36:	// right shift down
				modifiers_down |= 2;
				break;
			case 0xB6:	// right shift up
				modifiers_down &= 0xFF - 2;
				break;
			case 0x38:
				if(is_special_key()) {
					modifiers_down |= 8;		// right alt down
				} else {
					modifiers_down |= 4;		// left alt down
				}
				break;
			case 0xBA:
				if(is_special_key()) {
					modifiers_down &= 0xFF - 8;	// right alt up
				} else {
					modifiers_down &= 0xFF - 4;	// left alt up
				}
				break;
		}
	}
	void kb::key_cleanup_handler(byte scan_code, byte chr) {
		last_scan_code = scan_code;
	}

	byte kb::get_modifiers_down() {
		return modifiers_down;
	}
	bool kb::is_shift_down() {
		return (modifiers_down & 0b00000011) != 0;
	}
	bool kb::is_alt_down() {
		return (modifiers_down & 0b00001100) != 0;
	}

	bool kb::is_special_key() {
		return last_scan_code == 0xE0;
	}
}