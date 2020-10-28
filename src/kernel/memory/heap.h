#pragma once

#define MEM_HEAP_ALIGN_SIZE_BLOCKS	8

namespace mem {
	struct segment_header {
		ulong mem_length;
		segment_header* next;
		segment_header* prev;
		segment_header* next_free;
		segment_header* prev_free;
		bool free;
	};
	struct aligned_segment_header {
		ulong segment_header : 63;
		bool is_aligned : 1;
	};

	class heap {
		public:
			static void initalize(ulong, ulong);
			static void* alloc(ulong);
			static void* calloc(ulong); // "clear" alloc
			static void* realloc(void*, ulong);
			static void* aligned_alloc(ulong, ulong);
			static void free(void*);
			static void combine_free(segment_header*, segment_header*);
		private:
			inline static segment_header* first;
	};

	const auto malloc = heap::alloc;
	const auto calloc = heap::calloc;
	const auto realloc = heap::realloc;
	const auto amalloc = heap::aligned_alloc;
	const auto free = heap::free;
}