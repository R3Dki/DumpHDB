#include "printing.h"
#include "conversion.h"
#include "parsing.h"

u64 file_counter = 0;

void skip_bytes (FILE* file, u32 bytes_to_skip) {
    for (u32 i = 0; i < bytes_to_skip; i++) {
        fgetc(file);
        if (feof(file)) fail("Skipped reading the whole file. Please select a smaller reading offset.");
        file_counter++;
    }
}

u64 byte_counter = 0;
void print_byte_offset (u32 bytes_per_line, u8 format) {
    switch (format) {
        case DEC:
            printf("%07llu%s", byte_counter, OFFSET_PADDING);
            break;
        case HEX:
            printf("%06llX%s", byte_counter, OFFSET_PADDING);
            break;
        case OCT:
            printf("%07llo%s", byte_counter, OFFSET_PADDING);
            break;
        default:
            fail("Invalid Offset Printing Format.");
            break;
    }
    byte_counter += bytes_per_line;
}

#if !DYNAMIC_LINE_BUFFER
    byte linebuffer[LINE_BUFFER_SIZE];
#else
byte* linebuffer;
#endif

void print_ascii_column(u32 line_bytes) {
    ecput(TEXT_PADDING);
    for(u32 i = 0; i < line_bytes + 1; i++) {
        if (linebuffer[i] == '\n') linebuffer[i] = 217;
        if (linebuffer[i] == '\r') linebuffer[i] = 174;
        printf("%c", linebuffer[i]);
    }
}

bool reached_amount = false;
u32 read_up_to = 0, line_char_counter = 0;
u64 old_file_counter = 0;

void increase_file_counter(u8 increment_amount) {
    file_counter += increment_amount;
    line_char_counter += increment_amount;
}

void print_file(char* filename, u64 offset, u64 bytes_amount, u8 format, u8 grouping, u16 groups_per_line, u32 lines_per_block, bool show_byte_offset, u8 byte_offset_format, bool uppercase, bool text_column) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) fail("Couldn't open file.");
    if (offset) skip_bytes(file, offset);

    u32 line_bytes = (u32)(groups_per_line * group_byte_size[grouping]),
        block_lines_counter = 0;
    u8 bit_grouping_counter = 0;
    byte bytebuffer = 0;

#if DYNAMIC_LINE_BUFFER
    linebuffer = malloc(line_bytes + LINE_BUFFER_SAFETY_OVERHEAD);
    for (size i = 0; i < line_bytes + LINE_BUFFER_SAFETY_OVERHEAD - 4; i++) linebuffer[i] = 0;
#else
    if (line_bytes > LINE_BUFFER_SIZE) fail("Line Buffer too small to work properly. Recompile with a greater LINE_BUFFER_SIZE definition or enable the Dynamic Line Buffer compiled setting.");
