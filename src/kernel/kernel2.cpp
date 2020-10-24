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
	vga::println("Welcome to ScottOS");
	vga::newline();
	
	void* test_addr1 = malloc(0x10);
	void* test_addr2 = malloc(0x10);
	void* test_addr3 = malloc(0x10);
	vga::println(string::from_hex((ulong)test_addr1));
	vga::println(string::from_hex((ulong)test_addr2));
	vga::println(string::from_hex((ulong)test_addr3));

	free(test_addr1);
	free(test_addr2);
	free(test_addr3);

	void* test_addr4 = malloc(0x60);
	vga::println(string::from_hex((ulong)test_addr4));

	return;
}

char temp_buffer[128];