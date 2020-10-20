#include <kernel.h>
#include "io/port.h"
#include "io/idt.h"
#include "io/pic.h"
#include "io/keyboard.h"
#include "graphics/vga.h"
#include "structure/string.h"
#include "memory/map.h"

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
}

extern "C" void main() {
	setup();
	vga::clear();
	vga::println("Welcome to ScottOS");
	vga::newline();
	
	for(byte i = 0; i < map::usable_mem_regions_len; i++) { // mem_region_count map::usable_mem_regions_len
		map_entry* entry = map::usable_mem_regions[i]; // (map_entry*)mem_map_ptr map::usable_mem_regions[i]
		vga::print(entry);
		vga::newline();
		vga::newline();
	}

	return;
}

char temp_buffer[128];