#pragma once

//extern uint_8 mem_region_count;

namespace mem {
	struct map_entry {
		uint_64 base_address;
		uint_64 region_length;
		uint_32 region_type;
		uint_32 extended_attributes;
	};
}