#pragma once

#define MEM_MAP_USABLE_REGIONS_BUFFER_SIZE	5

namespace mem {
	struct map_entry {
		ulong base_address;
		ulong region_length;
		uint region_type;
		uint extended_attributes;
	};

	class map {
		public:
			static void set_usable_mem_regions(ulong*, byte);
		public:
			inline static byte usable_mem_regions_len;
			inline static map_entry* usable_mem_regions[MEM_MAP_USABLE_REGIONS_BUFFER_SIZE];
	};
}