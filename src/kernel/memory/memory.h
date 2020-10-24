#pragma once

namespace mem {
	class memory {
		public:
			static void set(void*, ulong, ulong);
	};

	const auto memset = memory::set;
}