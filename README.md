<h2 align="center"> afetch </h2>
<h4 align="center"> Simple system info </h4>

<p align="center">
<a href="https://repology.org/project/afetch/versions"> <img src="https://repology.org/badge/vertical-allrepos/afetch.svg" height="85px"> </a>
</p>

<img align="right" src="img/logo.png" height="250px">
Fast and simple system info (for UNIX based operating systems) written in POSIX compliant C99, that can be configured at compile time by editing the <a href="src/config.h">config.h</a> file. It uses the C Preprocessor to implement config options at compile time. <br> <br>

<h3> Why use afetch? </h3>
afetch is written in C99, meaning that it should be able to be compiled with almost all C compilers. As well as being written in a very fast language, it's multithreaded. This makes it even faster, as well as distinguishing it from similar programs written is POSIX sh. The only limitations it has is the speed of your distros package manager! </p>


**Requirements**
*  `/etc/os-release` file for package count on Linux
*  A C compiler
*  A <a href="https://en.wikipedia.org/wiki/C_POSIX_library">compatible C standard library</a> implementation
*  pthreads

**Package count supported**

*  Alpine
*  Arch
*  Arch7
*  ArchBang
*  Arco
*  Artix
*  CelOS
*  Debian
*  Deepin
*  Elementary OS
*  EndeavourOS
*  Fedora (slow due to package manager)
*  FreeBSD
*  Gentoo
*  MacOS (homebrew)
*  Manjaro
*  Mint
*  NetBSD
*  NixOS
*  OpenBSD
*  OpenSUSE Leap (slow due to package manager)
*  OpenSUSE Tumbleweed (slow due to package manager)
*  Parabola
*  Pop!\_OS
*  postmarketOS
*  Slackware
*  Solus
*  Ubuntu
*  Void
*  Zorin

afetch is made to be run anywhere, but if your operating system isn't in the list above then open an issue! If on Linux please show the output of `cat /etc/os-release`, or if you're using something else then `uname -s`. 


**Configuration options**
*  Custom text for each seperate row of info
*  Force upper/lowercase text
*  Option to print colour blocks, and choose a character for the block
*  More to be implemented soon



**To do**
*  Make README.md more dynamic (adapt to different screen sizes)
*  Add links to information about distros in README.md
*  Find more efficient ways to do certain things, like the `/etc/os-release` part on Linux.
*  Create CONFIG.md file with in depth guide to customisation

**Thanks**
*  All the [contributors](https://github.com/13-CF/afetch/graphs/contributors) <3

*  [neofetch](https://github.com/dylanaraps/neofetch)
*  [ufetch](https://github.com/jschx/ufetch)
*  [nerdfetch](https://github.com/ThatOneCalculator/NerdFetch)
*  [bitfetch](https://gitlab.com/bit9tream/bitfetch)


