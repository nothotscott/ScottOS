#pragma once

#include "port.h"

namespace io {
	void port::out(ushort port, byte val) {
		asm volatile ("outb %0, %1"
					:
					: "a"(val), "Nd"(port));
	}

	byte port::in(ushort port) {
		byte ret;
		asm volatile ("inb %1, %0"
					: "=a"(ret)
					: "Nd"(port));
		return ret;
	}
}