<h2 align="center"> afetch </h2>

<h3 align="center"> <img src="https://raw.githubusercontent.com/13-CF/afetch/master/logo.png"> </h3>


<p align=center>Fast and simple system info written in C, that can be configured at compile time by editing the <a href="https://raw.githubusercontent.com/13-CF/afetch/master/config.h"> config.h</a> file. <br> <br>
afetch is a command line tool to display basic system information. The goal is to be highly configurable, extremely fast and work with minimal dependencies. </p>

**Requirments**
*  A /etc/os-release file (/var/run/os-release)
*  A C compiler

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
*  FreeBSD (patch must be applied)
*  Slackware
*  Pop!_OS


**| Please request your distro if you want it added**


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
