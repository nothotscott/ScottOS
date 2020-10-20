#pragma once

#include "port.h"

#define IO_PIC1_COMMAND	0x20
#define IO_PIC1_DATA	0x21
#define IO_PIC2_COMMAND	0xA0
#define IO_PIC2_DATA	0xA1

#define IO_ICW1_INIT	0x10
#define IO_ICW1_ICW4	0x01
#define IO_ICW4_8086	0x01


namespace io {
	class pic {
		public:
			static void mask(){
				port::out(IO_PIC1_DATA, 0xFD);
				port::out(IO_PIC2_DATA, 0xFF);
			}

			static void remap(){
				byte d1, d2;
				d1 = port::in(IO_PIC1_DATA);
				d2 = port::in(IO_PIC2_DATA);

				port::out(IO_PIC1_COMMAND, IO_ICW1_INIT | IO_ICW1_ICW4);
				port::out(IO_PIC2_COMMAND, IO_ICW1_INIT | IO_ICW1_ICW4);
				port::out(IO_PIC1_DATA, 0);
				port::out(IO_PIC2_DATA, 8);
				port::out(IO_PIC1_DATA, 4);
				port::out(IO_PIC2_DATA, 2);
				port::out(IO_PIC1_DATA, IO_ICW4_8086);
				port::out(IO_PIC2_DATA, IO_ICW4_8086);
				
				port::out(IO_PIC1_DATA, d1);
				port::out(IO_PIC2_DATA, d2);
			}
	};
}