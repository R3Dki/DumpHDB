#pragma once
#ifndef CONVERSION_LIB
#define CONVERSION_LIB

#define CONVERSION_LIB_VER_MAJOR 1
#define CONVERSION_LIB_VER_MINOR 0
#define CONVERSION_LIB_VER_PATCH 1

#include "dumphdb.h"

//byte get_oct_digit(byte data); // ???

byte get_hex_digit(byte data, bool second_digit);

byte byte_from_word(word data, bool second_byte);

byte byte_from_dword(dword data, u8 byte_number);

byte byte_from_qword(dword data, u8 byte_number);

word word_from_bytes(byte byte1, byte byte2);

dword dword_from_bytes(byte byte1, byte byte2, byte byte3, byte byte4);

qword qword_from_bytes(byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7, byte byte8);


#endif // CONVERSION LIB