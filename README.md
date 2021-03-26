<h2 align="center"> afetch </h2>

<h3 align="center"> <img src="img/logo.png"> </h3>


<p align=center>Fast and simple system info (for UNIX based operating systems) written in POSIX compliant C99, that can be configured at compile time by editing the <a href="src/config.h">config.h</a> file. It uses the C Preprocessor to implement config options at compile time. <br> <br>

<h3 align="center"> Why use afetch? </h3>
<p align="center"> afetch is written in C99, meaning that it should be able to be compiled with almost all C compilers. As well as being written in a very fast language, it's multithreaded. This makes it even faster, as well as distinguishing it from similar programs written is POSIX sh. The only limitations it has is the speed of your distros package manager! </p>

**Requirements**
*  `/etc/os-release` file for package count on Linux
*  A C compiler
*  A <a href="https://en.wikipedia.org/wiki/C_POSIX_library">compatible C standard library</a>implementation
*  pthreads

**Package count supported**

*  Alpine
*  Arch
*  ArchBang
*  Arco
*  Artix
*  Debian
*  Deepin
*  Elementary OS
*  EndeavourOS
*  Fedora (slow due to package manager)
*  FreeBSD
*  Gentoo
*  Parabola
*  Manjaro
*  NetBSD
*  NixOS
*  OpenBSD
*  OpenSUSE Leap (slow due to package manager)
*  OpenSUSE Tumbleweed (slow due to package manager)
*  Pop!_OS
*  Slackware
*  Solus
*  Ubuntu
*  Void
*  macOS (Homebrew)

If your OS isn't in the list above, you'll still be able to build and run the program as long as you're either using Linux, or another UNIX based operating system with the necessary header files.


**Please request your distro if you want it added**

If on Linux, please show me the contents of the `/etc/os-release` file.



**Configuration options**
*  Custom text for each seperate row of info
*  Force lowercase text for OS name
*  Option to print colour blocks or not
*  More to be implemented soon



**To do**
*  Find more efficient ways to do certain things, like the `/etc/os-release` part on Linux.
*  Implement more config options
*  Make sure it actually works on every Linux distro
*  Create CONFIG.md file with in depth guide to customisation

**Thanks**
*  All the [contributors](https://github.com/13-CF/afetch/graphs/contributors) <3

*  [neofetch](https://github.com/dylanaraps/neofetch)
*  [ufetch](https://github.com/jschx/ufetch)
*  [nerdfetch](https://github.com/ThatOneCalculator/NerdFetch)
*  [bitfetch](https://gitlab.com/bit9tream/bitfetch)


