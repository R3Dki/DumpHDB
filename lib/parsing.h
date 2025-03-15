#pragma once
#ifndef PARSING_LIB
#define PARSING_LIB

#define PARSING_LIB_VER_MAJOR 1
#define PARSING_LIB_VER_MINOR 0
#define PARSING_LIB_VER_PATCH 3

#include "types.h"
#include "conversion.h"
#include "dumphdb.h"
#include "conversion.h"
#include "printing.h"
#include "help.h"

extern const u8 group_bit_size[];
extern const u8 group_byte_size[];

// Output Format Enum
enum format {
    BIN, // Binary
    OCT, // Octal
    DEC, // Decimal
    UDEC, // Unsigned Decimal
    HEX, // Hexadecimal
    ASCII // ASCII Text
};

// Output Grouping Enum
enum grouping {
    BIT, // 1 bit
    NIBBLE, // 4 bits
    BYTE = 3, // 8 bits
    WORD, // 16 bits
    DWORD, // 32 bits
    QWORD, // 64 bits
};

void exit(int exit_code);

void fail(const char* fail_messagge);

void warning(const char* warning_message);

bool pcmpstr(char* string1, char* string2);

void parse_args(i32 argc, char* argv[], u8* output_format, u8* output_grouping, u64 *bytes_offset, u64 *bytes_amount, u16 *groups_per_line, u32 *lines_per_block, bool* print_text_column, bool* show_byte_offset, bool* uppercase, u8* byte_offset_format, char** filename);

#endif // PARSING_LIB