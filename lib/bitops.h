#pragma once
#ifndef BITOPS_LIB
#define BITOPS_LIB

// BitOps Library Compiled Settings
#define DISABLE_BITGROUP_FUNCTIONS 0
// BitOps Library Compiled Settings

#define BITOPS_LIB_VER_MAJOR 1
#define BITOPS_LIB_VER_MINOR 2
#define BITOPS_LIB_VER_PATCH 1

#include "types.h"

// Gets specified bit from byte
// This is unsafe as it accepts bit_number values greater than 7 which results in undefined behaviour.
bool getbit(byte data, u8 bit_number);

// Checks if bit_number is in bounds and gets the specified bit from the byte.
// This alternative is better for security reasons, although it's slightly slower.
bool getbit_s(byte data, u8 bit_number);

// Gets specified bit from word
// This is unsafe as it accepts bit_number values greater than 15 which results in undefined behaviour.
bool wgetbit(word data, u8 bit_number);

// Checks if bit_number is in bounds and gets the specified bit from the byte.
// This alternative is better for security reasons, although it's slightly slower.
bool wgetbit_s(word data, u8 bit_number);

// Gets specified bit from byte
// This is unsafe as it accepts bit_number values greater than 31 which results in undefined behaviour.
bool dgetbit(dword data, u8 bit_number);

// Checks if bit_number is in bounds and gets the specified bit from the byte.
// This alternative is better for security reasons, although it's slightly slower.
bool dgetbit_s(dword data, u8 bit_number);

// Gets specified bit from qword.
// This is unsafe as it accepts bit_number values greater than 63 which results in undefined behaviour.
bool qgetbit(qword data, u8 bit_number);

// Checks if bit_number is in bounds and gets the specified bit from the byte.
// This alternative is better for security reasons, although it's slightly slower.
bool qgetbit_s(qword data, u8 bit_number);

// Gets the specified bit from a block.
bool getbit_block(block data, u64 block_size, u64 bit_number); // WORKING (NEEDS TO BE CHECKED)

byte getbyte_block(block data, u64 byte_number);

// Gets the specified bit from a page.
bool getbit_page(page data, u64 bit_number); // WORKING (NEEDS TO BE CHECKED)

// Gets the specified byte from a page
byte getbyte_page(page data, u64 bit_number);

// Gets a nibble from a byte.
nibble get_nibble(byte data, bool second_half);

// Checks whether a nibble is valid or not
// by comparing the first 4 bits with a bit mask.
// A valid nibble CAN'T have any of the first 4 bits set to 1.
// 00001111(Valid), 11110000(Invalid)
bool is_nibble_valid(nibble nibble_to_validate);

// Gets a group of bits from a byte.
// UNSAFE
bitgroup get_bitgroup_byte(byte data, u8 offset, u8 group_size);

// Gets a group of bits from a word.
// UNSAFE
bitgroup get_bitgroup_word(word data, u8 offset, u8 group_size);

// Gets a group of bits from a dword.
// UNSAFE
bitgroup get_bitgroup_dword(dword data, u8 offset, u8 group_size);

// Gets a group of bits from a qword.
// UNSAFE
bitgroup get_bitgroup_qword(qword data, u8 offset, u8 group_size);

#endif // BITOPS_LIB