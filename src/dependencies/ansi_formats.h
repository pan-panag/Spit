#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

/*
 * ANSI Colors and Styles Header
 * This header file provides ANSI escape codes for colors, background colors,
 * and text styles (bold, underline, etc.) for use in C programs.
 */

// Reset
#define RESET               "\x1b[0m"       // Reset all attributes
#define COLOR_RESET         RESET           // Alias for reset

// Regular text colors
#define BLACK               "\x1b[30m"
#define RED                 "\x1b[31m"
#define GREEN               "\x1b[32m"
#define YELLOW              "\x1b[33m"
#define BLUE                "\x1b[34m"
#define MAGENTA             "\x1b[35m"
#define CYAN                "\x1b[36m"
#define WHITE               "\x1b[37m"

// Bold text colors
#define BOLD_BLACK          "\x1b[1;30m"
#define BOLD_RED            "\x1b[1;31m"
#define BOLD_GREEN          "\x1b[1;32m"
#define BOLD_YELLOW         "\x1b[1;33m"
#define BOLD_BLUE           "\x1b[1;34m"
#define BOLD_MAGENTA        "\x1b[1;35m"
#define BOLD_CYAN           "\x1b[1;36m"
#define BOLD_WHITE          "\x1b[1;37m"

// Underline text colors
#define UNDERLINE_BLACK     "\x1b[4;30m"
#define UNDERLINE_RED       "\x1b[4;31m"
#define UNDERLINE_GREEN     "\x1b[4;32m"
#define UNDERLINE_YELLOW    "\x1b[4;33m"
#define UNDERLINE_BLUE      "\x1b[4;34m"
#define UNDERLINE_MAGENTA   "\x1b[4;35m"
#define UNDERLINE_CYAN      "\x1b[4;36m"
#define UNDERLINE_WHITE     "\x1b[4;37m"

// High-intensity text colors
#define BRIGHT_BLACK        "\x1b[90m"
#define BRIGHT_RED          "\x1b[91m"
#define BRIGHT_GREEN        "\x1b[92m"
#define BRIGHT_YELLOW       "\x1b[93m"
#define BRIGHT_BLUE         "\x1b[94m"
#define BRIGHT_MAGENTA      "\x1b[95m"
#define BRIGHT_CYAN         "\x1b[96m"
#define BRIGHT_WHITE        "\x1b[97m"

// Bold high-intensity text colors
#define BOLD_BRIGHT_BLACK   "\x1b[1;90m"
#define BOLD_BRIGHT_RED     "\x1b[1;91m"
#define BOLD_BRIGHT_GREEN   "\x1b[1;92m"
#define BOLD_BRIGHT_YELLOW  "\x1b[1;93m"
#define BOLD_BRIGHT_BLUE    "\x1b[1;94m"
#define BOLD_BRIGHT_MAGENTA "\x1b[1;95m"
#define BOLD_BRIGHT_CYAN    "\x1b[1;96m"
#define BOLD_BRIGHT_WHITE   "\x1b[1;97m"

// Background colors
#define BG_BLACK            "\x1b[40m"
#define BG_RED              "\x1b[41m"
#define BG_GREEN            "\x1b[42m"
#define BG_YELLOW           "\x1b[43m"
#define BG_BLUE             "\x1b[44m"
#define BG_MAGENTA          "\x1b[45m"
#define BG_CYAN             "\x1b[46m"
#define BG_WHITE            "\x1b[47m"

// High-intensity background colors
#define BG_BRIGHT_BLACK     "\x1b[0;100m"
#define BG_BRIGHT_RED       "\x1b[0;101m"
#define BG_BRIGHT_GREEN     "\x1b[0;102m"
#define BG_BRIGHT_YELLOW    "\x1b[0;103m"
#define BG_BRIGHT_BLUE      "\x1b[0;104m"
#define BG_BRIGHT_MAGENTA   "\x1b[0;105m"
#define BG_BRIGHT_CYAN      "\x1b[0;106m"
#define BG_BRIGHT_WHITE     "\x1b[0;107m"

// Text styles
#define BOLD                "\x1b[1m"
#define DIM                 "\x1b[2m"
#define ITALIC              "\x1b[3m"
#define UNDERLINE           "\x1b[4m"
#define BLINK               "\x1b[5m"
#define REVERSE             "\x1b[7m"
#define HIDDEN              "\x1b[8m"
#define STRIKETHROUGH       "\x1b[9m"

// Convenience combinations
#define BOLD_RED_TEXT       BOLD RED
#define BOLD_GREEN_TEXT     BOLD GREEN
#define BOLD_YELLOW_TEXT    BOLD YELLOW
#define BOLD_BLUE_TEXT      BOLD BLUE
#define BOLD_MAGENTA_TEXT   BOLD MAGENTA
#define BOLD_CYAN_TEXT      BOLD CYAN
#define BOLD_WHITE_TEXT     BOLD WHITE

#endif // ANSI_COLORS_H
