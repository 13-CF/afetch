#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include "colour.h"
#include "config.h"

struct dist {
    char *col1, *col2, *col3, *col4, *col5, *col6, *col7, *col8;
    char *getPkgCount;
};
struct dist info = {
    // .col1        = BWHITE "      ___   \n",
    // .col2        = BWHITE "  ___/   \\___ ",
    // .col3        = BWHITE " /   '---'   \\",
    // .col4        = BWHITE " '--_______--'",
    // .col5        = BWHITE "      / \\     ",
    // .col6        = BWHITE "     /   \\    ",
    // .col7        = BWHITE "    /     \\   ",
    // .col8        = BWHITE "              ",

    .col1 = BWHITE "",
    .col2 = GRAY "      ___    ",
    .col3 = GRAY "     (" BWHITE ".." GRAY " \\   ",
    .col4 = GRAY "     (" YELLOW "<>" GRAY " |   ",
    .col5 = GRAY "    /" WHITE "/  \\" GRAY " \\  ",
    .col6 = GRAY "   ( " WHITE "|  | " GRAY "/| ",
    .col7 = YELLOW "  _" GRAY "/\\ " WHITE "__)" GRAY "/" YELLOW "_" GRAY ") ",
    .col8 = YELLOW "  \\/" GRAY "-____" YELLOW "\\/  ",
    .getPkgCount = "echo unsupported",
};

char *username, hostname[HOST_NAME_MAX + 1], *osname, *shellname, *pkgCount;
char *krnlver;
long  uptimeH, uptimeM;

char *pipeRead(const char *exec)
{
    FILE *pipe = popen(exec, "r");
    if (pipe == NULL)
        return NULL;
    char     *returnVal    = malloc(256);
    const int scanf_return = fscanf(pipe, "%[^\n]256s", returnVal);
    pclose(pipe);
    if (scanf_return == EOF) {
        fprintf(stderr, "ERROR: scanf failed!\n");
        exit(EXIT_FAILURE);
    }
    return returnVal;
}

void *kernel()
{
    static struct utsname kernelData;
    uname(&kernelData);
    krnlver = kernelData.release;
    return NULL;
}

void *uptime()
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
    uptimeH = time.tv_sec / 3600;
    uptimeM = (time.tv_sec / 60) - (time.tv_sec / 3600 * 60);
#endif
    return NULL;
}

void *user()
{
    username = getenv("USER");

    return NULL;
}

void *host()
{
    gethostname(hostname, HOST_NAME_MAX + 1);

    return NULL;
}

void *shell()
{
    char *shell = getenv("SHELL");
    char *slash = strrchr(shell, '/');
    if (slash) {
        shell = slash + 1;
    }
    shellname = shell;
    return NULL;
}

