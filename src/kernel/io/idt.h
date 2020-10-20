#pragma once

#include "port.h"

#define IO_IDT_SIZE	256

extern "C" void _load_idt();

//Interrupt descriptor table
namespace io {
	struct idt64 {
		ushort	offset_low;
		ushort	selector;
		byte	ist;
		byte	types_attr;
		ushort	offset_mid;
		uint	offset_high;
		uint	zero;
	};

	class idt {
		public:
			static void initalize(idt64* tables, ulong* isr1_ptr, ushort offset = 0, ushort size = IO_IDT_SIZE){
				for(ushort i = offset; i < size; i++){
					tables[i].zero = 0;
					tables[i].offset_low = (ushort)((ulong)isr1_ptr & 0x000000000000FFFF);
					tables[i].offset_mid = (ushort)(((ulong)isr1_ptr & 0x00000000FFFF0000) >> 16);
					tables[i].offset_high = (uint)(((ulong)isr1_ptr & 0xFFFFFFFF00000000) >> 32);
					tables[i].ist = 0;
					tables[i].selector = 0x08;
					tables[i].types_attr = 0x8E;
				}
			}

			static void load() {
				_load_idt();
			}
	};
}