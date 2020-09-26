#pragma once

#define GFX_VGA_MEMORY	(uint_8*)	0xb8000
#define GFX_VGA_WIDTH	(uint_8)	80

namespace gfx {
	class vga {
		private:
			inline static uint_16 cursor_position = 0;
		public:
			static void set_cursor_position(uint_16);
			static void set_cursor_coords(uint_8, uint_8);
			static uint_16 get_position_from_coords(uint_8, uint_8);
			static void print(const char*);
	};
}