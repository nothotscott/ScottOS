#pragma once

#include "port.h"

#define IO_IDT_SIZE	256

extern "C" void _load_idt();

//Interrupt descriptor table
namespace io {
	struct idt64 {
		uint_16	offset_low;
		uint_16	selector;
		uint_8	ist;
		uint_8	types_attr;
		uint_16	offset_mid;
		uint_32	offset_high;
		uint_32	zero;
	};

	class idt {
		public:
			static void initalize(idt64* tables, uint_64* isr1_ptr, uint_16 offset = 0, uint_16 size = IO_IDT_SIZE){
				for(uint_16 i = offset; i < size; i++){
					tables[i].zero = 0;
					tables[i].offset_low = (uint_16)((uint_64)isr1_ptr & 0x000000000000FFFF);
					tables[i].offset_mid = (uint_16)(((uint_64)isr1_ptr & 0x00000000FFFF0000) >> 16);
					tables[i].offset_high = (uint_32)(((uint_64)isr1_ptr & 0xFFFFFFFF00000000) >> 32);
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