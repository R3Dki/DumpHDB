#pragma once
#ifndef PRINTING_LIB
#define PRINTING_LIB

#define PRINTING_LIB_VER_MAJOR 1
#define PRINTING_LIB_VER_MINOR 1
#define PRINTING_LIB_VER_PATCH 0

#include "dumphdb.h"
#include "parsing.h"
#include "escape_codes.h"

void print_file(char* filename, u64 offset, u64 bytes_amount, u8 format, u8 grouping, u16 groups_per_line, u32 lines_per_block, bool show_byte_offset, u8 byte_offset_format, bool uppercase, bool text_column);

#endif // PRINTING_LIB