#include "memory.h"

namespace mem {
	void memory::set(void* dest, ulong value, ulong num) {
		ulong bytes = num % 8;
		ulong qwords = num - bytes;
		// qword fill
		for(ulong* ptr = (ulong*)dest; ptr < (ulong*)((ulong)dest + qwords); ptr++){
			*ptr = value;
		}
		// byte fill
		byte* value_ptr = (byte*)&value;
		for (byte* ptr = (byte*)((ulong)dest + qwords); ptr < (byte*)((long)dest + num); ptr++){
			*ptr = *value_ptr;
			value_ptr++; // reframe the pointer to the 8 bit slice of a qword
		}
	}

	void memory::copy(void* dest, void* src, ulong num) {
		ulong bytes = num % 8;
		ulong qwords = num - bytes;
		ulong* src_ptr = (ulong*)src;
		// copy qwords
		for(ulong* ptr = (ulong*)dest; ptr < (ulong*)((ulong)dest + qwords); ptr++){
			*ptr = *src_ptr;
			src_ptr++;
		}
		// copy remaining bytes
		byte* src_ptr_byte = (byte*)((ulong)src + num);
		for (byte* ptr = (byte*)((ulong)dest + qwords); ptr < (byte*)((long)dest + num); ptr++){
			*ptr = *src_ptr_byte;
			src_ptr_byte++;
		}
	}
}