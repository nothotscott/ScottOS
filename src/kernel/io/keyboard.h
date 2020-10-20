#pragma once

namespace io {
	class kb {
		public:
			static void key_event_handler(byte scan_code, byte chr);
			static void key_cleanup_handler(byte scan_code, byte chr);
			static byte get_modifiers_down();
			static bool is_shift_down();
			static bool is_alt_down();
			static bool is_special_key();
		private:
			inline static byte modifiers_down = 0;
			inline static byte last_scan_code = 0;
		public:
			inline static const char scan_codes_1[] = {
				0, 0, '1', '2',
				'3', '4', '5', '6',
				'7', '8', '9', '0',
				'-', '=', 0, 0,
				'q', 'w', 'e', 'r',
				't', 'y', 'u', 'i',
				'o', 'p', '[', ']',
				0, 0, 'a', 's',
				'd', 'f', 'g', 'h',
				'j', 'k', 'l', ';',
				'\'', '`', 0, '\\',
				'z', 'x', 'c', 'v',
				'b', 'n', 'm', ',',
				'.', '/', 0, '*',
				0, ' '
			};
	};
}