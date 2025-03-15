#include "conversion.h"

//u8 get_oct_digit(byte data); // ???

u8 get_hex_digit(byte data, bool second_digit) {
    return get_bitgroup_byte(data, 4 * second_digit, 8);
}

byte byte_from_word(word data, bool second_byte) {
    return get_bitgroup_word(data, 8 * second_byte, 8);
}

byte byte_from_dword(dword data, u8 byte_number) {
    return get_bitgroup_dword(data, 8 * byte_number, 8);
}

byte byte_from_qword(dword data, u8 byte_number) {
    return get_bitgroup_qword(data, 8 * byte_number, 8);
}

word word_from_bytes(byte byte1, byte byte2) {
    return (word)byte1 << 8 | byte2;
}

dword dword_from_bytes(byte byte1, byte byte2, byte byte3, byte byte4) {
    return ((dword)byte1 << 8) | ((dword)byte2 << 16) | ((dword)byte3 << 24) | byte4;
}

qword qword_from_bytes(byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7, byte byte8) {
    return ((qword)byte1 << 8) | ((qword)byte2 << 16) | ((qword)byte3 << 24) |
           ((qword)byte4 << 32) | ((qword)byte5 << 40) | ((qword)byte6 << 48) |
           ((qword)byte7 << 56) | byte8;
}