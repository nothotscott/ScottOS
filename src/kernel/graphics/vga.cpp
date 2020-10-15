#pragma once

#include "vga.h"
#include "io/port.h"
#include "io/keyboard.h"
#include "structure/string.h"

using namespace io;
using namespace dstruct;

namespace gfx {
	void vga::set_cursor_position(uint_16 position) {
		port::out(0x3D4, 0x0F);
		port::out(0x3D5, (uint_8)(position & 0xFF));
		port::out(0x3D4, 0x0E);
		port::out(0x3D5, (uint_8)((position >> 8) & 0xFF));
		cursor_position = position;
	}

	void vga::set_cursor_delta(uint_16 delta) {
		set_cursor_position(cursor_position + delta);
	}

	void vga::set_cursor_coords(uint_8 x, uint_8 y) {
		set_cursor_position(get_position_from_coords(x, y));
	}

	uint_16 vga::get_position_from_coords(uint_8 x, uint_8 y) {
		return y * GFX_VGA_WIDTH + x;
	}

	void vga::print(string str, uint_8 color) {
		uint_8* char_ptr = (uint_8*)str;
		uint_16 index = vga::cursor_position;
		while (*char_ptr != 0) {
			switch(*char_ptr) {
				case '\n':
					index += GFX_VGA_WIDTH - index % GFX_VGA_WIDTH;
					break;
				case '\r':
					break;
				default:
					*(GFX_VGA_MEMORY + index * 2) = *char_ptr;
					*(GFX_VGA_MEMORY + index * 2 + 1) = color;
					index++;
					break;
			}
			char_ptr++;
		}
		set_cursor_position(index);
	}
	void vga::print(const char* str, uint_8 color) {
		print(string(str));
	}
	void vga::print(uint_8 chr, uint_8 color) {
		switch (chr) {
			case '\n':
				set_cursor_delta(GFX_VGA_WIDTH - cursor_position % GFX_VGA_WIDTH);
				break;
			default:
				*(GFX_VGA_MEMORY + vga::cursor_position * 2) = chr;
				*(GFX_VGA_MEMORY + vga::cursor_position * 2 + 1) = color;
				set_cursor_delta(1);
				break;
		}
	}

	void vga::println(string str, uint_8 color) {
		print(str);
		print('\n');
	}
	void vga::println(const char* str, uint_8 color) {
		print(str);
		print('\n');
	}

	void vga::clear(uint_8 color) {
		uint_64 color64 = (uint_64)color;
		uint_64 value = (color64 << 8) + (color64 << 24) + (color64 << 40) + (color64 << 56);
		for (uint_64* i = (uint_64*)GFX_VGA_MEMORY; i < (uint_64*)(GFX_VGA_MEMORY + GFX_VGA_WIDTH*GFX_VGA_HEIGHT*2); i++) {
			*i = value;
		}
		set_cursor_position(0);
	}


	void vga::key_event_handler(uint_8 scan_code, uint_8 chr){
		if (chr != 0) {
			if (kb::is_shift_down()){
				print(chr - 32);
			} else {
				print(chr);
			}
		} else {
			switch(scan_code) {
				case 0x8E:	// backspace
					set_cursor_delta(-1);
					print(' ');
					set_cursor_delta(-1);
					break;
				case 0x9C:	// Enter
					print('\n');
					break;
				case 0x50:	// Down arrow
					if(kb::is_special_key()) {
						set_cursor_delta(GFX_VGA_WIDTH);
					}
					break;
				case 0x48:	// Up arrow
					if(kb::is_special_key()) {
						set_cursor_delta(-GFX_VGA_WIDTH);
					}
					break;
				default:
					break;
			}
		}
	}
}
