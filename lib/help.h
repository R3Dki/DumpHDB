#define HELP_PAGE_VERSION_MAJOR 1
#define HELP_PAGE_VERSION_MINOR 0
#define HELP_PAGE "Usage: dumphdb [options] filename...\nOptions:\n\
  -v    Displays software and libraries versions.\n\
  -h    Displays the help page.\n\
  -b    Displays file contents in binary.\n\
  -o    Displays file contents in octal.\n\
  -d    Displays file contents in signed decimal.\n\
  -u    Displays file contents in unsigned decimal.\n\
  -x    Displays file contents in lowercase hexadecimal.\n\
  -X    Displays file contents in uppercase hexadecimal.\n\
  -t    Displays file contents in ASCII.\n\
  -g    Sets file contents output bits grouping.\n\
        Available options: \"bit\", \"nibble\", \"byte\", \"word\", \"dword\", \"qword\"\n\
  -l    Sets groups count per line.\n\
  -k    Sets lines per block.\n\
  -p    Displays file contents in ASCII beside the file contents.\n\
  -s    Displays byte offset of current line beside the file contents.\n\
  -a    Displays byte offset in octal format.\n\
  -c    Displays byte offset in decimal format.\n\
  -e    Displays byte offset in hexadecimal format.\n\
  -n    Amount of file contents in bytes to display.\n\
  -r    Reading start offset from specified amount of bytes.\n"
