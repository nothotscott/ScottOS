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
			static void* calloc(ulong);
			static void free(void* addess);
			static void combine_free(segment_header*, segment_header*);
		private:
			inline static segment_header* first;
	};

	const auto malloc = heap::alloc;
	const auto calloc = heap::calloc;
	const auto free = heap::free;
}