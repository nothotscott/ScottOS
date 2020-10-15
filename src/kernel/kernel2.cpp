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
using namespace dstruct;
using namespace mem;

void start_idt() {
	idt::initalize((idt64*)_idt, (uint_64*)&_isr1, 1, 2);
	pic::remap();
	pic::mask();
	idt::load();
}

//extern uint_8 mem_region_count;

extern "C" void main() {
	//start_idt();
	//set_default_handlers();
	vga::clear();
	vga::println("Welcome to ScottOS");
	//vga::println(string::from_int(mem_region_count));

	return;
}

char temp_buffer[128];