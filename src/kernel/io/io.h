#pragma once

namespace io {
	class bus {
		public:
			static void out(unsigned short port, unsigned char val);
			static unsigned char in(unsigned short port);
	};
}