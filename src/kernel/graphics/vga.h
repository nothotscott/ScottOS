#pragma once

#include "structure/string.h"
#include "memory/map.h"

#define GFX_VGA_MEMORY	(byte*)	0xb8000
#define GFX_VGA_WIDTH				80
#define GFX_VGA_HEIGHT				25
#define GFX_VGA_DEFAULT_CLEAR_COLOR	GFX_VGA_BG_BLUE | GFX_VGA_FG_WHITE
#define GFX_VGA_DEFAULT_TEXT_COLOR	GFX_VGA_BG_BLACK | GFX_VGA_FG_WHITE


#define GFX_VGA_BG_BLACK			0x00
#define GFX_VGA_BG_BLUE				0x10
#define GFX_VGA_BG_GREEM			0x20
#define GFX_VGA_BG_CYAN				0x30
#define GFX_VGA_BG_RED				0x40
#define GFX_VGA_BG_MAGENTA			0x50
#define GFX_VGA_BG_BROWN			0x60
#define GFX_VGA_BG_LIGHTGRAY		0x70
#define GFX_VGA_BG_BLINKINGBLACK	0x80
#define GFX_VGA_BG_BLINKINGBLUE		0x90
#define GFX_VGA_BG_BLINKINGGREEN	0xA0
#define GFX_VGA_BG_BLINKINGCYAN		0xB0
#define GFX_VGA_BG_BLINKINGRED		0xC0
#define GFX_VGA_BG_BLINKINGMAGENTA	0xD0
#define GFX_VGA_BG_BLINKINGYELLOW	0xE0
#define GFX_VGA_BG_BLINKINGWHITE	0xF0

#define GFX_VGA_FG_BLACK			0x00
#define GFX_VGA_FG_BLUE				0x01
#define GFX_VGA_FG_GREEM			0x02
#define GFX_VGA_FG_CYAN				0x03
#define GFX_VGA_FG_RED				0x04
#define GFX_VGA_FG_MAGENTA			0x05
#define GFX_VGA_FG_BROWN			0x06
#define GFX_VGA_FG_LIGHTGRAY		0x07
#define GFX_VGA_FG_DARKGRAY			0x08
#define GFX_VGA_FG_LIGHTBLUE		0x09
#define GFX_VGA_FG_LIGHTGREEN		0x0A
#define GFX_VGA_FG_LIGHTCYAN		0x0B
#define GFX_VGA_FG_LIGHTRED			0x0C
#define GFX_VGA_FG_LIGHTMAGENTA		0x0D
#define GFX_VGA_FG_YELLOW			0x0E
#define GFX_VGA_FG_WHITE			0x0F



namespace gfx {
	class vga {
		public:
			static void set_cursor_position(ushort);
			static void set_cursor_delta(ushort);
			static void set_cursor_coords(byte, byte);
			static ushort get_position_from_coords(byte, byte);
			static void print(structure::string, byte = GFX_VGA_DEFAULT_TEXT_COLOR);
			static void print(const char*, byte = GFX_VGA_DEFAULT_TEXT_COLOR);
			static void print(byte, byte = GFX_VGA_DEFAULT_TEXT_COLOR);
			static void println(structure::string, byte = GFX_VGA_DEFAULT_TEXT_COLOR);
			static void println(const char*, byte = GFX_VGA_DEFAULT_TEXT_COLOR);
			static void newline();
			static void clear(byte = GFX_VGA_DEFAULT_CLEAR_COLOR);

			static void key_event_handler(byte scan_code, byte chr);
		private:
			inline static ushort cursor_position;
	};
}