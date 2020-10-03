// used to change the text displayed, text boxes should all align


#define USERTEXT    "       USER"
#define DISROTEXT   "     DISTRO"
#define KERNELTEXT  "     KERNEL" 
#define UPTIMETEXT  "     UPTIME"
#define SHELLTEXT   "      SHELL"
#define PACKAGETEXT "       PKGS"


// For icons to display correctly, a nerd font may be required 
/*
#define USERTEXT    "     "
#define DISROTEXT   "     "
#define KERNELTEXT  "     " 
#define UPTIMETEXT  "     "
#define SHELLTEXT   "     "
#define PACKAGETEXT "     " */


	/* BRIGHT */
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


//probably don't change this (it'll break shit)
typedef struct distinfo {
	char * dcol1;
	char * dcol2;
	char * dcol3;
	char * dcol4;
	char * dcol5;
	char * dcol6;
	char * dcol7;
	char * dcol8;
	char * getpkg;
} Dist;
