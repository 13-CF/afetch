#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <time.h>

#include "config.h"

long long uptimealt(){
	FILE *uptimefile;
	char * uptimebuf = malloc(75);
	long long uptime;
	if (((uptimefile=fopen("/proc/uptime", "r")) == NULL) || uptimebuf==NULL) { fclose(uptimefile); return 1; }
	fgets(uptimebuf, 75,  uptimefile);
	fclose(uptimefile);
	uptime = strtol(uptimebuf, NULL, 10);
	free(uptimebuf);
	return uptime;
}



char * os()
{

	char *os = malloc(100);
#ifdef __linux__
	char *releasefileContents = malloc(100);
	
	if (releasefileContents == NULL || os == NULL) {
		perror("os(): ");
		exit(1);
	}

	FILE *f = fopen("/etc/os-release", "r");
	if (f == NULL) { f = fopen("/var/run/os-release", "r"); }
	//if neither of these files exist, it could be a basic FreeBSD install
	if (f == NULL) {
		strncpy(os, "unknown", 8);
		free(releasefileContents);
		return os;
	}

	fgets(releasefileContents, 100, f);
	fclose(f);

	snprintf(releasefileContents, 100, "%.*s", 50, releasefileContents + 5); //Delete the NAME= section
	
	strncpy(os, strtok(releasefileContents, "\""), 100);
	free(releasefileContents);

	if (strncmp(os, "Gentoo\n", 7) == 0) {
		os[6] = '\0';
	} else if (strncmp(os, "Y_NAME=", 7) == 0) {
		//PRETTY_NAME is on the first line on debian
		strncpy(os, "Debian", 7);
	} else if (strncmp(os, "Slackware\n", 10) == 0) {
		os[9] = '\0';
	} else if (strncmp(os, "NixOS\n", 6) == 0) {
		os[5] = '\0'; }
	return os;
#else
	struct utsname posixos;
	uname(&posixos);
	strcpy(os, posixos.sysname);
	return os;
#endif
}

char * lowercase(char * str) {
	if (LOWERCASE == 0) {
		int len=strlen(str);
		for (int i=0; i<len; i++) {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				str[i] += (32);}
		}
		return str;
	}
	return str;
}

void blockdraw() {
	char * colours[] = {"\033[1;30m", "\033[1;31m","\033[1;32m","\033[1;33m","\033[1;34m","\033[1;35m","\033[1;36m","\033[1;37m"};

	printf("  ");
	for (int i=0;i<8;i++){
		printf("%s", colours[i]);
		printf("%s", BLOCKCHAR);	
	}
	printf("\n\n");
	printf("\033[0m");
}



void replace(char * source, char * sub, char * with) { //stolen off of a youtube video, thank you stranger
	char * substring_source = strstr(source, sub);
	if (substring_source == NULL) {
		return;
	}

	memmove(substring_source + strlen(with),
		substring_source + strlen(sub),
		strlen(substring_source) - strlen(sub) +1 );
	memcpy(substring_source, with, strlen(with));
}