void *os()
{
    static struct utsname sysInfo;
    uname(&sysInfo);
    /* start */
    /* This whole section could probably be rewritten - it seems
       like a bit of a mess right now */
    if (strncmp(sysInfo.sysname, "Linux", 5) == 0) {
        char *osContents  = malloc(512);
        char *newContents = malloc(512);
        int   line        = 0;
        FILE *f           = fopen("/etc/os-release", "rt");
        if (f == NULL || osContents == NULL)
            return "Linux";
        /* look through each line of /etc/os-release until we're on the
         * NAME= line */
        while (fgets(osContents, 512, f)) {
            snprintf(newContents, 512, "%.*s", 511, osContents + 4);
            if (strncmp(newContents, "=", 1) == 0)
                break;
            line++;
        }
        fclose(f);
        free(osContents);
        if (strncmp(newContents, "=", 1) == 0) {
            int len = strlen(newContents);
            for (int i = 0; i < len; i++) {
                if (newContents[i] == '\"' || newContents[i] == '=') {
                    for (int ii = 0; ii < len; ii++)
                        newContents[ii] = newContents[ii + 1];
                    newContents[strlen(newContents) - 1] = '\0';
                }
            }
        }
        if (osname == NULL)
            osname = malloc(512);
        strcpy(osname, newContents);
        free(newContents);
        /* end */
        if (strncmp(osname, "Alpine Linux", 12) == 0) {
            info.col1        = BBLUE "\n";
            info.col2        = BBLUE "     /\\ /\\    ";
            info.col3        = BBLUE "    /  \\  \\   ";
            info.col4        = BBLUE "   /    \\  \\  ";
            info.col5        = BBLUE "  /      \\  \\ ";
            info.col6        = BBLUE " /        \\  \\";
            info.col7        = BBLUE "           \\  ";
            info.col8        = BBLUE "";
            info.getPkgCount = "grep 'P:' /lib/apk/db/installed | wc -l";
        } else if (strncmp(osname, "Arch Linux", 10) == 0) {
            // info.col1        = BCYAN "";
            // info.col2        = BCYAN "       /\\      ";
            // info.col3        = BCYAN "      /  \\     ";
            // info.col4        = BCYAN "     /\\   \\    ";
            // info.col5        = BBLUE "    /      \\   ";
            // info.col6        = BBLUE "   /   ,,   \\  ";
            // info.col7        = BBLUE "  /   |  |  -\\ ";
            // info.col8        = BBLUE " /_-''    ''-_\\";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "Arch bang Linux", 15) == 0) {
            info.col1        = BCYAN "           ____\n";
            info.col2        = BCYAN "       /\\ /   /";
            info.col3        = BCYAN "      /  /   / ";
            info.col4        = BCYAN "     /   / /   ";
            info.col5        = BCYAN "    /   /_/\\   ";
            info.col6        = BCYAN "   /   __   \\  ";
            info.col7        = BCYAN "  /   /_/\\   \\ ";
            info.col8        = BCYAN " /_-''    ''-_\\";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "ArcoLinux", 9) == 0) {
            info.col1        = BBLUE "";
            info.col2        = BBLUE "       /\\      ";
            info.col3        = BBLUE "      /  \\     ";
            info.col4        = BBLUE "     / /\\ \\    ";
            info.col5        = BBLUE "    / /  \\ \\   ";
            info.col6        = BBLUE "   / /    \\ \\  ";
            info.col7        = BBLUE "  / / _____\\ \\ ";
            info.col8        = BBLUE " /_/  `----.\\_\\";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "Artix Linux", 11) == 0) {
            info.col1        = BCYAN "";
            info.col2        = BCYAN "       /\\      ";
            info.col3        = BCYAN "      /  \\     ";
            info.col4        = BCYAN "     /`'.,\\    ";
            info.col5        = BCYAN "    /     ',   ";
            info.col6        = BCYAN "   /      ,`\\  ";
            info.col7        = BCYAN "  /   ,.'`.  \\ ";
            info.col8        = BCYAN " /.,'`     `'.\\";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "CelOS", 5) == 0) {
            info.col1 = BMAGENTA "\n";
            info.col2 = BMAGENTA "     ______     ";
            info.col3 = BMAGENTA "   _-" BWHITE " _____" BMAGENTA "\\" BWHITE
                                 "__  " BMAGENTA;
            info.col4 = BMAGENTA "  -         -   ";
            info.col5 =
                BWHITE "__" BMAGENTA "|" BWHITE "_____" BMAGENTA "     |  ";
            info.col6 = BMAGENTA "  |          |  ";
            info.col7 = BMAGENTA "  -_" BWHITE "  ______" BMAGENTA "/" BWHITE
                                 "_  " BMAGENTA;
            info.col8 = BMAGENTA "    -______/    ";
            // have to add support for flatpak too
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
            /* TO DO: CREATE DEEPIN LOGO */
        } else if (strncmp(osname, "Deepin", 6) == 0) {
            info.col1        = BRED "\n";
            info.col2        = BRED "";
            info.col3        = BRED "";
            info.col4        = BRED "";
            info.col5        = BRED "";
            info.col6        = BRED "";
            info.col7        = BRED "";
            info.col8        = BRED "";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osname, "Debian GNU/Linux", 16) == 0) {
            info.col1        = BRED "   _____\n";
            info.col2        = BRED "  /  __ \\ ";
            info.col3        = BRED " |  /    |";
            info.col4        = BRED " |  \\___- ";
            info.col5        = BRED " -_       ";
            info.col6        = BRED "   --_    ";
            info.col7        = BRED "          ";
            info.col8        = BRED "";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osname, "Arch7", 10) == 0) {
            info.col1        = BCYAN "";
            info.col2        = BCYAN "  _______      ";
            info.col3        = BCYAN " |____   \\     ";
            info.col4        = BCYAN "     / /\\ \\    ";
            info.col5        = BCYAN "    / /__\\ \\   ";
            info.col6        = BCYAN "   / /____\\ \\  ";
            info.col7        = BCYAN "  /_/      \\_\\ ";
            info.col8        = BCYAN "";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "elementary OS", 12) == 0) {
            info.col1        = BCYAN "";
            info.col2        = BCYAN "   _______  ";
            info.col3        = BCYAN "  / ____  \\ ";
            info.col4        = BCYAN " /  |  /  /\\";
            info.col5        = BCYAN " |__\\ /  / |";
            info.col6        = BCYAN " \\   /__/  /";
            info.col7        = BCYAN "  \\_______/ ";
            info.col8        = BCYAN "";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osname, "EndeavourOS", 11) == 0) {
            info.col1        = BCYAN "";
            info.col2        = BRED "      /" BBLUE "\\     " BCYAN;
            info.col3        = BRED "    /" BBLUE "/  \\" BCYAN "\\   " BCYAN;
            info.col4        = BRED "   /" BBLUE "/    \\ " BCYAN "\\ " BCYAN;
            info.col5        = BRED " / " BBLUE "/     _) " BCYAN ")" BCYAN;
            info.col6        = BRED "/_" BBLUE "/___-- " BCYAN "__- " BCYAN;
            info.col7        = BCYAN " /____--     " BCYAN;
            info.col8        = BCYAN "";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "Fedora", 6) == 0) {
            info.col1        = BWHITE "      _____\n" BBLUE;
            info.col2        = BWHITE "     /   __)" BBLUE "\\ ";
            info.col3        = BWHITE "     |  /  " BBLUE "\\ \\";
            info.col4        = BWHITE "  ___|  |" BBLUE "__/ /";
            info.col5        = BBLUE " / " BWHITE "(_    _)" BBLUE "_/ ";
            info.col6        = BBLUE "/ /  " BWHITE "|  |     " BBLUE;
            info.col7        = BBLUE "\\ \\" BWHITE "__/  |     " BBLUE;
            info.col8        = BBLUE " \\" BWHITE "(_____/" BBLUE;
            info.getPkgCount = "[[ $(which sqlite3 2>/dev/null) && $? -ne "
                               "1 ]] && (sqlite3 "
                               "/var/lib/rpm/rpmdb.sqlite \"select * from "
                               "Name\"|wc -l) || rpm -qa | wc -l";
        } else if (strncmp(osname, "Gentoo", 6) == 0) {
            info.col1        = BMAGENTA "   _-----_ \n";
            info.col2        = BMAGENTA "  (       \\  ";
            info.col3        = BMAGENTA "  \\    0   \\ ";
            info.col4        = BMAGENTA "   \\        )";
            info.col5        = BMAGENTA "   /      _/ ";
            info.col6        = BMAGENTA "  (     _-   ";
            info.col7        = BMAGENTA "  \\____-     ";
            info.col8        = BWHITE "\n";
            info.getPkgCount = "qlist -IRv | wc -l";
        } else if (strncmp(osname, "KDE neon", 8) == 0) {
            info.col1        = BGREEN "";
            info.col2        = BGREEN "            ";
            info.col3        = BGREEN "     --- _  ";
            info.col4        = BGREEN "  /  ---  \\ ";
            info.col5        = BGREEN " |  |   |  |";
            info.col6        = BGREEN "  \\  --- _/ ";
            info.col7        = BGREEN "     ---    ";
            info.col8        = BGREEN "";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osname, "Linux Mint", 10) == 0) {
            info.col1        = BGREEN "   _____________   \n";
            info.col2        = BGREEN "  |_            \\  ";
            info.col3        = BGREEN "   |  | _____  |   ";
            info.col4        = BGREEN "   |  | | | |  |   ";
            info.col5        = BGREEN "   |  | | | |  |   ";
            info.col6        = BGREEN "   |  \\_____/  |   ";
            info.col7        = BGREEN "   \\___________/   ";
            info.col8        = BGREEN "";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osname, "Manjaro", 7) == 0) {
            info.col1        = BGREEN "  ________  __ \n";
            info.col2        = BGREEN " |       | |  |";
            info.col3        = BGREEN " |   ____| |  |";
            info.col4        = BGREEN " |  |  __  |  |";
            info.col5        = BGREEN " |  | |  | |  |";
            info.col6        = BGREEN " |  | |  | |  |";
            info.col7        = BGREEN " |  | |  | |  |";
            info.col8        = BGREEN " |__| |__| |__|";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "NixOS", 5) == 0) {
            info.col1        = BMAGENTA "             \n";
            info.col2        = BMAGENTA "   \\\\  \\\\ //     ";
            info.col3        = BMAGENTA "  ==\\\\__\\\\/ //   ";
            info.col4        = BMAGENTA "    //   \\\\//    ";
            info.col5        = BMAGENTA " ==//     //==   ";
            info.col6        = BMAGENTA "  //\\\\___//      ";
            info.col7        = BMAGENTA " // /\\\\  \\\\==    ";
            info.col8        = BMAGENTA "   // \\\\  \\\\     ";
            info.getPkgCount = "nix-store -q --requisites "
                               "/run/current-system/sw | wc -l";
        } else if (strncmp(osname, "openSUSE Leap", 10) == 0 ||
                   strncmp(osname, "openSUSE Tumbleweed", 19) == 0) {
            info.col1        = BGREEN "   _______\n";
            info.col2        = BGREEN " __|   __ \\ ";
            info.col3        = BGREEN "      / .\\ \\";
            info.col4        = BGREEN "      \\__/ |";
            info.col5        = BGREEN "    _______|";
            info.col6        = BGREEN "    \\_______";
            info.col7        = BGREEN " __________/";
            info.col8        = BGREEN "";
            info.getPkgCount = "rpm -qa | wc -l";
        } else if (strncmp(osname, "Parabola", 8) == 0) {
            info.col1        = BMAGENTA "";
            info.col2        = BMAGENTA "   __ __ __  _  ";
            info.col3        = BMAGENTA " .`_//_//_/ / `.";
            info.col4        = BMAGENTA "           /  .`";
            info.col5        = BMAGENTA "          / .`  ";
            info.col6        = BMAGENTA "         /.`    ";
            info.col7        = BMAGENTA "        /`      ";
            info.col8        = BMAGENTA "";
            info.getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osname, "Pop!_OS", 7) == 0) {
            info.col1        = BCYAN " ______\n";
            info.col2        = BCYAN " \\   _ \\        __";
            info.col3        = BCYAN "  \\ \\ \\ \\      / /";
            info.col4        = BCYAN "   \\ \\_\\ \\    / / ";
            info.col5        = BCYAN "    \\  ___\\  /_/  ";
            info.col6        = BCYAN "     \\ \\    _     ";
            info.col7        = BCYAN "    __\\_\\__(_)_   ";
            info.col8        = BCYAN "   (___________)";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osname, "postmarketOS", 13) == 0) {
            info.col1        = BGREEN "        /\\       \n";
            info.col2        = BGREEN "       /  \\      ";
            info.col3        = BGREEN "      /    \\     ";
            info.col4        = BGREEN "     /\\__   \\    ";
            info.col5        = BGREEN "    /   /\\  _\\   ";
            info.col6        = BGREEN "   /   ___\\/  \\  ";
            info.col7        = BGREEN "  /    \\       \\ ";
            info.col8        = BGREEN " /_____/________\\";
            info.getPkgCount = "grep 'P:' /lib/apk/db/installed | wc -l";
        } else if (strncmp(osname, "Slackware", 10) == 0) {
            info.col1        = BBLUE "    ________\n";
            info.col2        = BBLUE "   /  ______| ";
            info.col3        = BBLUE "   | |______  ";
            info.col4        = BBLUE "   \\______  \\ ";
            info.col5        = BBLUE "    ______| | ";
            info.col6        = BBLUE " | |________/ ";
            info.col7        = BBLUE " |____________";
            info.col8        = BBLUE "";
            info.getPkgCount = "ls /var/log/packages | wc -l";
        } else if (strncmp(osname, "Solus", 5) == 0) {
            info.col1        = BMAGENTA "     __________\n";
            info.col2        = BMAGENTA "    /          \\   ";
            info.col3        = BMAGENTA "   /   /\\ \\     \\  ";
            info.col4        = BMAGENTA "  /   /  \\ \\     \\ ";
            info.col5        = BMAGENTA " |   /    \\ \\     |";
            info.col6        = BMAGENTA "  \\--------------/ ";
            info.col7        = BMAGENTA "   \\------------/  ";
            info.col8        = BMAGENTA "    \\----------/";
            info.getPkgCount = "ls /var/lib/eopkg/package/ | wc -l";
        } else if (strncmp(osname, "Ubuntu", 6) == 0) {
            info.col1        = BRED "";
            info.col2        = BRED "          _  ";
            info.col3        = BRED "      ---(_) ";
            info.col4        = BRED "  _/  ---  \\ ";
            info.col5        = BRED " (_) |   |   ";
            info.col6        = BRED "   \\  --- _/ ";
            info.col7        = BRED "      ---(_) ";
            info.col8        = BRED "";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osname, "void", 4) == 0) {
            info.col1 = BGREEN "      _____\n";
            info.col2 = BGREEN "   _  \\____ -  ";
            info.col3 = BGREEN "  / / ____ \\ \\ ";
            info.col4 = BGREEN " / / /    \\ \\ \\";
            info.col5 = BGREEN " | |  " BGRAY BITAL "VOID  " BGREEN "| |";
            info.col6 = BGREEN " \\ \\ \\____/ / /";
            info.col7 = BGREEN "  \\ \\____  /_/ ";
            info.col8 = BGREEN "   -_____\\";
            info.getPkgCount = "xbps-query -l | wc -l";
        } else if (strncmp(osname, "Zorin OS", 8) == 0) {
            info.col1        = BBLUE "    ______   \n";
            info.col2        = BBLUE "   /______\\  ";
            info.col3        = BBLUE "  /      / \\ ";
            info.col4        = BBLUE " /      /   \\";
            info.col5        = BBLUE " \\     /    /";
            info.col6        = BBLUE "  \\   /___ / ";
            info.col7        = BBLUE "   \\______/  ";
            info.col8        = BBLUE "";
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        }
    } else if (strncmp(sysInfo.sysname, "Darwin", 6) == 0) {
        info.col1 = "" BYELLOW;
        info.col2 = BGREEN "          .:'   " BYELLOW;
        info.col3 = BGREEN "      __ :'__   " BYELLOW;
        info.col4 = BYELLOW "   .'`__`-'__``." BYELLOW;
        info.col5 = BRED "  :__________.-'" BYELLOW;
        info.col6 = BRED "  :_________:   " BYELLOW;
        info.col7 = BMAGENTA "   :_________`-;" BYELLOW;
        info.col8 = BBLUE "    `.__.-.__.' " BYELLOW;
        if ((strncmp(sysInfo.machine, "iPhone", 6) == 0) ||
            (strncmp(sysInfo.machine, "iPad", 4) == 0) ||
            (strncmp(sysInfo.machine, "iPod", 4) == 0)) {
            info.getPkgCount = "dpkg -l | tail -n+6 | wc -l";

            char *iosVer = malloc(1024);
            strcpy(iosVer, "iOS ");
            char *productVer = pipeRead("sw_vers -productVersion");

            strcat(iosVer, productVer);
            free(productVer);
            osname = iosVer;
            free(iosVer);
        } else {
            info.getPkgCount =
                "ls /usr/local/Cellar/* | grep ':' | wc -l | xargs";

            char *macVer = malloc(64);
            strcpy(macVer, "macOS ");
            char *productVer = pipeRead("sw_vers -productVersion");

            strcat(macVer, productVer);
            free(productVer);
            osname = macVer;
            free(macVer);
        }
    } else if (strncmp(sysInfo.sysname, "FreeBSD", 7) == 0) {
        info.col1        = BRED "";
        info.col2        = BRED " /\\,-'''''-,/\\";
        info.col3        = BRED " \\_)       (_/";
        info.col4        = BRED " |           |";
        info.col5        = BRED " |           |";
        info.col6        = BRED "  ;         ; ";
        info.col7        = BRED "   '-_____-'  ";
        info.col8        = BRED "";
        info.getPkgCount = "pkg info | wc -l | tr -d ' '";
        osname           = sysInfo.sysname;
    } else if (strncmp(sysInfo.sysname, "OpenBSD", 7) == 0) {
        info.col1        = BYELLOW "      _____    \n";
        info.col2        = BYELLOW "    \\-     -/  ";
        info.col3        = BYELLOW " \\_/         \\ ";
        info.col4        = BYELLOW " |        " BWHITE "O O" BYELLOW " |";
        info.col5        = BYELLOW " |_  <   )  3 )";
        info.col6        = BYELLOW " / \\         / ";
        info.col7        = BYELLOW "    /-_____-\\  ";
        info.col8        = BYELLOW "";
        info.getPkgCount = "/bin/ls -1 /var/db/pkg/ | wc -l | tr -d ' '";
        osname           = sysInfo.sysname;
    } else if (strncmp(sysInfo.sysname, "NetBSD", 6) == 0) {
    }
    pkgCount = pipeRead(info.getPkgCount);

    return NULL;
}

