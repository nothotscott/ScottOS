#pragma once

#include "string.h"

using namespace dstruct;

namespace dstruct {
	string::string(const char* ptr) {
		m_ptr = (char*)ptr;
		set_length();
	}
	string::string(char* ptr) {
		m_ptr = ptr;
		set_length();
	}
	string::string(const char* ptr, uint_32 length) {
		m_ptr = (char*)ptr;
		set_length(length);
	}
	string::string(char* ptr, uint_32 length) {
		m_ptr = ptr;
		set_length(length);
	}

	string string::from_float(float value, uint_8 scale) {
		string str = from_int(value);
		uint_8 int_length = str.get_length();
		*(str.m_ptr + int_length) = '.';

		if (value < 0) {
			value *= -1;
		}
		float digit = value - (unsigned int)value;
		for(uint_8 i = 0; i < scale; i++) {
			digit *= 10;
			*(str.m_ptr + int_length + 1 + i) = (unsigned int)digit + 48;
			digit -= (unsigned int)digit;
		}
		str.set_length(int_length+ scale + 1);
		*(str.m_ptr + str.get_length()) = 0;
		return str;
	}

	string::~string() {
	}


	string::operator uint_8*() const {
		return (uint_8*)m_ptr;
	};


	uint_32 string::get_length() {
		return m_length;
	}
	void string::set_length() {
		m_length = 0;
		while(*(m_ptr + m_length) != 0){
			m_length++;
		}
	}
	void string::set_length(uint_32 length) {
		m_length = length;
	}
}