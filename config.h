//LOWERCASE FUNCTION IS EXPERIMENTAL (BROKEN) - COULD RESULT IN SEGFAULTS
#define LOWERCASE 1 // 0 for true, 1 for false. True should display all strings as lower case characters, but it might not work properly

//---------------------------------------------------------------------------------------------

#define SHELLPATH 1 //if set to 0, the full file path for the users shell will display

//---------------------------------------------------------------------------------------------

/* If you can see the icons, your font supports them */
#define USERTEXT    "       USER"//
#define DISROTEXT   "     DISTRO"//
#define KERNELTEXT  "     KERNEL"// 
#define UPTIMETEXT  "     UPTIME"//
#define SHELLTEXT   "      SHELL"//
#define PACKAGETEXT "       PKGS"//

//---------------------------------------------------------------------------------------------

//IF YOU WANT TO USE A CUSTOM COLOUR, UNCOMMENT THE LINE BELOW
//#define OVERRIDECOLOUR 

//This option only matters if the one above is enabled, it must be one of the colours listed in the 'COLOURS' file
#define CUSTOMCOLOUR "\033[1;36m"

//---------------------------------------------------------------------------------------------

#define CUSTOMART 1 //set to 1 to disable custom art

// custom ascii art can be edited by editing the variabled below
	     //COLOUR  //ASCII ART LINES
#define COL1 BRED     "      ___   \n"
#define COL2 BRED     "  ___/   \\___ " //info starts on column 2
#define COL3 BRED     " /   '---'   \\"
#define COL4 BRED     " '--_______--'"
#define COL5 BRED     "      / \\     "
#define COL6 BRED     "     /   \\    "
#define COL7 BRED     "     /   \\    " //info ends on column 7
#define COL8 BRED     ""


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// Probably don't change stuff below here




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