void colourDraw()
{
    if (PrintColours == false)
        return;

    printf("%s%s", VariableColour, ColourText);
    for (int i = 31; i < 37; i++) {
        printf("\033[0;%dm%s", i, ColourCharacter);
    } // print regular term colours
    // printf("\n                  ");
    // for (int i = 31; i < 37; i++) {
    //     printf("\033[1;%dm%s", i, ColourCharacter);
    // }

    printf("\n");
}

int main()
{
    struct utsname sysInfo;
    uname(&sysInfo);
    pthread_t threads[6];

    pthread_create(&threads[0], NULL, user, NULL);
    pthread_create(&threads[1], NULL, host, NULL);
    pthread_create(&threads[2], NULL, os, NULL);
    pthread_create(&threads[3], NULL, kernel, NULL);
    pthread_create(&threads[4], NULL, uptime, NULL);
    pthread_create(&threads[5], NULL, shell, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    /* os function must be run to get info.col1 */
    pthread_join(threads[2], NULL);
    printf("%s", info.col1);
    printf("%s  " BYELLOW "%s" BRED "@" BBLUE "%s\n", info.col2, username,
           hostname);
    printf("%s  %s%s%s%s\n", info.col3, VariableColour, OsText, TextColour,
           osname);
    pthread_join(threads[3], NULL);
    printf("%s  %s%s%s%s\n", info.col4, VariableColour, KernelText, TextColour,
           krnlver);
    pthread_join(threads[4], NULL);
    printf("%s  %s%s%s%ldh %ldm\n", info.col5, VariableColour, UptimeText,
           TextColour, uptimeH, uptimeM);
    pthread_join(threads[5], NULL);
    printf("%s  %s%s%s%s\n", info.col6, VariableColour, ShellText, TextColour,
           shellname);
    printf("%s  %s%s%s%s\n", info.col7, VariableColour, PackageText, TextColour,
           pkgCount);
    printf("%s  ", info.col8);

    colourDraw();
    printf("\n%s", RESET);

    return 0;
}
