#include "escape_codes.h"
#include "types.h"

const u8 compare_bits[] = { 1, 2, 4, 8, 16, 32, 64, 128 },
mode_short[] = { 1, 2, 3, 4, 5,  7,  8,  9 };

void ecput(const char* s) {
    while (*s) putchar(*s++);
}

void set_modes(u8 modes) {
    char delimiter = ';';
    u8 modes_count = 0, j = 0;
    ecput("\x1B[");
    for (u8 i = 8; i > 0; i--) { if (modes & compare_bits[i]) { modes_count++; } }
    for (u8 i = 8; i > 0; i--) {
        if (modes & compare_bits[i]) {
            j++;
            if (j == modes_count) { delimiter = 'm'; }
            printf("%d%c", mode_short[i], delimiter);
        }
    }
}

void reset_modes(u8 modes) {
    char delimiter = ';';
    u8 modes_count = 0, j = 0;
    ecput("\x1B[");
    for (u8 i = 8; i > 0; i--) { if (modes & compare_bits[i]) { modes_count++; } }
    for (u8 i = 8; i > 0; i--) {
        if (modes & compare_bits[i]) {
            j++;
            if (j == modes_count) { delimiter = 'm'; }
            printf("%d%c", mode_short[i] + 20, delimiter);
        }
    }
}

// Variadic Modes
#if ENABLE_VARIADIC_FUNCTIONS
void set_modes_c(u32 modes_count, ...) {
    va_list argptr;
    char delimiter = ';';
    va_start(argptr, modes_count);
    ecput("\x1B[");
    for (u8 i = 0; i < modes_count; i++) {
        if (i == modes_count - 1) { delimiter = 'm'; }
        printf("%d%c", va_arg(argptr, u32), delimiter);
    }
    va_end(argptr);
}

void reset_modes_c(u32 modes_count, ...) {
    va_list argptr;
    char delimiter = ';';
    va_start(argptr, modes_count);
    ecput("\x1B[");
    for (u8 i = 0; i < modes_count; i++) {
        if (i == modes_count - 1) { delimiter = 'm'; }
        printf("%d%c", 20 + va_arg(argptr, u32), delimiter);
    }
    va_end(argptr);
}
#endif
// Variadic Modes

void set_mode(u8 mode) {
    printf("\x1B[%dm", mode);
}

void reset() {
    ecput("\x1B[0m");
}

void reset_mode(u8 mode) {
    printf("\x1B[%dm", mode + 20);
}

void move_to_start() {
    ecput("\x1B[H");
}

void move(u16 x, u16 y) {
    printf("\x1B[%d;%dH", y, x);
}

void move_up(u16 lines) {
    printf("\x1B[%dA", lines);
}

void move_down(u16 lines) {
    printf("\x1B[%dB", lines);
}

void move_right(u16 columns) {
    printf("\x1B[%dC", columns);
}

void move_left(u16 columns) {
    printf("\x1B[%dD", columns);
}

void move_down_from_line_start(u16 lines) {
    printf("\x1B[%dE", lines);
}

void move_up_from_line_start(u16 lines) {
    printf("\x1B[%dF", lines);
}

void move_to_column(u16 column) {
    printf("\x1B[%dG", column);
}

void move_up_once() {
    ecput("\x1BM");
}

/*
void save_cursor_position_dec() {
    printf("\x1B%c", '7');
}

void restore_cursor_position_dec() {
    printf("\x1B%c", '8');
}
*/

void save_cursor_position_dec() {
    ecput("\x1B\7");
}

// Disabled because of Clang(-Wunknown-escape-sequence)
#if ENABLE_RESTORE_CURSOR_POSITION_DEC
void restore_cursor_position_dec() {
    ecput("\x1B\8");
}
#endif

void save_cursor_position_sco() {
    ecput("\x1B[s");
}

void restore_cursor_position_sco() {
    ecput("\x1B[u");
}

void color(u8 color_id) {
    printf("\x1B[38;5;%dm", color_id);
}

void color_rgb(u8 r, u8 g, u8 b) {
    printf("\x1B[38;2;%d;%d;%dm", r, g, b);
}

void background_color(u8 color_id) {
    printf("\x1B[48;5;%dm", color_id);
}

void background_color_rgb(u8 r, u8 g, u8 b) {
    printf("\x1B[48;2;%d;%d;%dm", r, g, b);
}

void sound() {
    ecput("\a");
}

void show_cursor() {
    ecput("\x1B[?25h");
}

void hide_cursor() {
    ecput("\x1B[?25l");
}

void enable_alternative_buffer() {
    ecput("\x1B[?1049h");
}

void disable_alternative_buffer() {
    ecput("\x1B[?1049l");
}

void save_screen() {
    ecput("\x1B[?47h");
}

void restore_screen() {
    ecput("\x1B[?47l");
}

void erase_after_cursor() {
    ecput("\x1B[0J");
}

void erase_before_cursor() {
    ecput("\x1B[1J");
}

void erase_screen() {
    ecput("\x1B[2J");
}

void erase_saved_lines() {
    ecput("\x1B[3J");
}

void erase_line_after_cursor() {
    ecput("\x1B[0K");
}

void erase_line_before_cursor() {
    ecput("\x1B[1K");
}

void erase_line() {
    ecput("\x1B[2K");
}

void clear_screen() {
    reset();
    erase_screen();
    move_to_start();
}