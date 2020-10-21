#include "heap.h"

namespace mem {
	void heap::initalize(ulong heap_address, ulong heap_length) {
		first = (segment_header*)heap_address;
		first->mem_length = heap_length - sizeof(segment_header);
		first->next = 0;
		first->prev = 0;
		first->next_free = 0;
		first->prev_free = 0;
		first->free = true;
	}

	void* heap::alloc(ulong size){
		ulong remainder = size % 8;
		size -= remainder;
		if (remainder != 0){
			size += 8;
		}
		segment_header* current = first;
		while(true){
			if(current->mem_length >= size) {
				return current + 1;
			}
		}
	}
}