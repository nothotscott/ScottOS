#pragma once

extern char temp_buffer[128];

namespace structure {
	class string {
		public:
			string(const char*);
			string(char*);
			string(const char*, uint length);
			string(char*, uint length);
			template<typename T>
			static structure::string from_hex(T);
			template<typename T>
			static structure::string from_int(T);
			static structure::string from_float(float, byte);
			~string();

			operator byte*() const;
			
			uint get_length();
			void set_length();
			void set_length(uint);
		private:
			char*		m_ptr;
			uint		m_length;
	};


	
	// do mem alloc version when implemented

	template<typename T>
	string string::from_hex(T value) {
		byte length = sizeof(T) * 2 - 1;
		T* val_ptr = &value;
		byte* ptr;
		byte nibble;
		for (byte i = 0; i < length; i++){
			ptr = (byte*)val_ptr + i;
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
		byte negative = false;
		if (value < 0){
			negative = true;
			value *= -1;
			temp_buffer[0] = '-';
		}

		ulong value64 = (ulong)value;
		byte length = negative;
		while (value64 / 10 > 0) {
			value64 /= 10;
			length++;
		}
		value64 = (ulong)value;
		byte i = 0;
		while(value64 / 10 > 0) {
			byte digit = value64 % 10;
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