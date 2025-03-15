#pragma once
#ifndef DUMPHDB
#define DUMPHDB

// DumpHDB Compiled Settings
// Default Values
#define DEFAULT_OUTPUT_FORMAT OCT
#define DEFAULT_OUTPUT_GROUPING DWORD
#define DEFAULT_BYTES_OFFSET 0
#define DEFAULT_BYTES_AMOUNT 0
#define DEFAULT_GROUPS_PER_LINE 4
#define DEFAULT_LINES_PER_BLOCK 32
#define DEFAULT_PRINT_TEXT_COLUMN true
#define DEFAULT_SHOW_BYTE_OFFSET true
#define DEFAULT_BYTE_OFFSET_FORMAT OCT
// Default Values
#define MAX_ARGS 20
#define OFFSET_PADDING "  "
#define TEXT_PADDING "    "
#define GROUP_SEPARATOR_PADDING " "
#define DYNAMIC_LINE_BUFFER true // This option enables the Dynamic Line Buffer which allocates the line buffer during the printing process with a calculated size, it may be a bit slower but is more memory efficient. 
#define LINE_BUFFER_SIZE 512 // If Dynamic Line Buffer is enabled Line Buffer Size will be ignored.
#define LINE_BUFFER_SAFETY_OVERHEAD 8 // If Dynamic Line Buffer is enabled this overhead will be added to the size of the linebuffer to avoid possible undefined behaviour.
// DumpHDB Compiled Settings

#define DUMPHDB_VER_MAJOR 1
#define DUMPHDB_VER_MINOR 0
#define DUMPHDB_VER_PATCH 4

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "bitops.h"
#include "printing.h"

#endif