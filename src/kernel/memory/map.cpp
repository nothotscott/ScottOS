#include "map.h"

using namespace structure;

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

	string map::tostring(map_entry* entry) {
		// Reimplement when there's dynamic memory
		/*print("Memory base");
		print(string::from_hex(entry->base_address));
		newline();
		print("Region length: ");
		print(string::from_int(entry->region_length));
		newline();
		print("Region type: ");
		print(string::from_int(entry->region_type));
		newline();
		print("Memory attributes: ");
		print(string::from_int(entry->extended_attributes));*/
		return string("test");
	}
};