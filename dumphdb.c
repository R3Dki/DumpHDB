#include "lib/parsing.h"
#include "lib/printing.h"

/*
* ARGS LIST (Till now)
* -v   print software version
* -b   binary output
* -o   octal output
* -d   decimal output
* -x   lowercase hexadecimal output
* -X   uppercase hexadecimal output
* -t   ascii text output
* -g   output grouping(can type "bit", byte", "etc" or number(custom))
* -p   prints an ascii version of the file beside the file contents
* -s   show byte offset
* -c   change byte offset to hex
* -r   bytes offset to start reading from
* -n   amount of bytes to print
* -h   print help page
* -k   lines per block
* -l   amount of groups per line
*/
// Printing Library may need to be rewritten.


int main(i32 argc, char* argv[]) {
    u8 format = 0, grouping = 0, offset_format = 0;
    u16 line_groups = 0;
    u32 block_lines_amount = 0;
    u64 byte_amount = 0, byte_start_offset = 0;
    bool text_column = false, byte_offset = false, uppercase = false;
    char *file_path = 0;

    parse_args(argc, argv, &format, &grouping, &byte_start_offset,
        &byte_amount, &line_groups, &block_lines_amount, &text_column,
        &byte_offset, &uppercase, &offset_format, &file_path
    );

    print_file(file_path, byte_start_offset, byte_amount,
        format, grouping,
        line_groups, block_lines_amount,
        byte_offset, offset_format,
        uppercase, text_column
    );

}