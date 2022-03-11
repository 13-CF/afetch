#define OS_TEXT      "  " // "     OS "
#define KERNEL_TEXT  "  " // " KERNEL "
#define UPTIME_TEXT  "  " // " UPTIME "
#define SHELL_TEXT   "  " // "  SHELL "
#define PACKAGE_TEXT "  " // "   PKGS "
#define COLOR_TEXT   "  "

/* See options in color.h file */
#define TEXT_COLOR     BGREEN
#define VARIABLE_COLOR BMAGENTA

#define PRINT_COLORS    1 // 0 == false, anything else is true
#define COLOR_CHARACTER "● "

/* Some examples of things you may want to use for your COLOR_CHARACTER

          ▀ ▁ ▂ ▃ ▄ ▅ ▆ ▇ █ ▉ ▊ ▋ ▌ ▍ ▎ ▏

          █ ▄ ▀ ●
*/

/* These lines are automatically set by get_os.sh */
#define DISTRO "Distro"
#define GET_PKG_CNT ""
#define ASCII_ART \
    .row1 = BWHITE "",                \
    .row2 = BGREEN "      ___     ",  \
    .row3 = BGREEN "  ___/   \\___ ", \
    .row4 = BGREEN " /   '---'   \\", \
    .row5 = BGREEN " '--_______--'",  \
    .row6 = BWHITE "      / \\     ", \
    .row7 = BWHITE "     /   \\    ", \
    .row8 = BWHITE "    /     \\   "
