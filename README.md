# afetch ~ Another Fetch
Simple system info written in C
Can be configured at compile time by editing the [config.h file](config.h) 

**Requirments**
*  A /etc/os-release file (/var/run/os-release works, or freebsd-version command)
*  A C compiler (preferably GCC, I can't get it to compile with clang on FreeBSD)
*  libsysinfo if on FreeBSD

**Currently Supports**
*  Void
*  Gentoo
*  Arch
*  Artix
*  Fedora (slow due to package manager)
*  OpenSUSE Leap (slow due to package manager)
*  OpenSUSE Tumbleweed (slow due to package manager)
*  Debian
*  Ubuntu
*  Manjaro
*  Alpine
*  FreeBSD (Makefile must be edited)
*  Slackware

**Building on FreeBSD**
*  You will have to install the libsysinfo package, then follow the instructions in the Makefile


**| Please request your distro if you want it added**


![gif](preview.gif)




**To do**
*  Improve Makefile
*  Clean up the config file
*  Find a faster way to list packages on distros using RPM

**Thanks**
*  [neofetch](https://github.com/dylanaraps/neofetch)

