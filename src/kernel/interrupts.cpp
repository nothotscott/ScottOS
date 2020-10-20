#pragma once

#define	EVENT_HANDLERS_BUFFER_SIZE	8

using namespace io;
using namespace gfx;
using namespace structure;

extern idt64 _idt[IO_IDT_SIZE];
extern ulong _isr1;

// TODO dynamically allocate event handler arrays after memalloc
void (*key_event_handlers[EVENT_HANDLERS_BUFFER_SIZE])(byte scan_code, byte chr);
void (*key_cleanup_handlers[EVENT_HANDLERS_BUFFER_SIZE])(byte scan_code, byte chr);

void set_default_handlers(){
	key_event_handlers[0] = kb::key_event_handler;
	key_event_handlers[1] = vga::key_event_handler;
	key_cleanup_handlers[0] = kb::key_cleanup_handler;
}


extern "C" void _isr1_handler() {
	byte scan_code = port::in(0x60);
	byte chr = 0;
	if (scan_code < 0x3A) {
		chr = kb::scan_codes_1[scan_code];
	}
	for(byte i = 0; i < EVENT_HANDLERS_BUFFER_SIZE; i++) {
		if (key_event_handlers[i] != 0) {
			key_event_handlers[i](scan_code, chr);
		}
	}
	for(byte i = 0; i < EVENT_HANDLERS_BUFFER_SIZE; i++) {
		if (key_cleanup_handlers[i] != 0) {
			key_cleanup_handlers[i](scan_code, chr);
		}
	}
	port::out(IO_PIC1_COMMAND, 0x20);
	port::out(IO_PIC2_COMMAND, 0x20);
}