struct distinfo asciiart() {
#ifdef __linux__
	char* dist = os();
#else
	struct utsname ui;
	uname(&ui);
	char* dist = malloc(50);
	strcpy(dist, ui.sysname);
#endif
	struct distinfo info;
	while (1) {
#ifdef __linux__
/* Linux distros go below here. Make sure they are not before the '#else' */
	if (strncmp(dist, "void", 4) == 0) {
		info.dcol1 =    BGREEN"     _______\n";
		info.dcol2 =    BGREEN"  _ \\______ - ";
		info.dcol3 =	BGREEN" | \\  ___  \\ |";
		info.dcol4 = 	BGREEN" | | /   \\ | |";
		info.dcol5 =	BGREEN" | | \\___/ | |";
		info.dcol6 =	BGREEN" | \\______ \\_|";
		info.dcol7  =	BGREEN "  -_______\\   ";
		info.dcol8  =   "";
		info.getpkg = "xbps-query -l | wc -l";
		break;
	} else if (strncmp(dist, "Gentoo", 6) == 0) {
		info.dcol1=BMAGENTA"   _-----_ \n";
      		info.dcol2=BMAGENTA"  (       \\  ";
      		info.dcol3=BMAGENTA"  \\    0   \\ ";
      		info.dcol4=BMAGENTA"   \\        )";
    		info.dcol5=BMAGENTA"   /      _/ ";
   		info.dcol6=BMAGENTA"  (     _-   ";
   		info.dcol7=BMAGENTA"  \\____-     ";
   		info.dcol8=BWHITE"\n";
		info.getpkg = "ls -d /var/db/pkg/*/* | wc -l";
		break;
	} else if (strncmp(dist, "Arch Linux", 10)==0) {
       		info.dcol1=BCYAN"";
      		info.dcol2=BCYAN"      /\\      ";
      		info.dcol3=BCYAN"     /  \\     ";
      		info.dcol4=BCYAN"    /\\   \\    ";
    		info.dcol5=BCYAN"   /      \\   ";
   		info.dcol6=BCYAN"  /   ,,   \\  ";
   		info.dcol7=BCYAN" /   |  |  -\\ ";
   		info.dcol8=BCYAN"/_-''    ''-_\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Manjaro Linux", 13)==0) {
   		info.dcol1=BGREEN" ________  __ \n";
       		info.dcol2=BGREEN"|       | |  |";
      		info.dcol3=BGREEN"|   ____| |  |";
      		info.dcol4=BGREEN"|  |  __  |  |";
      		info.dcol5=BGREEN"|  | |  | |  |";
    		info.dcol6=BGREEN"|  | |  | |  |";
   		info.dcol7=BGREEN"|  | |  | |  |";
   		info.dcol8=BGREEN"|__| |__| |__|\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Artix Linux", 11)==0) {
       		info.dcol1=BCYAN"";
      		info.dcol2=BCYAN"      /\\      ";
      		info.dcol3=BCYAN"     /  \\     ";
      		info.dcol4=BCYAN"    /`'.,\\    ";
    		info.dcol5=BCYAN"   /     ',   ";
   		info.dcol6=BCYAN"  /      ,`\\  ";
   		info.dcol7=BCYAN" /   ,.'`.  \\ ";
   		info.dcol8=BCYAN"/.,'`     `'.\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Fedora", 6)==0) {
       		info.dcol1=BWHITE"      _____\n"BBLUE;
      		info.dcol2=BWHITE"     /   __)"BBLUE"\\ ";
      		info.dcol3=BWHITE"     |  /  "BBLUE"\\ \\";
      		info.dcol4=BWHITE"  ___|  |"BBLUE"__/ /";
    		info.dcol5=BBLUE" / "BWHITE"(_    _)"BBLUE"_/ ";
   		info.dcol6=BBLUE"/ /  "BWHITE"|  |     "BBLUE;
   		info.dcol7=BBLUE"\\ \\"BWHITE"__/  |     "BBLUE;
   		info.dcol8=BBLUE" \\"BWHITE"(_____/"BBLUE;
		info.getpkg="rpm -qa | wc -l";	//this command is really slow, should probably find a faster way to find the packages
		break;
	} else if (strncmp(dist, "Debian", 6)==0) {
       		info.dcol1=BRED"  _____\n";
      		info.dcol2=BRED" /  __ \\ ";
      		info.dcol3=BRED"|  /    |";
      		info.dcol4=BRED"|  \\___- ";
    		info.dcol5=BRED"-_       ";
   		info.dcol6=BRED"  --_    ";
   		info.dcol7=BRED"         ";
   		info.dcol8=BRED"";
		info.getpkg="dpkg -l | tail -n+6 | wc -l";
		break;
	} else if (strncmp(dist, "Ubuntu", 6)==0) {
   		info.dcol1=BRED"";
       		info.dcol2=BRED"         _  ";
      		info.dcol3=BRED"     ---(_) ";
      		info.dcol4=BRED" _/  ---  \\ ";
      		info.dcol5=BRED"(_) |   |   ";
    		info.dcol6=BRED"  \\  --- _/ ";
   		info.dcol7=BRED"     ---(_) ";
   		info.dcol8=BRED"";
		info.getpkg="dpkg -l | tail -n+6 | wc -l";
		break;
	} else if (strncmp(dist, "Alpine Linux", 12)==0) {
   		info.dcol1=BBLUE"\n";
       		info.dcol2=BBLUE"    /\\ /\\    ";
      		info.dcol3=BBLUE"   /  \\  \\   ";
      		info.dcol4=BBLUE"  /    \\  \\  ";
      		info.dcol5=BBLUE" /      \\  \\ ";
    		info.dcol6=BBLUE"/        \\  \\";
   		info.dcol7=BBLUE"          \\  ";
   		info.dcol8=BBLUE"";
		info.getpkg="apk info | wc -l";
		break;
	} else if (strncmp(dist, "Slackware", 10) == 0) {
		info.dcol1=BBLUE"   ________\n";
		info.dcol2=BBLUE"  /  ______| ";
		info.dcol3=BBLUE"  | |______  ";
		info.dcol4=BBLUE"  \\______  \\ ";
		info.dcol5=BBLUE"   ______| | ";
		info.dcol6=BBLUE"| |________/ ";
		info.dcol7=BBLUE"|____________";
		info.dcol8=BBLUE"";
		info.getpkg="ls /var/log/packages | wc -l";
		break;
	} else if (strncmp(dist, "openSUSE Leap", 10) == 0 || strncmp(dist, "openSUSE Tumbleweed", 19) == 0) {
		info.dcol1=BGREEN"  _______\n";
		info.dcol2=BGREEN"__|   __ \\ ";
		info.dcol3=BGREEN"     / .\\ \\";
		info.dcol4=BGREEN"     \\__/ |";
		info.dcol5=BGREEN"   _______|";
		info.dcol6=BGREEN"   \\_______";
		info.dcol7=BGREEN"__________/";
		info.dcol8=BGREEN"";
		info.getpkg="rpm -qa | wc -l";
		break;
	} else if (strncmp(dist, "Pop!_OS", 7) == 0) {
		info.dcol1=BCYAN"______\n";
		info.dcol2=BCYAN"\\   _ \\        __";
		info.dcol3=BCYAN" \\ \\ \\ \\      / /";
		info.dcol4=BCYAN"  \\ \\_\\ \\    / / ";
		info.dcol5=BCYAN"   \\  ___\\  /_/  ";
		info.dcol6=BCYAN"    \\ \\    _     ";
		info.dcol7=BCYAN"   __\\_\\__(_)_   ";
		info.dcol8=BCYAN"  (___________)";
		info.getpkg="dpkg -l | tail -n+6 | wc -l"; 
		break;
	} else if (strncmp(dist, "NixOS", 5) == 0) {
		info.dcol1=BMAGENTA"            \n";
		info.dcol2=BMAGENTA"  \\\\  \\\\ //     ";
		info.dcol3=BMAGENTA" ==\\\\__\\\\/ //   ";
		info.dcol4=BMAGENTA"   //   \\\\//    ";
		info.dcol5=BMAGENTA"==//     //==   ";
		info.dcol6=BMAGENTA" //\\\\___//      ";
		info.dcol7=BMAGENTA"// /\\\\  \\\\==    ";
		info.dcol8=BMAGENTA"  // \\\\  \\\\     ";
		info.getpkg="nix-store -q --requisites /run/current-system/sw | wc -l";
		break; }
