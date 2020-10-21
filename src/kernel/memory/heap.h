#pragma once

namespace mem {
	struct segment_header {
		ulong mem_length;
		segment_header* next;
		segment_header* prev;
		segment_header* next_free;
		segment_header* prev_free;
		bool free;
	};

	class heap {
		public:
			static void initalize(ulong, ulong);
			static void* alloc(ulong);
		private:
			inline static segment_header* first;
	};
}

const auto malloc = mem::heap::alloc;