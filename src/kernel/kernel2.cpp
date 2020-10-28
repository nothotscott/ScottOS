#include <kernel.h>
#include "io/port.h"
#include "io/idt.h"
#include "io/pic.h"
#include "io/keyboard.h"
#include "graphics/vga.h"
#include "structure/string.h"
#include "memory/map.h"
#include "memory/heap.h"

/*	Additional implementations	*/
#include "interrupts.cpp"

using namespace io;
using namespace gfx;
using namespace structure;
using namespace mem;


extern ulong* mem_map_ptr;
extern byte mem_region_count;

void start_idt() {
	idt::initalize((idt64*)_idt, (ulong*)&_isr1, 1, 2);
	pic::remap();
	pic::mask();
	idt::load();
}

void setup() {
	start_idt();
	set_default_handlers();
	map::set_usable_mem_regions(mem_map_ptr, mem_region_count);
	heap::initalize(HEAP_START, HEAP_SIZE);
}

extern "C" void main() {
	setup();
	vga::clear();
	//vga::println("Welcome to ScottOS");
	const char* poop = "Test";
	vga::print(poop);
	vga::newline();

	vga::println(string::from_hex(poop));
	vga::print_memory((void*)((ulong)poop - 2), 16*3);
	
	byte* ptr = new byte[16];
	for(byte i = 0; i < 16; i++){
		ptr[i] = i;
	}
	//vga::print_memory(ptr, 16*2);
	vga::print(string::from_hex(0x1234));

	return;
}

char temp_buffer[0x4000];