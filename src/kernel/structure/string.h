#pragma once

extern char temp_buffer[128];

namespace dstruct {
	class string {
		public:
			string(const char*);
			string(char*);
			string(const char*, uint_32 length);
			string(char*, uint_32 length);
			template<typename T>
			static dstruct::string from_hex(T);
			template<typename T>
			static dstruct::string from_int(T);
			static dstruct::string from_float(float, uint_8);
			~string();

			operator uint_8*() const;
			
			uint_32 get_length();
			void set_length();
			void set_length(uint_32);
		private:
			char*		m_ptr;
			uint_32		m_length;
	};


	
	// do mem alloc version when implemented

	template<typename T>
	string string::from_hex(T value) {
		uint_8 length = sizeof(T) * 2 - 1;
		T* val_ptr = &value;
		uint_8* ptr;
		uint_8 nibble;
		for (uint_8 i = 0; i < length; i++){
			ptr = (uint_8*)val_ptr + i;
			nibble = (*ptr & 0xF0) >> 4;
			temp_buffer[length - (i * 2 + 1)] = nibble + (nibble > 9 ? 55 : 48);
			nibble = *ptr & 0x0F;
			temp_buffer[length - (i * 2)] = nibble + (nibble > 9 ? 55 : 48);
		}
		temp_buffer[length + 1] = 0;
		return string(temp_buffer, length);
	}

	template<typename T>
	string string::from_int(T value) {
		uint_8 negative = false;
		if (value < 0){
			negative = true;
			value *= -1;
			temp_buffer[0] = '-';
		}

		uint_64 value64 = (uint_64)value;
		uint_8 length = negative;
		while (value64 / 10 > 0) {
			value64 /= 10;
			length++;
		}
		value64 = (uint_64)value;
		uint_8 i = 0;
		while(value64 / 10 > 0) {
			uint_8 digit = value64 % 10;
			value64 /= 10;
			temp_buffer[length - i] = digit + 48;
			i++;
		}
		temp_buffer[negative] = (value64 % 10) + 48;
		temp_buffer[length + 1] = 0;
		length++;
		return string(temp_buffer, length);
	}
}