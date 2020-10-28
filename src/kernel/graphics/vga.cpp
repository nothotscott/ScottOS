#include "vga.h"
#include "io/port.h"
#include "io/keyboard.h"
#include "structure/string.h"

using namespace io;
using namespace structure;

namespace gfx {
	void vga::set_cursor_position(ushort position) {
		port::out(0x3D4, 0x0F);
		port::out(0x3D5, (byte)(position & 0xFF));
		port::out(0x3D4, 0x0E);
		port::out(0x3D5, (byte)((position >> 8) & 0xFF));
		cursor_position = position;
	}

	void vga::set_cursor_delta(ushort delta) {
		set_cursor_position(cursor_position + delta);
	}

	void vga::set_cursor_coords(byte x, byte y) {
		set_cursor_position(get_position_from_coords(x, y));
	}

	ushort vga::get_position_from_coords(byte x, byte y) {
		return y * GFX_VGA_WIDTH + x;
	}

	void vga::print(string str, byte color) {
		byte* char_ptr = (byte*)str;
		ushort index = vga::cursor_position;
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
	void vga::print(const char* str, byte color) {
		print(string(str), color);
	}
	void vga::print(byte chr, byte color) {
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

	void vga::println(string str, byte color) {
		print(str, color);
		newline();
	}
	void vga::println(const char* str, byte color) {
		print(str, color);
		newline();
	}

	void vga::newline() {
		set_cursor_delta(GFX_VGA_WIDTH - cursor_position % GFX_VGA_WIDTH);
	}

	void vga::clear(byte color) {
		ulong color64 = (ulong)color;
		ulong value = (color64 << 8) + (color64 << 24) + (color64 << 40) + (color64 << 56);
		for (ulong* i = (ulong*)GFX_VGA_MEMORY; i < (ulong*)(GFX_VGA_MEMORY + GFX_VGA_WIDTH*GFX_VGA_HEIGHT*2); i++) {
			*i = value;
		}
		set_cursor_position(0);
	}

	void vga::print_memory(void* address, ulong length, byte bpr, byte color, byte header_color) {
		ulong start = (ulong)address - ((ulong)address % 8);
		if(header_color != 0) {
			print("Offset          ", header_color);
			for(byte i = 0; i < bpr; i++){
				print(' ', header_color);
				print(string::from_hex(i), header_color);
			}
			newline();
		}
		for(ulong row = start; row < start + length; row += bpr){
			print(string::from_hex(row), color);
			for(byte* ptr = (byte*)row; ptr < (byte*)(row + bpr) && ptr < (byte*)(start + length); ptr++){
				print(' ', color);
				print(string::from_hex(*ptr), color);
			}
			newline();
		}
	}


	void vga::key_event_handler(byte scan_code, byte chr){
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
