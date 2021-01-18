#define CUSTOMCMD 1
#define PKGCMD "ps aux | tail -n+1 | wc -l | tr -d ' '"
//---------------------------------------------------------------------------------------------
#define LOWERCASE 1
//---------------------------------------------------------------------------------------------
#define SHELLPATH 1
//---------------------------------------------------------------------------------------------
#define BLOCKS 1
#define BLOCKCHAR " ██"
	/*
Block characters are shown inside this comment. If you can't see them, then your current font doesn't support them

	▀ ▁ ▂ ▃ ▄ ▅ ▆ ▇ █ ▉ ▊ ▋ ▌ ▍ ▎ ▏

	█ ▄ ▀ ●
	*/
//---------------------------------------------------------------------------------------------
#define USERTEXT    "     USER"//
#define DISROTEXT   "   DISTRO"//
#define KERNELTEXT  "   KERNEL"//
#define UPTIMETEXT  "   UPTIME"//
#define SHELLTEXT   "    SHELL"//
#define PACKAGETEXT "     PKGS"//
//---------------------------------------------------------------------------------------------
#define TEXTCOLOUR WHITE
//---------------------------------------------------------------------------------------------

//#define OVERRIDECOLOUR
#define CUSTOMCOLOUR "\033[1;33m"

//---------------------------------------------------------------------------------------------

#define CUSTOMART 1

#define COL1 BRED     "\033[1;36m     ___   \n"
#define COL2 BRED     "\033[1;31m ___\033[1;36m/   \\\033[1;31m___ " //info starts on column 2
#define COL3 BRED     "\033[1;31m/   \033[1;36m'---'\033[1;31m   \\"
#define COL4 BRED     "\033[1;31m'--_______--'"
#define COL5 BRED     "\033[1;33m     / \\     "
#define COL6 BRED     "\033[1;33m    /   \\    "
#define COL7 BRED     "\033[1;33m   /     \\   " //info ends on column 7
#define COL8 BRED     ""


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// Probably don't change stuff below here


#define RESET "\033[0m"


#ifdef OVERRIDECOLOUR


		/* BOLD */
	#define BBLACK CUSTOMCOLOUR
	#define BRED CUSTOMCOLOUR
	#define BGREEN CUSTOMCOLOUR
	#define BYELLOW CUSTOMCOLOUR
	#define BBLUE CUSTOMCOLOUR
	#define BMAGENTA CUSTOMCOLOUR
	#define BCYAN CUSTOMCOLOUR
	#define BWHITE CUSTOMCOLOUR
		/* NORMAL */
	#define BLACK "\033[0;30m"
	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define YELLOW "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define MAGENTA "\033[0;35m"
	#define CYAN "\033[0;36m"
	#define WHITE "\033[0;37m"

#else

		/* BOLD */
	#define BBLACK "\033[1;30m"
	#define BRED "\033[1;31m"
	#define BGREEN "\033[1;32m"
	#define BYELLOW "\033[1;33m"
	#define BBLUE "\033[1;34m"
	#define BMAGENTA "\033[1;35m"
	#define BCYAN "\033[1;36m"
	#define BWHITE "\033[1;37m"
		/* NORMAL */
	#define BLACK "\033[0;30m"
	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define YELLOW "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define MAGENTA "\033[0;35m"
	#define CYAN "\033[0;36m"
	#define WHITE "\033[0;37m"
#endif
//
//I wouldn't suggest trying to change this, theres no need to and it'll break things
struct distinfo {
	char * dcol1;
	char * dcol2;
	char * dcol3;
	char * dcol4;
	char * dcol5;
	char * dcol6;
	char * dcol7;
	char * dcol8;
	char * getpkg;
};

