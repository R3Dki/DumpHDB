#include "parsing.h"

const u8 group_bit_size[] = {1, 3, 4, 8, 16, 32, 64, 6, 9, 12, 15, 18, 24};
const u8 group_byte_size[] = {1, 3, 1, 1, 2, 4, 8, 6, 9, 12, 15, 18, 3};

// Expected Input Enum
enum expected_input {
    ARGUMENT,
    GROUPING
};

bool file_exists(const char* path) {
    FILE *file;
    file = fopen(path, "r");
    if (file != NULL) { fclose(file); return true; }
    return false;
}

u64 atoi_p(char s[]) {
    u64 n = 0;
    for (u32 i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}


void fail(const char* fail_message) {
    fprintf(stderr, "%s%s%s", "\x1B[0m\x1B[38;5;196m", fail_message, "\x1B[0m");
    exit(FAILURE);
}

void warning(const char* warning_message) {
     printf("%s%s%s", "\x1B[0m\x1B[38;5;226m", warning_message, "\x1B[0m");
}

bool pcmpstr(char* string1, char* string2) {
    while(*string1 == *string2++)
        if (*string1++ == '\0') return true;
    return false;
}

bool continue_flag = false, get_bytes_amount = false, get_bytes_offset = false, get_line_groups = false, get_lines_per_block = false;
const char
    *grouping_args[] =    {"bit",  "nibble", "byte",  "word",  "dword", "qword"};
const u8 list_size = ARRAY_SIZE(grouping_args);
u8 next_input = ARGUMENT;

void parse_args(i32 argc, char* argv[], u8* output_format, u8* output_grouping, u64 *bytes_offset, u64 *bytes_amount, u16 *groups_per_line, u32 *lines_per_block, bool *print_text_column, bool* show_byte_offset, bool* uppercase, u8* byte_offset_format, char** filename) {
    *output_format = DEFAULT_OUTPUT_FORMAT;
    *output_grouping = DEFAULT_OUTPUT_GROUPING;
    *bytes_offset = DEFAULT_BYTES_OFFSET;
    *bytes_amount = DEFAULT_BYTES_AMOUNT;
    *groups_per_line = DEFAULT_GROUPS_PER_LINE;
    *print_text_column = DEFAULT_PRINT_TEXT_COLUMN;
    *show_byte_offset = DEFAULT_SHOW_BYTE_OFFSET;
    *byte_offset_format = DEFAULT_BYTE_OFFSET_FORMAT;
    *lines_per_block = DEFAULT_LINES_PER_BLOCK;
    *uppercase = false;

    if (argc < 2) fail("Too few arguments. Use -h for the help page");
    if (argc >= MAX_ARGS) fail("Too many arguments. Use -h for the help page.");

    for (size i = 1; i < argc; i++) {
        if (get_bytes_amount) { *bytes_amount = atoi_p(argv[i]); get_bytes_amount = false; continue; }
        if (get_bytes_offset) { *bytes_offset = atoi_p(argv[i]); get_bytes_offset = false; continue; }
        if (get_line_groups)  { *groups_per_line = atoi_p(argv[i]); get_line_groups = false; continue; }
        if (get_lines_per_block)  { *lines_per_block = atoi_p(argv[i]); get_lines_per_block = false; continue; }

        if (next_input != ARGUMENT) {
            for (u8 j = 0; j < list_size; j++)
            if (pcmpstr(argv[i], (string)grouping_args[j])) {
                if (next_input == GROUPING) *output_grouping = ++j;
                continue_flag = true;
                next_input = ARGUMENT;
                break;
            }
        }
        
        if(continue_flag) { continue_flag = false; continue; }

        if (next_input == GROUPING)
            fail("Invalid grouping option. Use -h to display available grouping types.");

        if(argv[i][0] == '-' && next_input == ARGUMENT) { // Check if input is an option or filename
            if(pcmpstr(argv[i], "-v")) {
                printf("DumpHDB Version %d.%d.%d\nTypes Library Version %d.%d.%d\n\
Parsing Library Verion %d.%d.%d\nPrinting Library Version %d.%d.%d\n\
Bit Ops Library Version %d.%d.%d\nConversion Library Version %d.%d.%d\n\
Help Page Version %d.%d\n",
                DUMPHDB_VER_MAJOR, DUMPHDB_VER_MINOR, DUMPHDB_VER_PATCH,
                TYPES_LIB_VERSION_MAJOR,TYPES_LIB_VERSION_MINOR,TYPES_LIB_VERSION_PATCH,
                PARSING_LIB_VER_MAJOR, PARSING_LIB_VER_MINOR, PARSING_LIB_VER_PATCH,
                PRINTING_LIB_VER_MAJOR, PRINTING_LIB_VER_MINOR, PRINTING_LIB_VER_PATCH,
                BITOPS_LIB_VER_MAJOR, BITOPS_LIB_VER_MINOR, BITOPS_LIB_VER_PATCH,
                CONVERSION_LIB_VER_MAJOR, CONVERSION_LIB_VER_MINOR, CONVERSION_LIB_VER_PATCH,
                HELP_PAGE_VERSION_MAJOR, HELP_PAGE_VERSION_MINOR);
                exit(0);
            }
            if(pcmpstr(argv[i], "-h")) { printf("DumpHDB Version %d.%d.%d Help Page\n%s", DUMPHDB_VER_MAJOR, DUMPHDB_VER_MINOR, DUMPHDB_VER_PATCH, HELP_PAGE); exit(0); }
            if(pcmpstr(argv[i], "-g")) { next_input = GROUPING; continue; }
            if(pcmpstr(argv[i], "-b")) { *output_format = BIN; continue; }
            if(pcmpstr(argv[i], "-o")) { *output_format = OCT; continue; }
            if(pcmpstr(argv[i], "-d")) { *output_format = DEC; continue; }
            if(pcmpstr(argv[i], "-u")) { *output_format = UDEC; continue; }
            if(pcmpstr(argv[i], "-x")) { *output_format = HEX; continue; }
            if(pcmpstr(argv[i], "-X")) { *output_format = HEX; *uppercase = true; continue; }
            if(pcmpstr(argv[i], "-t")) { *output_format = ASCII; continue; }
            if(pcmpstr(argv[i], "-n")) { get_bytes_amount = true; continue; }
            if(pcmpstr(argv[i], "-r")) { get_bytes_offset = true; continue; }
            if(pcmpstr(argv[i], "-l")) { get_line_groups = true; continue; }
            if(pcmpstr(argv[i], "-p")) { *print_text_column = true; continue; }
            if(pcmpstr(argv[i], "-s")) { *show_byte_offset = true; continue; }
            if(pcmpstr(argv[i], "-a")) { *byte_offset_format = OCT; continue; }
            if(pcmpstr(argv[i], "-c")) { *byte_offset_format = DEC; continue; }
            if(pcmpstr(argv[i], "-e")) { *byte_offset_format = HEX; continue; }
            if(pcmpstr(argv[i], "-k")) { get_lines_per_block = true; continue; }
            fail("Invalid argument, Use -h for the help page.");
        }

        //*filename = malloc(256);
        if (file_exists(argv[i])) {
            //strcpy(*filename, argv[i]);
            *filename = argv[i];
            continue;
        }
        fail("File does not exist.");
    }

    if (*filename == NULL) fail("No file specified.");

    // Check for incompatible groupings

    if (*output_grouping == BIT && *output_format != BIN) {
        warning("Bit Grouping is not supported by any numerical system other than Binary, using Byte Grouping");
        *output_grouping = BYTE;
    }

    if (*output_format == HEX && *output_grouping == BIT) {
        warning("Hexadecimal does not support Bit Grouping, using Byte Grouping");
        *output_grouping = BYTE;
    }
    
    if ((*output_format == DEC || *output_format == UDEC) && *output_grouping == BIT) {
        warning("Decimal does not support Bit Grouping, using Byte Grouping");
        *output_grouping = BYTE;
    }

    if (*output_format == OCT && (*output_grouping == NIBBLE || *output_grouping == BIT)) {
        warning("Octal doesn't support the current Grouping Option, using Byte Grouping.");
        *output_grouping = BYTE;
    }
    // Check for incompatible groupings
}
