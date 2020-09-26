#pragma once

#include "graphics.h"
#include "io/io.h"

using namespace io;

namespace gfx {
	void vga::set_cursor_position(uint_16 position) {
		bus::out(0x3D4, 0x0F);
		bus::out(0x3D5, (uint_8)(position & 0xFF));
		bus::out(0x3D4, 0x0E);
		bus::out(0x3D5, (uint_8)((position >> 8) & 0xFF));
		vga::cursor_position = position;
	}

	void vga::set_cursor_coords(uint_8 x, uint_8 y) {
		vga::set_cursor_position(vga::get_position_from_coords(x, y));
	}

	uint_16 vga::get_position_from_coords(uint_8 x, uint_8 y) {
		return y * GFX_VGA_WIDTH + x;
	}

	void vga::print(const char* str) {
		uint_8* char_ptr = (uint_8*)str;
		uint_16 index = vga::cursor_position;
		while (*char_ptr != 0) {
			*(GFX_VGA_MEMORY + index * 2) = *char_ptr;
			index++;
			char_ptr++;
		}
		vga::set_cursor_position(index);
	}
}
