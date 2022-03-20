#define OS_TEXT      "os      "
#define KERNEL_TEXT  "kernel  "
#define UPTIME_TEXT  "uptime  "
#define SHELL_TEXT   "shell   "
#define PACKAGE_TEXT "pkgs    "
#define MEMORY_TEXT  "memory  "

/* See options in color.h file */
#define TEXT_COLOR     GREEN
#define VARIABLE_COLOR BMAGENTA

#define PRINT_HOST      1 // 0 == false, anything else is true
#define PRINT_OS        1 
#define PRINT_KERNEL    1 
#define PRINT_UPTIME    1 
#define PRINT_PKGS      1 
#define PRINT_SHELL     0
#define PRINT_MEMORY    1 
#define PRINT_COLORS    1
#define COLOR_CHARACTER "███"

/* Some examples of things you may want to use for your COLOR_CHARACTER

          ▀ ▁ ▂ ▃ ▄ ▅ ▆ ▇ █ ▉ ▊ ▋ ▌ ▍ ▎ ▏

          █ ▄ ▀ ●
*/

/* These lines are automatically set by get_os.sh */
#define DISTRO      "Distro"
#define GET_PKG_CNT ""
#define ASCII_ART \
    .row1 = BGREEN "      ___       ",  \
    .row2 = BGREEN "  ___/   \\___   ", \
    .row3 = BGREEN " /   '---'   \\  ", \
    .row4 = BGREEN " '--_______--'  ",  \
    .row5 = BWHITE "      / \\       ", \
    .row6 = BWHITE "     /   \\      ", \
    .row7 = BWHITE "    /     \\     ", \
    .row8 = BWHITE "                 "
