#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include "color.h"
#include "config.h"

typedef struct dist {
    char *col1, *col2, *col3, *col4, *col5, *col6, *col7, *col8;
    char *get_pkg_count;
} dist;

unsigned int hash(char *str)
{
    unsigned int hash = 5381;
    int          c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

char *pipe_read(const char *exec)
{
    FILE *pipe = popen(exec, "r");
    if (pipe == NULL)
        return NULL;
    char     *return_val   = malloc(256);
    const int scanf_return = fscanf(pipe, "%[^\n]256s", return_val);
    pclose(pipe);
    if (scanf_return == EOF) {
        fprintf(stderr, "ERROR: scanf failed!\n");
        exit(EXIT_FAILURE);
    }
    return return_val;
}

void uptime(long *uptime_h, long *uptime_m)
{
    struct timespec time;
#if defined(CLOCK_BOOTTIME)
#define CLOCK CLOCK_BOOTTIME
#elif defined(CLOCK_UPTIME)
#define CLOCK CLOCK_UPTIME
#elif defined(__APPLE__)
#define CLOCK CLOCK_MONOTONIC
#endif

#ifdef CLOCK
    clock_gettime(CLOCK, &time);
    *uptime_h = time.tv_sec / 3600;
    *uptime_m = (time.tv_sec / 60) - (time.tv_sec / 3600 * 60);
#endif
}

char *shell()
{
    char *shell = getenv("SHELL");
    char *slash = strrchr(shell, '/');
    if (slash) {
        shell = slash + 1;
    }
    return shell;
}

void os(struct utsname *sys_info, struct dist *inf, char *os_name)
{
    if (strncmp(sys_info->sysname, "Linux", 5) == 0) {
        char  os_contents[512];
        FILE *fp = fopen("/etc/os-release", "rt");
        if (!fp) {
            strncpy(os_name, "Linux", 6);
            inf->col1 = BWHITE "";
            inf->col2 = GRAY "      ___   ";
            inf->col3 = GRAY "     (" BWHITE ".." GRAY " \\  ";
            inf->col4 = GRAY "     (" YELLOW "<>" GRAY " |  ";
            inf->col5 = GRAY "    /" WHITE "/  \\" GRAY " \\ ";
            inf->col6 = GRAY "   ( " WHITE "|  | " GRAY "/|";
            inf->col7 = YELLOW "  _" GRAY "/\\ " WHITE "__)" GRAY "/" YELLOW
                               "_" GRAY ")";
            inf->col8 = YELLOW "  \\/" GRAY "-____" YELLOW "\\/ ";
            return;
        }
        fread(os_contents, 1, 512, fp);
        fclose(fp);
        char *name = strstr(os_contents, "NAME=");
        name += 5;
        if (*name == '"') {
            name++;
        }
        int i;
        for (i = 0; name[i] != '"' && name[i] != '\n'; i++) {
            os_name[i] = name[i];
        }
        os_name[i] = '\0';

        switch (hash(os_name)) {
#include "distros.h"
        }

    } else if (strncmp(sys_info->sysname, "Darwin", 6) == 0) {
        inf->col1         = "" BYELLOW;
        inf->col2         = BGREEN "          .:'   " BYELLOW;
        inf->col3         = BGREEN "      __ :'__   " BYELLOW;
        inf->col4         = BYELLOW "   .'`__`-'__``." BYELLOW;
        inf->col5         = BRED "  :__________.-'" BYELLOW;
        inf->col6         = BRED "  :_________:   " BYELLOW;
        inf->col7         = BMAGENTA "   :_________`-;" BYELLOW;
        inf->col8         = BBLUE "    `.__.-.__.' " BYELLOW;
        char *product_ver = pipe_read("sw_vers -productVersion");
        if ((strncmp(sys_info->machine, "iPhone", 6) == 0) ||
            (strncmp(sys_info->machine, "iPad", 4) == 0) ||
            (strncmp(sys_info->machine, "iPod", 4) == 0)) {
            inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";

            char ios_ver[1024];
            strcpy(ios_ver, "iOS ");

            strcat(ios_ver, product_ver);
            strncpy(os_name, ios_ver, 1024);
        } else {
            inf->get_pkg_count =
                "ls /usr/local/Cellar/* | grep ':' | wc -l | xargs";

            char mac_ver[64];
            strcpy(mac_ver, "macOS ");

            strcat(mac_ver, product_ver);
            strncpy(os_name, mac_ver, 64);
        }
        free(product_ver);
    } else if (strncmp(sys_info->sysname, "FreeBSD", 7) == 0) {
        inf->col1          = BRED "";
        inf->col2          = BRED " /\\,-'''''-,/\\";
        inf->col3          = BRED " \\_)       (_/";
        inf->col4          = BRED " |           |";
        inf->col5          = BRED " |           |";
        inf->col6          = BRED "  ;         ; ";
        inf->col7          = BRED "   '-_____-'  ";
        inf->col8          = BRED "              ";
        inf->get_pkg_count = "pkg info | wc -l | tr -d ' '";
        os_name            = sys_info->sysname;
    } else if (strncmp(sys_info->sysname, "OpenBSD", 7) == 0) {
        inf->col1          = BYELLOW "";
        inf->col2          = BYELLOW "      _____    ";
        inf->col3          = BYELLOW "    \\-     -/  ";
        inf->col4          = BYELLOW " \\_/         \\ ";
        inf->col5          = BYELLOW " |        " BWHITE "O O" BYELLOW " |";
        inf->col6          = BYELLOW " |_  <   )  3 )";
        inf->col7          = BYELLOW " / \\         / ";
        inf->col8          = BYELLOW "    /-_____-\\  ";
        inf->get_pkg_count = "/bin/ls -1 /var/db/pkg/ | wc -l | tr -d ' '";
        os_name            = sys_info->sysname;
    } else if (strncmp(sys_info->sysname, "NetBSD", 6) == 0) {
    }
}

void colour_draw()
{
    if (!PRINT_COLORS)
        return;

    printf("%s%s", VARIABLE_COLOR, COLOR_TEXT);
    for (int i = 31; i < 37; i++) {
        printf("\033[0;%dm%s", i, COLOR_CHARACTER);
    } // print regular term colours
}

int main()
{
    struct dist info = {
        .col1          = BWHITE "",
        .col2          = BGREEN "      ___     ",
        .col3          = BGREEN "  ___/   \\___ ",
        .col4          = BGREEN " /   '---'   \\",
        .col5          = BGREEN " '--_______--'",
        .col6          = BWHITE "      / \\     ",
        .col7          = BWHITE "     /   \\    ",
        .col8          = BWHITE "    /     \\   ",
        .get_pkg_count = "echo unsupported",
    };
    struct utsname sys_info;
    uname(&sys_info);
    char hostname[HOST_NAME_MAX + 1], osname[512];
    long uptime_h, uptime_m;

    gethostname(hostname, HOST_NAME_MAX + 1);
    os(&sys_info, &info, osname);
    uptime(&uptime_h, &uptime_m);

    printf("%s", info.col1);
    printf("%s   " BYELLOW "%s" BRED "@" BBLUE "%s\n", info.col2, getlogin(),
           hostname); // user@host
    printf("%s   %s%s%s%s\n", info.col3, VARIABLE_COLOR, OS_TEXT, TEXT_COLOR,
           osname); // osname
    printf("%s   %s%s%s%s\n", info.col4, VARIABLE_COLOR, KERNEL_TEXT,
           TEXT_COLOR,
           sys_info.release); // kernel version
    printf("%s   %s%s%s%ldh %ldm\n", info.col5, VARIABLE_COLOR, UPTIME_TEXT,
           TEXT_COLOR, uptime_h, uptime_m); // uptime
    printf("%s   %s%s%s%s\n", info.col6, VARIABLE_COLOR, SHELL_TEXT, TEXT_COLOR,
           shell()); // shell
    printf("%s   %s%s%s%s\n", info.col7, VARIABLE_COLOR, PACKAGE_TEXT,
           TEXT_COLOR,
           pipe_read(info.get_pkg_count)); // package count
    printf("%s   ", info.col8);

    colour_draw();
    printf("%s\n\n", RESET);

    return 0;
}
