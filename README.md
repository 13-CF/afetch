<h2 align="center"> afetch </h2>

<h3 align="center"> <img src="https://raw.githubusercontent.com/13-CF/afetch/master/logo.png"> </h3>


<p align=center>Fast and simple POSIX compliant system info written in C99, that can be configured at compile time by editing the <a href="https://raw.githubusercontent.com/13-CF/afetch/master/config.h"> config.h</a> file. <br> <br>
afetch is a command line tool to display basic system information. The goal is to be highly configurable, extremely fast and work with minimal dependencies. </p>

**Requirments**
*  A /etc/os-release file 
*  A C compiler 

**Currently Supports**
If an OS/distro is marked as supported, then that means the number of packages and a custom logo will be displayed, but the program should still work if your OS/distro isn't on this list.


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
*  FreeBSD 
*  OpenBSD 
*  Slackware
*  Pop!_OS

It can also be build on a variety of other POSIX complient operating systems that have the necessary header files. It's been tested on MINIX and NetBSD (which may be supported soon)


**Please request your distro if you want it added**
If on Linux, please show me the contents of the `/etc/os-release` file. 


![gif](preview.gif)

**Manual**

I have provided a manual for configuration in the [afetch.1](afetch.1) file. You can view it by running `mandoc afetch.1 | less`, or `man afetch` if you've already ran `make install`.


**Configuration options**
*  Custom colours
*  Custom artwork
*  Edit headings for info rows 
*  Force lowercase text (unstable)
*  Show path to shell
*  Select text colour
*  Colour blocks



**To do**
*  Fix segfaults on certain distros when lowercase text is enabled, maybe a memory error?
*  Improve Makefile
*  Find a faster way to list packages on distros using RPM

**Thanks**
*  [neofetch](https://github.com/dylanaraps/neofetch)
*  [ufetch](https://github.com/jschx/ufetch)
*  [nerdfetch](https://github.com/ThatOneCalculator/NerdFetch)
*  [bitfetch](https://gitlab.com/bit9tream/bitfetch)
