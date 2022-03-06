#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include "colour.h"
#include "config.h"

typedef struct dist {
    char *col1, *col2, *col3, *col4, *col5, *col6, *col7, *col8;
    char *getPkgCount;
} dist;

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

char *kernel()
{
    static struct utsname kernelData;
    uname(&kernelData);
    return kernelData.release;
}

void uptime(long *uptimeH, long *uptimeM)
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
    *uptimeH = time.tv_sec / 3600;
    *uptimeM = (time.tv_sec / 60) - (time.tv_sec / 3600 * 60);
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

char *os(struct utsname *sysInfo, struct dist *inf)
{
    /* start */
    /* This whole section could probably be rewritten - it seems
       like a bit of a mess right now */
    char *osn = malloc(512);
    if (strncmp(sysInfo->sysname, "Linux", 5) == 0) {
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
        strcpy(osn, newContents);
        free(newContents);
        /* end */
        if (strncmp(osn, "Alpine Linux", 12) == 0) {
            inf->col1        = BBLUE "\n";
            inf->col2        = BBLUE "     /\\ /\\    ";
            inf->col3        = BBLUE "    /  \\  \\   ";
            inf->col4        = BBLUE "   /    \\  \\  ";
            inf->col5        = BBLUE "  /      \\  \\ ";
            inf->col6        = BBLUE " /        \\  \\";
            inf->col7        = BBLUE "           \\  ";
            inf->col8        = BBLUE "";
            inf->getPkgCount = "grep 'P:' /lib/apk/db/installed | wc -l";
        } else if (strncmp(osn, "Arch Linux", 10) == 0) {
            inf->col1        = BCYAN "";
            inf->col2        = BCYAN "       /\\      ";
            inf->col3        = BCYAN "      /  \\     ";
            inf->col4        = BCYAN "     /\\   \\    ";
            inf->col5        = BBLUE "    /      \\   ";
            inf->col6        = BBLUE "   /   ,,   \\  ";
            inf->col7        = BBLUE "  /   |  |  -\\ ";
            inf->col8        = BBLUE " /_-''    ''-_\\";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "Arch bang Linux", 15) == 0) {
            inf->col1        = BCYAN "           ____\n";
            inf->col2        = BCYAN "       /\\ /   /";
            inf->col3        = BCYAN "      /  /   / ";
            inf->col4        = BCYAN "     /   / /   ";
            inf->col5        = BCYAN "    /   /_/\\   ";
            inf->col6        = BCYAN "   /   __   \\  ";
            inf->col7        = BCYAN "  /   /_/\\   \\ ";
            inf->col8        = BCYAN " /_-''    ''-_\\";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "ArcoLinux", 9) == 0) {
            inf->col1        = BBLUE "";
            inf->col2        = BBLUE "       /\\      ";
            inf->col3        = BBLUE "      /  \\     ";
            inf->col4        = BBLUE "     / /\\ \\    ";
            inf->col5        = BBLUE "    / /  \\ \\   ";
            inf->col6        = BBLUE "   / /    \\ \\  ";
            inf->col7        = BBLUE "  / / _____\\ \\ ";
            inf->col8        = BBLUE " /_/  `----.\\_\\";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "Artix Linux", 11) == 0) {
            inf->col1        = BCYAN "";
            inf->col2        = BCYAN "       /\\      ";
            inf->col3        = BCYAN "      /  \\     ";
            inf->col4        = BCYAN "     /`'.,\\    ";
            inf->col5        = BCYAN "    /     ',   ";
            inf->col6        = BCYAN "   /      ,`\\  ";
            inf->col7        = BCYAN "  /   ,.'`.  \\ ";
            inf->col8        = BCYAN " /.,'`     `'.\\";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "CelOS", 5) == 0) {
            inf->col1 = BMAGENTA "\n";
            inf->col2 = BMAGENTA "     ______     ";
            inf->col3 = BMAGENTA "   _-" BWHITE " _____" BMAGENTA "\\" BWHITE
                                 "__  " BMAGENTA;
            inf->col4 = BMAGENTA "  -         -   ";
            inf->col5 =
                BWHITE "__" BMAGENTA "|" BWHITE "_____" BMAGENTA "     |  ";
            inf->col6 = BMAGENTA "  |          |  ";
            inf->col7 = BMAGENTA "  -_" BWHITE "  ______" BMAGENTA "/" BWHITE
                                 "_  " BMAGENTA;
            inf->col8 = BMAGENTA "    -______/    ";
            // have to add support for flatpak too
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
            /* TO DO: CREATE DEEPIN LOGO */
        } else if (strncmp(osn, "Deepin", 6) == 0) {
            inf->col1        = BRED "\n";
            inf->col2        = BRED "";
            inf->col3        = BRED "";
            inf->col4        = BRED "";
            inf->col5        = BRED "";
            inf->col6        = BRED "";
            inf->col7        = BRED "";
            inf->col8        = BRED "";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osn, "Debian GNU/Linux", 16) == 0) {
            inf->col1        = BRED "   _____\n";
            inf->col2        = BRED "  /  __ \\ ";
            inf->col3        = BRED " |  /    |";
            inf->col4        = BRED " |  \\___- ";
            inf->col5        = BRED " -_       ";
            inf->col6        = BRED "   --_    ";
            inf->col7        = BRED "          ";
            inf->col8        = BRED "";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osn, "Arch7", 10) == 0) {
            inf->col1        = BCYAN "";
            inf->col2        = BCYAN "  _______      ";
            inf->col3        = BCYAN " |____   \\     ";
            inf->col4        = BCYAN "     / /\\ \\    ";
            inf->col5        = BCYAN "    / /__\\ \\   ";
            inf->col6        = BCYAN "   / /____\\ \\  ";
            inf->col7        = BCYAN "  /_/      \\_\\ ";
            inf->col8        = BCYAN "";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "elementary OS", 12) == 0) {
            inf->col1        = BCYAN "";
            inf->col2        = BCYAN "   _______  ";
            inf->col3        = BCYAN "  / ____  \\ ";
            inf->col4        = BCYAN " /  |  /  /\\";
            inf->col5        = BCYAN " |__\\ /  / |";
            inf->col6        = BCYAN " \\   /__/  /";
            inf->col7        = BCYAN "  \\_______/ ";
            inf->col8        = BCYAN "";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osn, "EndeavourOS", 11) == 0) {
            inf->col1        = BCYAN "";
            inf->col2        = BRED "      /" BBLUE "\\     " BCYAN;
            inf->col3        = BRED "    /" BBLUE "/  \\" BCYAN "\\   " BCYAN;
            inf->col4        = BRED "   /" BBLUE "/    \\ " BCYAN "\\ " BCYAN;
            inf->col5        = BRED " / " BBLUE "/     _) " BCYAN ")" BCYAN;
            inf->col6        = BRED "/_" BBLUE "/___-- " BCYAN "__- " BCYAN;
            inf->col7        = BCYAN " /____--     " BCYAN;
            inf->col8        = BCYAN "";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "Fedora", 6) == 0) {
            inf->col1        = BWHITE "      _____\n" BBLUE;
            inf->col2        = BWHITE "     /   __)" BBLUE "\\ ";
            inf->col3        = BWHITE "     |  /  " BBLUE "\\ \\";
            inf->col4        = BWHITE "  ___|  |" BBLUE "__/ /";
            inf->col5        = BBLUE " / " BWHITE "(_    _)" BBLUE "_/ ";
            inf->col6        = BBLUE "/ /  " BWHITE "|  |     " BBLUE;
            inf->col7        = BBLUE "\\ \\" BWHITE "__/  |     " BBLUE;
            inf->col8        = BBLUE " \\" BWHITE "(_____/" BBLUE;
            inf->getPkgCount = "[[ $(which sqlite3 2>/dev/null) && $? -ne "
                               "1 ]] && (sqlite3 "
                               "/var/lib/rpm/rpmdb.sqlite \"select * from "
                               "Name\"|wc -l) || rpm -qa | wc -l";
        } else if (strncmp(osn, "Gentoo", 6) == 0) {
            inf->col1        = BMAGENTA "   _-----_ \n";
            inf->col2        = BMAGENTA "  (       \\  ";
            inf->col3        = BMAGENTA "  \\    0   \\ ";
            inf->col4        = BMAGENTA "   \\        )";
            inf->col5        = BMAGENTA "   /      _/ ";
            inf->col6        = BMAGENTA "  (     _-   ";
            inf->col7        = BMAGENTA "  \\____-     ";
            inf->col8        = BWHITE "\n";
            inf->getPkgCount = "qlist -IRv | wc -l";
        } else if (strncmp(osn, "KDE neon", 8) == 0) {
            inf->col1        = BGREEN "";
            inf->col2        = BGREEN "            ";
            inf->col3        = BGREEN "     --- _  ";
            inf->col4        = BGREEN "  /  ---  \\ ";
            inf->col5        = BGREEN " |  |   |  |";
            inf->col6        = BGREEN "  \\  --- _/ ";
            inf->col7        = BGREEN "     ---    ";
            inf->col8        = BGREEN "";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osn, "Linux Mint", 10) == 0) {
            inf->col1        = BGREEN "   _____________   \n";
            inf->col2        = BGREEN "  |_            \\  ";
            inf->col3        = BGREEN "   |  | _____  |   ";
            inf->col4        = BGREEN "   |  | | | |  |   ";
            inf->col5        = BGREEN "   |  | | | |  |   ";
            inf->col6        = BGREEN "   |  \\_____/  |   ";
            inf->col7        = BGREEN "   \\___________/   ";
            inf->col8        = BGREEN "";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osn, "Manjaro", 7) == 0) {
            inf->col1        = BGREEN "  ________  __ \n";
            inf->col2        = BGREEN " |       | |  |";
            inf->col3        = BGREEN " |   ____| |  |";
            inf->col4        = BGREEN " |  |  __  |  |";
            inf->col5        = BGREEN " |  | |  | |  |";
            inf->col6        = BGREEN " |  | |  | |  |";
            inf->col7        = BGREEN " |  | |  | |  |";
            inf->col8        = BGREEN " |__| |__| |__|";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "NixOS", 5) == 0) {
            inf->col1        = BMAGENTA "             \n";
            inf->col2        = BMAGENTA "   \\\\  \\\\ //     ";
            inf->col3        = BMAGENTA "  ==\\\\__\\\\/ //   ";
            inf->col4        = BMAGENTA "    //   \\\\//    ";
            inf->col5        = BMAGENTA " ==//     //==   ";
            inf->col6        = BMAGENTA "  //\\\\___//      ";
            inf->col7        = BMAGENTA " // /\\\\  \\\\==    ";
            inf->col8        = BMAGENTA "   // \\\\  \\\\     ";
            inf->getPkgCount = "nix-store -q --requisites "
                               "/run/current-system/sw | wc -l";
        } else if (strncmp(osn, "openSUSE Leap", 10) == 0 ||
                   strncmp(osn, "openSUSE Tumbleweed", 19) == 0) {
            inf->col1        = BGREEN "   _______\n";
            inf->col2        = BGREEN " __|   __ \\ ";
            inf->col3        = BGREEN "      / .\\ \\";
            inf->col4        = BGREEN "      \\__/ |";
            inf->col5        = BGREEN "    _______|";
            inf->col6        = BGREEN "    \\_______";
            inf->col7        = BGREEN " __________/";
            inf->col8        = BGREEN "";
            inf->getPkgCount = "rpm -qa | wc -l";
        } else if (strncmp(osn, "Parabola", 8) == 0) {
            inf->col1        = BMAGENTA "";
            inf->col2        = BMAGENTA "   __ __ __  _  ";
            inf->col3        = BMAGENTA " .`_//_//_/ / `.";
            inf->col4        = BMAGENTA "           /  .`";
            inf->col5        = BMAGENTA "          / .`  ";
            inf->col6        = BMAGENTA "         /.`    ";
            inf->col7        = BMAGENTA "        /`      ";
            inf->col8        = BMAGENTA "";
            inf->getPkgCount = "pacman -Qq | wc -l";
        } else if (strncmp(osn, "Pop!_OS", 7) == 0) {
            inf->col1        = BCYAN " ______\n";
            inf->col2        = BCYAN " \\   _ \\        __";
            inf->col3        = BCYAN "  \\ \\ \\ \\      / /";
            inf->col4        = BCYAN "   \\ \\_\\ \\    / / ";
            inf->col5        = BCYAN "    \\  ___\\  /_/  ";
            inf->col6        = BCYAN "     \\ \\    _     ";
            inf->col7        = BCYAN "    __\\_\\__(_)_   ";
            inf->col8        = BCYAN "   (___________)";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osn, "postmarketOS", 13) == 0) {
            inf->col1        = BGREEN "        /\\       \n";
            inf->col2        = BGREEN "       /  \\      ";
            inf->col3        = BGREEN "      /    \\     ";
            inf->col4        = BGREEN "     /\\__   \\    ";
            inf->col5        = BGREEN "    /   /\\  _\\   ";
            inf->col6        = BGREEN "   /   ___\\/  \\  ";
            inf->col7        = BGREEN "  /    \\       \\ ";
            inf->col8        = BGREEN " /_____/________\\";
            inf->getPkgCount = "grep 'P:' /lib/apk/db/installed | wc -l";
        } else if (strncmp(osn, "Slackware", 10) == 0) {
            inf->col1        = BBLUE "    ________\n";
            inf->col2        = BBLUE "   /  ______| ";
            inf->col3        = BBLUE "   | |______  ";
            inf->col4        = BBLUE "   \\______  \\ ";
            inf->col5        = BBLUE "    ______| | ";
            inf->col6        = BBLUE " | |________/ ";
            inf->col7        = BBLUE " |____________";
            inf->col8        = BBLUE "";
            inf->getPkgCount = "ls /var/log/packages | wc -l";
        } else if (strncmp(osn, "Solus", 5) == 0) {
            inf->col1        = BMAGENTA "     __________\n";
            inf->col2        = BMAGENTA "    /          \\   ";
            inf->col3        = BMAGENTA "   /   /\\ \\     \\  ";
            inf->col4        = BMAGENTA "  /   /  \\ \\     \\ ";
            inf->col5        = BMAGENTA " |   /    \\ \\     |";
            inf->col6        = BMAGENTA "  \\--------------/ ";
            inf->col7        = BMAGENTA "   \\------------/  ";
            inf->col8        = BMAGENTA "    \\----------/";
            inf->getPkgCount = "ls /var/lib/eopkg/package/ | wc -l";
        } else if (strncmp(osn, "Ubuntu", 6) == 0) {
            inf->col1        = BRED "";
            inf->col2        = BRED "          _  ";
            inf->col3        = BRED "      ---(_) ";
            inf->col4        = BRED "  _/  ---  \\ ";
            inf->col5        = BRED " (_) |   |   ";
            inf->col6        = BRED "   \\  --- _/ ";
            inf->col7        = BRED "      ---(_) ";
            inf->col8        = BRED "";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        } else if (strncmp(osn, "void", 4) == 0) {
            inf->col1 = BGREEN "      _____\n";
            inf->col2 = BGREEN "   _  \\____ -  ";
            inf->col3 = BGREEN "  / / ____ \\ \\ ";
            inf->col4 = BGREEN " / / /    \\ \\ \\";
            inf->col5 = BGREEN " | |  " BGRAY BITAL "VOID  " BGREEN "| |";
            inf->col6 = BGREEN " \\ \\ \\____/ / /";
            inf->col7 = BGREEN "  \\ \\____  /_/ ";
            inf->col8 = BGREEN "   -_____\\";
            inf->getPkgCount = "xbps-query -l | wc -l";
        } else if (strncmp(osn, "Zorin OS", 8) == 0) {
            inf->col1        = BBLUE "    ______   \n";
            inf->col2        = BBLUE "   /______\\  ";
            inf->col3        = BBLUE "  /      / \\ ";
            inf->col4        = BBLUE " /      /   \\";
            inf->col5        = BBLUE " \\     /    /";
            inf->col6        = BBLUE "  \\   /___ / ";
            inf->col7        = BBLUE "   \\______/  ";
            inf->col8        = BBLUE "";
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";
        }
    } else if (strncmp(sysInfo->sysname, "Darwin", 6) == 0) {
        inf->col1 = "" BYELLOW;
        inf->col2 = BGREEN "          .:'   " BYELLOW;
        inf->col3 = BGREEN "      __ :'__   " BYELLOW;
        inf->col4 = BYELLOW "   .'`__`-'__``." BYELLOW;
        inf->col5 = BRED "  :__________.-'" BYELLOW;
        inf->col6 = BRED "  :_________:   " BYELLOW;
        inf->col7 = BMAGENTA "   :_________`-;" BYELLOW;
        inf->col8 = BBLUE "    `.__.-.__.' " BYELLOW;
        if ((strncmp(sysInfo->machine, "iPhone", 6) == 0) ||
            (strncmp(sysInfo->machine, "iPad", 4) == 0) ||
            (strncmp(sysInfo->machine, "iPod", 4) == 0)) {
            inf->getPkgCount = "dpkg -l | tail -n+6 | wc -l";

            char *iosVer = malloc(1024);
            strcpy(iosVer, "iOS ");
            char *productVer = pipeRead("sw_vers -productVersion");

            strcat(iosVer, productVer);
            free(productVer);
            osn = iosVer;
            free(iosVer);
        } else {
            inf->getPkgCount =
                "ls /usr/local/Cellar/* | grep ':' | wc -l | xargs";

            char *macVer = malloc(64);
            strcpy(macVer, "macOS ");
            char *productVer = pipeRead("sw_vers -productVersion");

            strcat(macVer, productVer);
            free(productVer);
            osn = macVer;
            free(macVer);
        }
    } else if (strncmp(sysInfo->sysname, "FreeBSD", 7) == 0) {
        inf->col1        = BRED "";
        inf->col2        = BRED " /\\,-'''''-,/\\";
        inf->col3        = BRED " \\_)       (_/";
        inf->col4        = BRED " |           |";
        inf->col5        = BRED " |           |";
        inf->col6        = BRED "  ;         ; ";
        inf->col7        = BRED "   '-_____-'  ";
        inf->col8        = BRED "";
        inf->getPkgCount = "pkg info | wc -l | tr -d ' '";
        osn              = sysInfo->sysname;
    } else if (strncmp(sysInfo->sysname, "OpenBSD", 7) == 0) {
        inf->col1        = BYELLOW "      _____    \n";
        inf->col2        = BYELLOW "    \\-     -/  ";
        inf->col3        = BYELLOW " \\_/         \\ ";
        inf->col4        = BYELLOW " |        " BWHITE "O O" BYELLOW " |";
        inf->col5        = BYELLOW " |_  <   )  3 )";
        inf->col6        = BYELLOW " / \\         / ";
        inf->col7        = BYELLOW "    /-_____-\\  ";
        inf->col8        = BYELLOW "";
        inf->getPkgCount = "/bin/ls -1 /var/db/pkg/ | wc -l | tr -d ' '";
        osn              = sysInfo->sysname;
    } else if (strncmp(sysInfo->sysname, "NetBSD", 6) == 0) {
    }
    return osn;
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
        .col7 =
            YELLOW "  _" GRAY "/\\ " WHITE "__)" GRAY "/" YELLOW "_" GRAY ") ",
        .col8        = YELLOW "  \\/" GRAY "-____" YELLOW "\\/  ",
        .getPkgCount = "echo unsupported",
    };
    struct utsname sysInfo;
    uname(&sysInfo);
    char *username, hostname[HOST_NAME_MAX + 1], *osname = NULL, *shellname,
                                                 *pkgCount, *krnlver;
    long uptimeH, uptimeM;

    username = getenv("USER");
    gethostname(hostname, HOST_NAME_MAX + 1);
    osname  = os(&sysInfo, &info);
    krnlver = kernel();
    uptime(&uptimeH, &uptimeM);
    shellname = shell();
    pkgCount  = pipeRead(info.getPkgCount);

    printf("%s", info.col1);
    printf("%s  " BYELLOW "%s" BRED "@" BBLUE "%s\n", info.col2, username,
           hostname);
    printf("%s  %s%s%s%s\n", info.col3, VariableColour, OsText, TextColour,
           osname);
    printf("%s  %s%s%s%s\n", info.col4, VariableColour, KernelText, TextColour,
           krnlver);
    printf("%s  %s%s%s%ldh %ldm\n", info.col5, VariableColour, UptimeText,
           TextColour, uptimeH, uptimeM);
    printf("%s  %s%s%s%s\n", info.col6, VariableColour, ShellText, TextColour,
           shellname);
    printf("%s  %s%s%s%s\n", info.col7, VariableColour, PackageText, TextColour,
           pkgCount);
    printf("%s  ", info.col8);

    colourDraw();
    printf("\n%s", RESET);

    free(osname);
    return 0;
}
