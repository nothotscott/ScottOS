#include "heap.h"
#include "memory.h"

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

	void* heap::alloc(ulong size) {
		ulong remainder = size % 8;
		size -= remainder;
		if (remainder != 0){
			size += 8;
		}
		segment_header* current = first;
		while(current->mem_length < size){
			if(current->next == 0) {		// physical memory limit reached
				return 0;
			}
			current = current->next_free;
		}
		if(current->mem_length > size + sizeof(segment_header)){	// make new free segment afterwards if there's room
			segment_header* seg = (segment_header*)((ulong)current + sizeof(segment_header) + size);
			seg->free = true;
			seg->mem_length = (ulong)(current->mem_length - sizeof(segment_header) + size);
			seg->next_free = current->next_free;
			seg->next = current->next;
			seg->prev_free = current;
			seg->prev = current->prev_free;
			
			current->next_free = seg;
			current->next = seg;
			current->mem_length = size;
		}
		if(current == first){				// make sure first is actually first
			first = current->next;
		}
		current->free = false;
		// Ensure linked list is correct
		if(current->prev_free != 0){
			current->prev_free->next_free = current->next_free;
		}
		if(current->next_free != 0){
			current->next_free->prev_free = current->prev_free;
		}
		if(current->prev != 0){
			current->prev->next_free = current->next_free;
		}
		if(current->next != 0){
			current->next->prev_free = current->prev_free;
		}
		return current + 1;
	}

	void* heap::calloc(ulong size) {
		void* address = alloc(size);
		memory::set(address, 0, size);
		return address;
	}

	void heap::free(void* address) {
		segment_header* current = ((segment_header*)address) - 1;
		current->free = true;
		if(current < first) {
			first = current;
		}
		// Reframe current segment header
		if(current->next_free != 0 && current->next_free->prev_free < current){
			current->next_free->prev_free = current;
		}
		if(current->prev_free != 0 && current->prev_free->next_free > current){
			current->prev_free->next_free = current;
		}
		if(current->next != 0){
			current->next->prev = current;
			if(current->next->free) {
				combine_free(current, current->next);
			}
		}
		if(current->prev != 0){
			current->prev->next = current;
			if(current->prev->free) {
				combine_free(current, current->prev);
			}
		}
	}

	void heap::combine_free(segment_header* seg1, segment_header* seg2){
		if(seg1 == 0 || seg2 == 0) {
			return;
		}
		if(seg1 < seg2){
			// seg1 expands to the end of seg2
			seg1->mem_length += seg2->mem_length + sizeof(segment_header);
			seg1->next = seg2->next;
			seg1->next_free = seg2->next_free;
			// seg2 relapses back to the begining of seg1
			seg2->next->prev = seg1;
			seg2->next_free->prev_free = seg1;
		} else {
			// seg2 expands to the end of seg1
			seg2->mem_length += seg1->mem_length + sizeof(segment_header);
			seg2->next = seg1->next;
			seg2->next_free = seg1->next_free;
			// seg1 relapses back to the begining of seg2
			seg1->next->prev = seg2;
			seg1->next_free->prev_free = seg2;
		}
	}
}