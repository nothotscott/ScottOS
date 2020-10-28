#pragma once

namespace mem {
	class memory {
		public:
			static void set(void*, ulong, ulong);
			static void copy(void*, void*, ulong);
	};

	const auto memset = memory::set;
	const auto memcpy = memory::copy;
}