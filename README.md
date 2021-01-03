<h2 align="center"> afetch </h2>

<h3 align="center"> <img src="img/logo.png"> </h3>


<p align=center>Fast and simple system info (for UNIX based operating systems) written in POSIX compliant C99, that can be configured at compile time by editing the <a href="src/config.h">config.h</a> file. It uses the C Preprocessor to implement config options at compile time. <br> <br>
afetch is a command line tool to display basic system information. The goal is to be highly configurable, extremely fast and work with no dependencies apart from the POSIX header files. </p>

**Requirments**
*  A `/etc/os-release` file 
*  A C compiler
*  A <a href="https://en.wikipedia.org/wiki/C_POSIX_library">compatible C standard library</a> implementation

**Package count supported**

*  Void
*  Gentoo
*  Arch
*  Artix
*  Arco
*  Fedora (slow due to package manager)
*  OpenSUSE Leap (slow due to package manager)
*  OpenSUSE Tumbleweed (slow due to package manager)
*  Debian
*  Ubuntu
*  Manjaro
*  Alpine
*  Slackware
*  Pop!_OS
*  NixOS
*  FreeBSD 
*  OpenBSD 
*  NetBSD
*  DragonflyBSD

If your OS isn't in the list above, you'll still be able to build the program as long as you're either using Linux, or another UNIX based operating system with the necessary header files.


**Please request your distro if you want it added**

If on Linux, please show me the contents of the `/etc/os-release` file. 


![gif](img/preview.gif)

**Manual**

I have provided a manual for configuration in the [afetch.1](src/afetch.1) file. You can view it by running `mandoc src/afetch.1 | less`, or `man afetch` if you've already ran `make install`.


**Configuration options**
*  Support for one custom shell command (replaces the package count)
*  Custom colours
*  Custom artwork
*  Edit headings for info rows 
*  Force lowercase text (unstable)
*  Show path to shell
*  Select text colour
*  Colour blocks



**To do**
*  Optimise


**Thanks**
*  [neofetch](https://github.com/dylanaraps/neofetch)
*  [ufetch](https://github.com/jschx/ufetch)
*  [nerdfetch](https://github.com/ThatOneCalculator/NerdFetch)
*  [bitfetch](https://gitlab.com/bit9tream/bitfetch)
