#include <kernel.h>
#include "graphics/graphics.h"

using namespace gfx;

const char* asd = "Hello, World" ;

extern "C" void _start() {
	//char str[] = "Hello, World";
	vga::print(asd);
	
	return;
}