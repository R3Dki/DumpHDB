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
#define LINE_BUFFER_SIZE 512
// DumpHDB Compiled Settings

#define DUMPHDB_VER_MAJOR 1
#define DUMPHDB_VER_MINOR 0
#define DUMPHDB_VER_PATCH 2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "bitops.h"
#include "printing.h"

#endif