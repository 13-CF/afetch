# aFetch ~ Another Fetch
Simple system info written in C
Can be configured at compile time by editing the [config.h file](config.h) 

**Requirments**
*  A /etc/os-release file (/var/run/os-release on BSDs also works)
*  A C compiler
*  libsysinfo if on FreeBSD

**Currently Supports**
*  Void
*  Gentoo
*  Arch
*  Artix
*  Fedora (slow due to the package manager)
*  Debian
*  Ubuntu
*  Manjaro
*  Alpine


**Partial Support**
*  FreeBSD (ldflags must be edited in the makefile to include sysinfo)

**Building on FreeBSD**
You will have to install the libsysinfo package, then follow the instructions in the first line of the makefile


**Please request your distro if you want it added**


![Screenshot on Void](screenshot1.png)
![screenshot on FreeBSD](screenshot2.png)

(I don't use FreeBSD, but the screenshot above should look similar)


**To do**
*  Add support for more distros (please request your distro, and provide the content of the /etc/os-release file)
*  Fix strncmp function deleting needed characters (this will help make the program more efficient, with less if statements.
*  Improve Makefile

**Thanks**
*  [neofetch](https://github.com/dylanaraps/neofetch)

