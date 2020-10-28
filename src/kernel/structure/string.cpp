#include "string.h"

using namespace structure;

namespace structure {
	string::string(){
		m_ptr = 0;
		set_length(0);
	}
	string::string(const char* ptr) {
		m_ptr = (char*)ptr;
		set_length();
	}
	string::string(char* ptr) {
		m_ptr = ptr;
		set_length();
	}
	string::string(const char* ptr, uint length) {
		m_ptr = (char*)ptr;
		set_length(length);
	}
	string::string(char* ptr, uint length) {
		m_ptr = ptr;
		set_length(length);
	}
	string::string(string& str) {
		m_ptr = str.m_ptr;
		set_length(str.get_length());
	}

	string string::from_float(float value, byte scale) {
		string str = from_int(value);
		byte int_length = str.get_length();
		*(str.m_ptr + int_length) = '.';

		if (value < 0) {
			value *= -1;
		}
		float digit = value - (unsigned int)value;
		for(byte i = 0; i < scale; i++) {
			digit *= 10;
			*(str.m_ptr + int_length + 1 + i) = (unsigned int)digit + 48;
			digit -= (unsigned int)digit;
		}
		str.set_length(int_length+ scale + 1);
		*(str.m_ptr + str.get_length()) = 0;
		return str;
	}

	string::~string() {
		//delete m_ptr;
	}


	string::operator byte*() const {
		return (byte*)m_ptr;
	};


	uint string::get_length() {
		return m_length;
	}
	void string::set_length() {
		m_length = 0;
		while(*(m_ptr + m_length) != 0){
			m_length++;
		}
	}
	void string::set_length(uint length) {
		m_length = length;
	}
}