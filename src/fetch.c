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

typedef struct ascii_art {
    char *row1, *row2, *row3, *row4, *row5, *row6, *row7, *row8;
} ascii_art;

typedef struct uptime {
    int day, hour, minute;
} uptime;

char *pipe_read(const char *exec)
{
    FILE *pipe = popen(exec, "r");
    if (pipe == NULL)
        return NULL;
    char     *return_val   = malloc(256);
    const int scanf_return = fscanf(pipe, "%[^\n]256s", return_val);
    pclose(pipe);

    return scanf_return == EOF ? NULL : return_val;
}

uptime get_uptime()
{
    uptime          up;
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
    up.day    = time.tv_sec / (24 * 3600);
    up.hour   = (time.tv_sec / 3600) - (time.tv_sec / (24 * 3600) * 24);
    up.minute = (time.tv_sec / 60) - (time.tv_sec / 3600 * 60);
#endif
    return up;
}

char *get_shell()
{
    char *shell = getenv("SHELL");
    char *slash = strrchr(shell, '/');
    if (slash) {
        shell = slash + 1;
    }
    return shell;
}

void get_memory_usage(unsigned long *mem_used, unsigned long *mem_total)
{
    unsigned long mem_free, mem_available, buffers, cached, shmem,
        s_reclaimable;
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        printf("error");
        return;
    }

    char buf[1024] = {0}, *ptr;
    fread(buf, 1024, 1, fp);

    ptr = strstr(buf, "MemTotal:");
    sscanf(ptr, "MemTotal: %lu", mem_total);

    ptr = strstr(ptr, "MemFree:");
    sscanf(ptr, "MemFree: %lu", &mem_free);

    ptr = strstr(ptr, "MemAvailable:");
    sscanf(ptr, "MemAvailable: %lu", &mem_available);

    ptr = strstr(ptr, "Buffers:");
    sscanf(ptr, "Buffers: %lu", &buffers);

    ptr = strstr(ptr, "Cached:");
    sscanf(ptr, "Cached: %lu", &cached);

    ptr = strstr(ptr, "Shmem:");
    sscanf(ptr, "Shmem: %lu", &shmem);

    ptr = strstr(ptr, "SReclaimable:");
    sscanf(ptr, "SReclaimable: %lu", &s_reclaimable);

    *mem_used =
        *mem_total + shmem - mem_free - buffers - cached - s_reclaimable;

    fclose(fp);
}

void print_logo(ascii_art ascii)
{
    printf("%s\n", ascii.row1);
    printf("%s\n", ascii.row2);
    printf("%s\n", ascii.row3);
    printf("%s\n", ascii.row4);
    printf("%s\n", ascii.row5);
    printf("%s\n", ascii.row6);
    printf("%s\n", ascii.row7);
    printf("%s\n", ascii.row8);
}

void print_stats(char *host, struct utsname sys_info, struct uptime time,
                 char *pkg_cnt, char *shell, unsigned long mem_used,
                 unsigned long mem_total)
{
    int row = 7;

    printf("\033[8A");
    printf("\033[15C");

    if (PRINT_HOST) {
        printf("   " BYELLOW "%s" BRED "@" BBLUE "%s\n", getlogin(), host);
        printf("\033[15C");
        row--;
    }

    if (PRINT_OS) {
        printf("   " VARIABLE_COLOR OS_TEXT TEXT_COLOR DISTRO "\n");
        printf("\033[15C");
        row--;
    }

    if (PRINT_KERNEL) {
        printf("   " VARIABLE_COLOR KERNEL_TEXT TEXT_COLOR "%s\n",
               sys_info.release);
        printf("\033[15C");
        row--;
    }

    if (PRINT_UPTIME) {
        printf("   " VARIABLE_COLOR UPTIME_TEXT TEXT_COLOR);
        if (time.day)
            printf("%dd ", time.day);
        if (time.hour)
            printf("%dh ", time.hour);
        if (time.minute)
            printf("%dm ", time.minute);

        printf("\n\033[15C");
        row--;
    }

    if (PRINT_PKGS) {
        printf("   " VARIABLE_COLOR PACKAGE_TEXT TEXT_COLOR "%s\n", pkg_cnt);
        printf("\033[15C");
        row--;
    }

    if (PRINT_SHELL) {
        printf("   " VARIABLE_COLOR PACKAGE_TEXT TEXT_COLOR "%s\n", shell);
        printf("\033[15C");
        row--;
    }

    if (PRINT_MEMORY) {
        printf("   " VARIABLE_COLOR MEMORY_TEXT TEXT_COLOR);
        printf("%lu/%lu MB (%d%%)\n", mem_used / 1024, mem_total / 1024,
               (int)(mem_used / (double)mem_total * 100));
        printf("\033[15C   ");
        row--;
    }

    if (PRINT_COLORS) {
        printf(VARIABLE_COLOR COLOR_TEXT);
        for (int i = 31; i < 37; i++) {
            printf("\033[0;%dm%s", i, COLOR_CHARACTER);
        } // print regular term colours
        printf("\n");
        row--;
    }

    if (row > 0)
        printf("\033[%dB", row);
    printf("%s\n", RESET);
}

int main()
{
    struct ascii_art logo = {ASCII_ART};
    struct utsname   sys_info;
    struct uptime    time;
    char             hostname[HOST_NAME_MAX + 1], *pkg_cnt, *shell;
    unsigned long    mem_used, mem_total;

    gethostname(hostname, HOST_NAME_MAX + 1);
    uname(&sys_info);
    time    = get_uptime();
    pkg_cnt = pipe_read(GET_PKG_CNT);
    shell   = get_shell();
    get_memory_usage(&mem_used, &mem_total);

    print_logo(logo);
    print_stats(hostname, sys_info, time, pkg_cnt, shell, mem_used, mem_total);
    free(pkg_cnt);

    return 0;
}

