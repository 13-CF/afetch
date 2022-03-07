#define OS_TEXT      "  " // "     OS "
#define KERNEL_TEXT  "  " // " KERNEL "
#define UPTIME_TEXT  "  " // " UPTIME "
#define SHELL_TEXT   "  " // "  SHELL "
#define PACKAGE_TEXT "  " // "   PKGS "
#define COLOR_TEXT   "  "

/* See options in color.h file */
#define TEXT_COLOR     BGREEN
#define VARIABLE_COLOR BMAGENTA

#define PRINT_COLORS    1 /* 0 == false, anything else is true */
#define COLOR_CHARACTER "███"

/* Some examples of things you may want to use for your COLOR_CHARACTER

          ▀ ▁ ▂ ▃ ▄ ▅ ▆ ▇ █ ▉ ▊ ▋ ▌ ▍ ▎ ▏

          █ ▄ ▀ ●
*/

typedef enum distros {
    Arch_Linux          = 254074419,
    Alpine_Linux        = 3363245038,
    Arch_bang_Linux     = 763435659,
    ArcoLinux           = 2287133210,
    Artix_Linux         = 2845327101,
    CelOS               = 217358875,
    Deepin              = 2916796186,
    Debian_GNU_Linux    = 1273810001,
    Arch7               = 215445210,
    elementary_OS       = 4287928349,
    EndeavourOS         = 2528286416,
    Fedora              = 2995030230,
    Gentoo              = 3034530353,
    KDE_neon            = 3370769609,
    Linux_Mint          = 4242320749,
    Manjaro             = 357211085,
    NixOS               = 230560822,
    openSUSE_Leap       = 1786748121,
    openSUSE_Tumbleweed = 330835877,
    Parabola            = 2350242215,
    Pop_OS              = 484288278,
    postmarketOS        = 67040561,
    Slackware           = 2077090562,
    Solus               = 236694267,
    Ubuntu              = 3579113288,
    Void                = 2090838615,
    Zorin_OS            = 4243423673,
} distros;