#else
	/* All operating systems that aren't Linux distros go under here. */
	if (strncmp(dist, "OpenBSD", 7) == 0) {
		info.dcol1 =    BYELLOW"      _____    \n";
		info.dcol2 =	BYELLOW"    \\-     -/  ";
		info.dcol3 = 	BYELLOW" \\_/         \\ ";
		info.dcol4 =	BYELLOW" |        "BWHITE"O O"BYELLOW" |";
		info.dcol5 =	BYELLOW" |_  <   )  3 )";
		info.dcol6  =	BYELLOW" / \\         / ";
		info.dcol7  =   BYELLOW"    /-_____-\\  ";
		info.dcol8 =    BYELLOW"";
		info.getpkg = "pkg_info | wc -l | tr -d ' '";
		break;
	} else if (strncmp(dist, "FreeBSD", 7)==0) {
   		info.dcol1=BRED"";
       		info.dcol2=BRED"/\\,-'''''-,/\\";
      		info.dcol3=BRED"\\_)       (_/";
      		info.dcol4=BRED"|           |";
      		info.dcol5=BRED"|           |";
    		info.dcol6=BRED" ;         ; ";
   		info.dcol7=BRED"  '-_____-'  ";
   		info.dcol8=BRED"";
		info.getpkg="pkg info | wc -l | tr -d ' '";
		break;
	} else if (strncmp(dist, "NetBSD", 6)==0) {
   		info.dcol1=BWHITE"\\\\"BMAGENTA"\\`-______,----__\n";
       		info.dcol2=BWHITE" \\\\"BMAGENTA"        __,---\\`_";
      		info.dcol3=BWHITE"  \\\\"BMAGENTA"       \\`.____  ";
      		info.dcol4=BWHITE"   \\\\"BMAGENTA"-______,----\\`-";
      		info.dcol5=BWHITE"    \\\\"BMAGENTA"              ";
    		info.dcol6=BWHITE"     \\\\"BMAGENTA"             ";
   		info.dcol7=BWHITE"      \\\\"BMAGENTA"            ";
   		info.dcol8=BWHITE"";
		info.getpkg="pkg_info | wc -l | tr -d ' '";
		break;
	} else if (strncmp(dist, "DragonFly", 9)==0) {
       		info.dcol1=BCYAN"   ,"BBLUE"_"BCYAN",   \n";
      		info.dcol2=BCYAN"('-_"BBLUE"|"BCYAN"_-')";
      		info.dcol3=BCYAN" >--"BBLUE"|"BCYAN"--< ";
      		info.dcol4=BCYAN"(_-'"BBLUE"|"BCYAN"'-_)";
    		info.dcol5=BCYAN"    "BBLUE"|"BCYAN"    ";
   		info.dcol6=BCYAN"    "BBLUE"|"BCYAN"    ";
   		info.dcol7=BCYAN"    "BBLUE"|"BCYAN"    ";
   		info.dcol8=BCYAN"";
		info.getpkg="pkg info | wc -l | tr -d ' '";
		break; }
