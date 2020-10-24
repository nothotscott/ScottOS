#include "memory.h"

namespace mem {
	void memory::set(void* start, ulong value, ulong num) {
		ulong bytes = num % 8;
		ulong qwords = num - bytes;
		// qword fill
		for(ulong* ptr = (ulong*)start; ptr < (ulong*)((ulong)start + qwords); ptr++){
			*ptr = value;
		}
		// byte fill
		byte* value_ptr = (byte*)&value;
		for (byte* ptr = (byte*)((ulong)start + qwords); ptr < (byte*)((long)start + num); ptr++){
			*ptr = *value_ptr;
			value_ptr++; // reframe the pointer to the 8 bit slice of a qword
		}
	}
}