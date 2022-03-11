#define OS_TEXT      "  " // "     OS "
#define KERNEL_TEXT  "  " // " KERNEL "
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
#define DISTRO "Android 11"
#define GET_PKG_CNT "pacman -Qq | wc -l"
#define ASCII_ART \
    .row1 = BCYAN "",                  \
    .row2 = BCYAN "       /\\      ",  \
    .row3 = BCYAN "      /  \\     ",  \
    .row4 = BCYAN "     /\\   \\    ", \
    .row5 = BBLUE "    /      \\   ",  \
    .row6 = BBLUE "   /   ,,   \\  ",  \
    .row7 = BBLUE "  /   |  |  -\\ ",  \
    .row8 = BBLUE " /_-''    ''-_\\"
