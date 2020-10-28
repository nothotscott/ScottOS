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

	void* heap::realloc(void* address, ulong size) {
		segment_header* seg;
		aligned_segment_header* ash = (aligned_segment_header*)address - 1;
		if(ash->is_aligned) {
			seg = (segment_header*)(ulong)ash->segment_header;
		} else{
			seg = (segment_header*)address - 1;
		}

		ulong smaller_size = seg->mem_length < size ? seg->mem_length : size;
		void* new_address = alloc(size);
		memory::copy(new_address, address, size);
		free(address);
		return new_address;
	}

	void* heap::aligned_alloc(ulong alignment, ulong size) {
		// Align alignment by byte
		ulong alignment_rem = alignment % MEM_HEAP_ALIGN_SIZE_BLOCKS;
		alignment -= alignment_rem;
		alignment += alignment_rem == 0 ? 0 : MEM_HEAP_ALIGN_SIZE_BLOCKS;
		// Align size by byte
		ulong size_rem = size % MEM_HEAP_ALIGN_SIZE_BLOCKS;
		size -= size_rem;
		size += size_rem == 0 ? 0 : MEM_HEAP_ALIGN_SIZE_BLOCKS;
		// Allocate full size without overflow but is sorta wasteful
		void* address = alloc(size + alignment);
		ulong address_aligned = (ulong)address;
		// Align address along alignment
		ulong rem = address_aligned % alignment;
		address_aligned -= rem;
		if(rem != 0) {	// can't reuse existing heap functions if the address isn't perfectly on the alignment
			address_aligned += alignment;
			aligned_segment_header* ash = (aligned_segment_header*)address_aligned - 1;
			ash->is_aligned = true;
			ash->segment_header = (ulong)address - sizeof(segment_header);
		}
		return (void*)address_aligned;
	}

	void heap::free(void* address) {
		segment_header* current;
		// Get current based on if it's an aligned header or not
		aligned_segment_header* ash = (aligned_segment_header*)address - 1;
		if(ash->is_aligned) {
			current = (segment_header*)(ulong)ash->segment_header;
		} else {
			current = (segment_header*)address - 1;
		}
		/*if(current->prev == 0 && current->next == 0){
			return;
		}*/

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