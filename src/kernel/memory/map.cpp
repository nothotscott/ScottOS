#pragma once

#include "map.h"

namespace mem {
	void map::set_usable_mem_regions(ulong* mem_map_ptr, byte mem_region_count) {
		usable_mem_regions_len = 0;
		for(byte i = 0; i < mem_region_count; i++) {
			map_entry* entry = (map_entry*)mem_map_ptr + i;
			if (entry->region_type != 1) {
				continue;
			}
			usable_mem_regions[usable_mem_regions_len] = entry;
			usable_mem_regions_len++;
		}
	}
};