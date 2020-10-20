#pragma once

namespace io {
	class port {
		public:
			static void out(ushort port, byte val);
			static byte in(ushort port);
	};
}