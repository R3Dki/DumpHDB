#pragma once
#ifndef ESCAPE_CODES_LIB
#define ESCAPE_CODES_LIB


// Escape Codes Library Compiled Settings
#define ENABLE_VARIADIC_FUNCTIONS false
#define ENABLE_RESTORE_CURSOR_POSITION_DEC false
// Escape Codes Library Compiled Settings


#define ESCAPE_CODES_LIB_VERSION_MAJOR 1
#define ESCAPE_CODES_LIB_VERSION_MINOR 0
#define ESCAPE_CODES_LIB_VERSION_PATCH 1

#include "types.h"
#include <stdio.h>

#if ENABLE_VARIADIC_FUNCTIONS
#include <stdarg.h>
#endif


// Color IDs enum
enum color {
    BLACK = 16,
    DARK_RED = 88,
    RED = 196,
    DARK_BLUE = 17,
    BLUE = 27,
    DARK_GREEN = 22,
    GREEN = 82,
    DARK_AQUA = 23,
    AQUA = 87,
    DARK_YELLOW = 100,
    YELLOW = 226,
    GRAY = 240,
    WHITE = 255,
    DARK_PURPLE = 92,
    PURPLE = 207,
    DARK_ORANGE = 130,
    ORANGE = 208,
    DARK_PINK = 95,
    PINK = 217
};

// Style Modes Enum for Bitwise OR Separated Modes (BOLD | ITALIC)
enum mode {
    BOLD = 0b00000001,
    DIM = 0b00000010,
    ITALIC = 0b00000100,
    UNDERLINE = 0b00001000,
    BLINK = 0b00010000,
    REVERSE = 0b00100000,
    HIDDEN = 0b01000000,
    STRIKETHROUGH = 0b10000000
};

#if ENABLE_VARIADIC_FUNCTIONS
// Style Modes enum for Variadic Modes (2, BOLD_C, ITALIC_C)
enum mode_code {
    BOLD_C = 1,
    DIM_C,
    ITALIC_C,
    UNDERLINE_C,
    BLINK_C,
    REVERSE_C = 7,
    HIDDEN_C,
    STRIKETHROUGH_C
};
#endif

// Prints string to output.
void ecput(const char* s);

// Sets multiple Style Modes at once (separated by bitwise OR | )
void set_modes(u8 modes);

// Resets multiple Style Modes at once (separated by bitwise OR | )
void reset_modes(u8 modes);

#if ENABLE_VARIADIC_FUNCTIONS
// Sets multiple Style Modes at once (Uses variadic arguments, (number_of_args, style_c1, style_c2))
void set_modes_c(u32 modes_count, ...);

// Resets multiple Style Modes at once (Uses variadic arguments, (number_of_args, style_c1, style_c2))
void reset_modes_c(u32 modes_count, ...);
#endif
// Sets a specific Style Mode
void set_mode(u8 mode);

// Resets every Style Mode
void reset();

// Resets a specific Style Mode
void reset_mode(u8 mode);

// Moves cursor to start of window
void move_to_start();

// Moves cursor to x, y position
void move(u16 x, u16 y);

// Moves cursor up a specified amount lines
void move_up(u16 lines);

// Moves cursor down a specified amount lines
void move_down(u16 lines);

// Moves cursor right a specified amount columns
void move_right(u16 columns);

// Moves cursor left a specified amount columns
void move_left(u16 columns);

void move_down_from_line_start(u16 lines);

void move_up_from_line_start(u16 lines);

// Moves cursor to a specified column
void move_to_column(u16 column);

// Moves cursor up one line
void move_up_once();

// Stores current cursor position in decimal
void save_cursor_position_dec();

// Restores the last saved decimal cursor position
// Disabled because of Clang(-Wunknown-escape-sequence)
#if ENABLE_RESTORE_CURSOR_POSITION_DEC
void restore_cursor_position_dec();
#endif

// Stores current cursor position
void save_cursor_position_sco();

// Restores the last saved cursor position
void restore_cursor_position_sco();

// Sets text color to the specified Color ID
// You can use numbers from 0 to 255, search "escape codes color ids" for specific Color IDs
// You can use the color enum which contains color IDs by name
void color(u8 color_id);

// Sets text color to the specified RGB value
void color_rgb(u8 r, u8 g, u8 b);

// Sets background color to the specified Color ID
// You can use numbers from 0 to 255, search "escape codes color ids" for specific Color IDs
// You can use the color enum which contains color IDs by name
void background_color(u8 color_id);

// Sets background color to the specified RGB value
void background_color_rgb(u8 r, u8 g, u8 b);

// Plays Bell Ring(the sound set for alerts in your OS)
void sound();

// Shows cursor
void show_cursor();

// Hides cursor
void hide_cursor();

// Enables Alternative Buffer
void enable_alternative_buffer();

// Disables Alternative Buffer
void disable_alternative_buffer();

// Saves current screen state
void save_screen();

// Restores saved screen state
void restore_screen();

// Erases every character after cursor position
void erase_after_cursor();

// Erases every character before cursor position
void erase_before_cursor();

// Erases every character on screen
void erase_screen();

// Erases saved lines
void erase_saved_lines();

// Erases the next line after cursor
void erase_line_after_cursor();

// Erases the previous line before cursor
void erase_line_before_cursor();

// Erases the line where the cursor is
void erase_line();

// Erases screen and returns to 0, 0 position
void clear_screen();

#endif // ESCAPE CODES LIB