#endif
    if (show_byte_offset) print_byte_offset(line_bytes, byte_offset_format);

    while(!feof(file)) {
        switch(format) {
            case BIN:
                increase_file_counter(1);
                bytebuffer = fgetc(file);
                linebuffer[line_char_counter] = bytebuffer;
                switch (grouping) {
                    case BIT:
                        printf("%u %u %u %u %u %u %u %u ",
                            getbit(bytebuffer, 0), getbit(bytebuffer, 1),
                            getbit(bytebuffer, 2), getbit(bytebuffer, 3),
                            getbit(bytebuffer, 4), getbit(bytebuffer, 5),
                            getbit(bytebuffer, 6), getbit(bytebuffer, 7));
                        
                        break;
                    case NIBBLE:
                        printf("%u%u%u%u ",
                            getbit(bytebuffer, 0), getbit(bytebuffer, 1),
                            getbit(bytebuffer, 2), getbit(bytebuffer, 3));
                        if (groups_per_line <= 1) { puts(""); if (show_byte_offset) print_byte_offset(line_bytes, byte_offset_format); }
                        printf("%u%u%u%u",
                            getbit(bytebuffer, 4), getbit(bytebuffer, 5),
                            getbit(bytebuffer, 6), getbit(bytebuffer, 7));
                        break;
                    default:
                        printf("%u%u%u%u%u%u%u%u",
                            getbit(bytebuffer, 0), getbit(bytebuffer, 1),
                            getbit(bytebuffer, 2), getbit(bytebuffer, 3),
                            getbit(bytebuffer, 4), getbit(bytebuffer, 5),
                            getbit(bytebuffer, 6), getbit(bytebuffer, 7));
                        break;
                }
                break;
            case OCT:
                //-----------------------------
                switch (grouping) {
                    case NIBBLE:
                        increase_file_counter(1);
                        bytebuffer = fgetc(file);
                        linebuffer[line_char_counter] = bytebuffer;
                        printf("%02o %02o", get_nibble(bytebuffer, true), get_nibble(bytebuffer, false));
                        break;
                    case BYTE:
                        increase_file_counter(1);
                        bytebuffer = fgetc(file);
                        linebuffer[line_char_counter] = bytebuffer;
                        printf("%03o", fgetc(file));
                        break;
                    case WORD:
                        increase_file_counter(2);
                        printf("%06o", word_from_bytes(fgetc(file), fgetc(file)));
                        break;
                    case DWORD:
                        increase_file_counter(4);
                        printf("%012o", dword_from_bytes(fgetc(file), fgetc(file), fgetc(file), fgetc(file)));
                        break;
                    case QWORD:
                        increase_file_counter(8);
                        printf("%024llo", qword_from_bytes(fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file)));
                        break;
                    default:
                        fail("Invalid Grouping for Octal.");
                        break;
                    }
                //-----------------------------
                break;
            case DEC:
                //-----------------------------
                switch (grouping) {
                case NIBBLE:
                    increase_file_counter(1);
                    bytebuffer = fgetc(file);
                    linebuffer[line_char_counter] = bytebuffer;
                    printf("%2hhd %2hhd", get_nibble(bytebuffer, true), get_nibble(bytebuffer, false));
                    break;
                case BYTE:
                    increase_file_counter(1);
                    bytebuffer = fgetc(file);
                    linebuffer[line_char_counter] = bytebuffer;
                    printf("%3hd", bytebuffer);
                    break;
                case WORD:
                    increase_file_counter(2);
                    printf("%5hd", word_from_bytes(fgetc(file), fgetc(file)));
                    break;
                case DWORD:
                    increase_file_counter(4);
                    printf("%10d", dword_from_bytes(fgetc(file), fgetc(file), fgetc(file), fgetc(file)));
                    break;
                case QWORD:
                    increase_file_counter(8);
                    printf("%20lld", qword_from_bytes(fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file)));
                    break;
                default:
                    fail("Invalid Grouping for Decimal.");
                    break;
                }
                //-----------------------------
                break;
            case UDEC:
                //-----------------------------
                switch (grouping) {
                case NIBBLE:
                    increase_file_counter(1);
                    bytebuffer = fgetc(file);
                    linebuffer[line_char_counter] = bytebuffer;
                    printf("%2hhu %2hhu", get_nibble(bytebuffer, true), get_nibble(bytebuffer, false));
                    break;
                case BYTE:
                    increase_file_counter(1);
                    bytebuffer = fgetc(file);
                    linebuffer[line_char_counter] = bytebuffer;
                    printf("%3hu", bytebuffer);
                    break;
                case WORD:
                    increase_file_counter(2);
                    printf("%5hu", word_from_bytes(fgetc(file), fgetc(file)));
                    break;
                case DWORD:
                    increase_file_counter(4);
                    printf("%10u", dword_from_bytes(fgetc(file), fgetc(file), fgetc(file), fgetc(file)));
                    break;
                case QWORD:
                    increase_file_counter(8);
                    printf("%20llu", qword_from_bytes(fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file), fgetc(file)));
                    break;
                default:
                    fail("Invalid Grouping for Decimal.");
                    break;
                }
                //-----------------------------
                break;
            case HEX:
                    increase_file_counter(1);
                    bytebuffer = fgetc(file);
                    linebuffer[line_char_counter] = bytebuffer;
                    if (uppercase) {
                        if (grouping == NIBBLE) {
                            printf("%X %X", get_nibble(bytebuffer, true), get_nibble(bytebuffer, false));
                            break;
                        }
                        printf("%02X", bytebuffer);
                    } else {
                        if (grouping == NIBBLE) {
                            printf("%x %x", get_nibble(bytebuffer, true), get_nibble(bytebuffer, false));
                            break;
                        }
                        printf("%02x", bytebuffer);
                    }
                break;
            case ASCII:
                increase_file_counter(1);
                bytebuffer = fgetc(file);
                linebuffer[line_char_counter] = bytebuffer;
                if (bytebuffer == '\n') bytebuffer = 175;
                if (bytebuffer == '\r') bytebuffer = 217;
                printf("%c", bytebuffer);
                break;
            default:
                fail("Invalid printing format.");
                break;
        }
        //-------------------------------------
        
        if (bytes_amount != 0 && file_counter >= bytes_amount + offset) break;
        
        if (line_char_counter % group_byte_size[grouping] == 0) ecput(GROUP_SEPARATOR_PADDING);
        if (line_char_counter >= line_bytes) {
            line_char_counter = 0;
            block_lines_counter++;
            if (text_column) print_ascii_column(line_bytes);
            puts(" ");
            if(block_lines_counter >= lines_per_block) {
                block_lines_counter = 0;
                ecput("Block\n");
            }
            if (show_byte_offset) print_byte_offset(line_bytes, byte_offset_format);
        }
    }

    // Padding and linebuffer compensation
    const char* byte_output_size[] = {"        ", "  ", " ", "  ", " "};
    while (line_char_counter < line_bytes) {
        if (line_char_counter % group_byte_size[grouping] == 0) ecput(GROUP_SEPARATOR_PADDING);
        ecput(byte_output_size[format]);
        linebuffer[line_char_counter+1] = ' ';
        line_char_counter++;
    }
    // Padding and linebuffer compensation

    if (text_column) print_ascii_column(line_bytes);
    puts("");
    if (show_byte_offset) print_byte_offset(1, byte_offset_format);
    puts("");
#if DYNAMIC_LINE_BUFFER
    free(linebuffer);
#endif
}