#endif
	 else {
       		info.dcol1=BWHITE"     ___   \n";
      		info.dcol2=BWHITE" ___/   \\___ ";
      		info.dcol3=BWHITE"/   '---'   \\";
      		info.dcol4=BWHITE"'--_______--'";
    		info.dcol5=BWHITE"     / \\     ";
   		info.dcol6=BWHITE"    /   \\    ";
   		info.dcol7=BWHITE"   /     \\   ";
   		info.dcol8=BWHITE"";
		info.getpkg = "echo ???";
	 	break; }}
	if (CUSTOMART == 0) {
		info.dcol1 = COL1;
		info.dcol2 = COL2;
		info.dcol3 = COL3;
		info.dcol4 = COL4;
		info.dcol5 = COL5;
		info.dcol6 = COL6;
		info.dcol7 = COL7;
		info.dcol8 = COL8; }
	if (CUSTOMCMD == 0) {
		info.getpkg = PKGCMD; }
	free(dist);
	return info;
}

char * shell() {
	if (SHELLPATH == 0) {
		return getenv("SHELL"); }


	char * shell = getenv("SHELL");

	replace(shell, "/bin/", "\0");
	replace(shell, "/usr", "\0");
	replace(shell, "/local", "\0");
	return shell; 
}

int main(){
	struct utsname ui; 
	uname(&ui);
	struct timespec si;

#ifdef CLOCK_BOOTTIME
	clock_gettime(CLOCK_BOOTTIME, &si);
#elif CLOCK_UPTIME
	clock_gettime(CLOCK_UPTIME, &si);
#else
	long long uptime = uptimealt(); //  uptime/3600 for minutes, (uptime/60)-(uptime/3600*60) for hours
#endif
	struct distinfo ascii = asciiart();
	char *os_string = os();
	FILE *pkgs;
	char i;
	
	printf("%s", ascii.dcol1);
	printf("%s %s %s%s\n",ascii.dcol2,USERTEXT, TEXTCOLOUR, lowercase(getenv("USER")));
	printf("%s %s %s%s\n",ascii.dcol3,DISROTEXT, TEXTCOLOUR, lowercase(os_string));
	printf("%s %s %s%s\n",ascii.dcol4,KERNELTEXT, TEXTCOLOUR, ui.release);
#if defined(CLOCK_BOOTTIME) || defined(CLOCK_UPTIME)
	printf("%s %s %s%ldh %ldm\n", ascii.dcol5,lowercase(UPTIMETEXT), TEXTCOLOUR, si.tv_sec / 3600, (si.tv_sec / 60) - (si.tv_sec / 3600 * 60));
#else
	printf("%s %s %s%ldh %ldm\n", ascii.dcol5,lowercase(UPTIMETEXT), TEXTCOLOUR, uptime / 3600, (uptime / 60) - (uptime / 3600 * 60));
#endif
	printf("%s %s %s%s\n",ascii.dcol6, SHELLTEXT,TEXTCOLOUR, shell());
	printf("%s %s %s",ascii.dcol7, PACKAGETEXT, TEXTCOLOUR);

	pkgs = popen(ascii.getpkg, "r");
	if (pkgs == NULL) {
		puts("\0"); }
	while ( (i=fgetc(pkgs)) != EOF) {
		putchar(i); }

	pclose(pkgs);
	printf("%s", ascii.dcol8);
	printf("\n");
	if (BLOCKS == 0) {
		blockdraw();
	} 
	printf("%s", RESET); // Reset terminal's colors
	free(os_string);
	return 0;
}
