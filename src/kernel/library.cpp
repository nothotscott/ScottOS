#include <kernel.h>

// Graphics
#include "graphics/vga.cpp"

// IO
#include "io/port.cpp"
#include "io/keyboard.cpp"

// Data structures
#include "structure/string.cpp"

// Memory
#include "memory/map.cpp"
#include "memory/heap.cpp"
#include "memory/memory.cpp"


/* Operator implementations */
void* operator new(size_t size) {
	return mem::heap::alloc(size);
}
void* operator new[](size_t size) {
	return mem::heap::alloc(size);
}
void operator delete(void* p, size_t) {
	mem::heap::free(p);
}
void operator delete[](void* p, size_t) {
	mem::heap::free(p);
}