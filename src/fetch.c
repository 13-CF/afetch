#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "color.h"
#include "config.h"

typedef struct ascii_art {
    char *row1, *row2, *row3, *row4, *row5, *row6, *row7, *row8;
} ascii_art;

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

void memory()
{
    unsigned long mem_used, mem_total, mem_free, mem_available, buffers, cached, shmem, s_reclaimable;
    int fd = open("/proc/meminfo", O_RDONLY);
    if (fd < 0) {
        printf("error");
        return;
    }

    char buf[1024] = {0}, *ptr;
    read(fd, buf, 1024 - 1);

    ptr = strstr(buf, "MemTotal:");
    sscanf(ptr, "MemTotal: %lu", &mem_total);

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

    mem_used = mem_total + shmem - mem_free - buffers - cached - s_reclaimable;

    printf("%luMB / %luMB\n", mem_used / 1024, mem_total / 1024);

    close(fd);
}

void colour_draw()
{
    if (!PRINT_COLORS)
        return;

    printf("%s%s", VARIABLE_COLOR, COLOR_TEXT);
    for (int i = 31; i < 37; i++) {
        printf("\033[0;%dm%s", i, COLOR_CHARACTER);
    } // print regular term colours
    printf("\n");
}

int main()
{
    struct ascii_art logo = {ASCII_ART};
    struct utsname   sys_info;
    uname(&sys_info);
    char hostname[HOST_NAME_MAX + 1], *pkg_cnt;
    long uptime_h, uptime_m;

    gethostname(hostname, HOST_NAME_MAX + 1);
    uptime(&uptime_h, &uptime_m);
    pkg_cnt = pipe_read(GET_PKG_CNT);

    printf("%s   " BYELLOW "%s" BRED "@" BBLUE "%s\n", logo.row1, getlogin(),
           hostname); // user@host
    printf("%s   %s%s%s%s\n", logo.row2, VARIABLE_COLOR, OS_TEXT, TEXT_COLOR,
           DISTRO); // osname
    printf("%s   %s%s%s%s\n", logo.row3, VARIABLE_COLOR, KERNEL_TEXT,
           TEXT_COLOR, sys_info.release); // kernel version
    printf("%s   %s%s%s%ldh %ldm\n", logo.row4, VARIABLE_COLOR, UPTIME_TEXT,
           TEXT_COLOR, uptime_h, uptime_m); // uptime
    printf("%s   %s%s%s%s\n", logo.row5, VARIABLE_COLOR, SHELL_TEXT, TEXT_COLOR,
           shell()); // shell
    printf("%s   %s%s%s%s\n", logo.row6, VARIABLE_COLOR, PACKAGE_TEXT,
           TEXT_COLOR, pkg_cnt); // package count
    printf("%s   %s%s%s", logo.row7, VARIABLE_COLOR, MEMORY_TEXT, TEXT_COLOR);
    memory();
    printf("%s   ", logo.row8);
    colour_draw();

    printf("%s\n", RESET);
    free(pkg_cnt);

    return 0;
}

