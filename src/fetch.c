
#ifndef __APPLE__
   #define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <time.h>

#ifdef __APPLE__
   #include <sys/sysctl.h>
#endif

#include "config.h"

char *pipeRead(const char *cmd){
	FILE *pipeFile = popen(cmd, "r");
	if (pipeFile == NULL) return NULL;
	char *outPtr = malloc(50);
	fscanf(pipeFile, "%[^\n]s", outPtr);
	pclose(pipeFile);
	return outPtr;
}

long long uptimealt(){
	/* function to read from /proc/uptime to get the uptime.
	   It is only called when CLOCK_UPTIME or CLOCK_BOOTTIME
	   aren't defined and the OS isn't macOS. */
	FILE *uptimefile;
	char * uptimebuf = malloc(75);
	long long uptime;
	if (((uptimefile=fopen("/proc/uptime", "r")) == NULL) || uptimebuf==NULL) { fclose(uptimefile); return 0; }
	fgets(uptimebuf, 75,  uptimefile);
	fclose(uptimefile);
	uptime = strtol(uptimebuf, NULL, 10);
	free(uptimebuf);
	return uptime;
}

char * os()
{
#ifdef __linux__
	char *osContents = malloc(512);
	char *newContents = malloc(512);
	int line = 0;
	FILE *f = fopen("/etc/os-release", "rt");
	if (f == NULL || osContents == NULL) return "Linux";
	// look through each line of /etc/os-release until we're on the NAME= line
	while (fgets(osContents, 512, f)) {
		snprintf(newContents, 512, "%.*s", 511, osContents+4);
		if (strncmp(newContents, "=", 1) == 0) break;
		line++; }
	fclose(f);
	free(osContents);

	if (strncmp(newContents, "=", 1) == 0) {
		int len = strlen(newContents);
		for (int i = 0; i<len; i++){
			if (newContents[i] == '\"' || newContents[i] == '=') {
				for (int ii = 0; ii<len; ii++) newContents[ii] = newContents[ii+1];
				newContents[strlen(newContents)-1] = '\0';
			}
		 }
	}
	return newContents;
#elif __APPLE__
	char *macVersion = malloc(50);
	strcpy(macVersion, "macOS ");

	char *productVersion = pipeRead("sw_vers -productVersion");

	strcat(macVersion, productVersion);
	free(productVersion);

	return macVersion;
#else
	/* If you aren't runnig a Linux distro or macOS then this is run.
	 * Output should be the same as output from uname -s. */
	char *os = malloc(100);
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
	printf("    ");
	for (int i = 30; i<38; i++){
		printf("\033[0;%dm%s", i, BLOCKCHAR);
	}
	printf("\n    ");
	for (int i = 30; i<38; i++){
		printf("\033[1;%dm%s", i, BLOCKCHAR);
	}

	printf("\n\n");
	printf("\033[0m");
}

/* Logos created by neofetch and ufetch developers */
struct distinfo asciiart() {
	char* dist = os();
	struct distinfo info;
	while (1) {
#ifdef __linux__
/* Linux distros go below here. Make sure they are not before the '#else' */
	if (strncmp(dist, "Alpine Linux", 12) == 0) {
		info.dcol1 = BBLUE"\n";
		info.dcol2 = BBLUE"    /\\ /\\    ";
		info.dcol3 = BBLUE"   /  \\  \\   ";
		info.dcol4 = BBLUE"  /    \\  \\  ";
		info.dcol5 = BBLUE" /      \\  \\ ";
		info.dcol6 = BBLUE"/        \\  \\";
		info.dcol7 = BBLUE"          \\  ";
		info.dcol8 = BBLUE"";
		info.getpkg = "apk info | wc -l";
		break;
	} else if (strncmp(dist, "Arch Linux", 10) == 0) {
		info.dcol1 = BCYAN"";
		info.dcol2 = BCYAN"      /\\      ";
		info.dcol3 = BCYAN"     /  \\     ";
		info.dcol4 = BCYAN"    /\\   \\    ";
		info.dcol5 = BCYAN"   /      \\   ";
		info.dcol6 = BCYAN"  /   ,,   \\  ";
		info.dcol7 = BCYAN" /   |  |  -\\ ";
		info.dcol8 = BCYAN"/_-''    ''-_\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Arch bang Linux", 15) == 0) {
		info.dcol1 = BCYAN"          ____\n";
		info.dcol2 = BCYAN"      /\\ /   /";
		info.dcol3 = BCYAN"     /  /   / ";
		info.dcol4 = BCYAN"    /   / /   ";
		info.dcol5 = BCYAN"   /   /_/\\   ";
		info.dcol6 = BCYAN"  /   __   \\  ";
		info.dcol7 = BCYAN" /   /_/\\   \\ ";
		info.dcol8 = BCYAN"/_-''    ''-_\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "ArcoLinux", 9) == 0) {
		info.dcol1 = BBLUE"";
		info.dcol2 = BBLUE"      /\\      ";
		info.dcol3 = BBLUE"     /  \\     ";
		info.dcol4 = BBLUE"    / /\\ \\    ";
		info.dcol5 = BBLUE"   / /  \\ \\   ";
		info.dcol6 = BBLUE"  / /    \\ \\  ";
		info.dcol7 = BBLUE" / / _____\\ \\ ";
		info.dcol8 = BBLUE"/_/  `----.\\_\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Artix Linux", 11) == 0) {
		info.dcol1 = BCYAN"";
		info.dcol2 = BCYAN"      /\\      ";
		info.dcol3 = BCYAN"     /  \\     ";
		info.dcol4 = BCYAN"    /`'.,\\    ";
		info.dcol5 = BCYAN"   /     ',   ";
		info.dcol6 = BCYAN"  /      ,`\\  ";
		info.dcol7 = BCYAN" /   ,.'`.  \\ ";
		info.dcol8 = BCYAN"/.,'`     `'.\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Debian GNU/Linux", 16) == 0) {
		info.dcol1 = BRED"  _____\n";
		info.dcol2 = BRED" /  __ \\ ";
		info.dcol3 = BRED"|  /    |";
		info.dcol4 = BRED"|  \\___- ";
		info.dcol5 = BRED"-_       ";
		info.dcol6 = BRED"  --_    ";
		info.dcol7 = BRED"         ";
		info.dcol8 = BRED"";
		info.getpkg = "dpkg -l | tail -n+6 | wc -l";
		break;
	} else if (strncmp(dist, "elementary OS", 12) == 0) {
		info.dcol1 = BCYAN"";
		info.dcol2 = BCYAN"  _______  ";
		info.dcol3 = BCYAN" / ____  \\ ";
		info.dcol4 = BCYAN"/  |  /  /\\";
		info.dcol5 = BCYAN"|__\\ /  / |";
		info.dcol6 = BCYAN"\\   /__/  /";
		info.dcol7 = BCYAN" \\_______/ ";
		info.dcol8 = BCYAN"";
		info.getpkg = "dpkg -l | tail -n+6 | wc -l";
		break;
	} else if (strncmp(dist, "EndeavourOS", 11) == 0) {
		info.dcol1 = BCYAN"";
		info.dcol2 = BRED"      /"BBLUE"\\     "BCYAN;
		info.dcol3 = BRED"    /"BBLUE"/  \\"BCYAN"\\   "BCYAN;
		info.dcol4 = BRED"   /"BBLUE"/    \\ "BCYAN"\\ "BCYAN;
		info.dcol5 = BRED" / "BBLUE"/     _) "BCYAN")"BCYAN;
		info.dcol6 = BRED"/_"BBLUE"/___-- "BCYAN"__- "BCYAN;
		info.dcol7 = BCYAN" /____--     "BCYAN;
		info.dcol8 = BCYAN"";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Fedora", 6) == 0) {
		info.dcol1 = BWHITE"      _____\n"BBLUE;
		info.dcol2 = BWHITE"     /   __)"BBLUE"\\ ";
		info.dcol3 = BWHITE"     |  /  "BBLUE"\\ \\";
		info.dcol4 = BWHITE"  ___|  |"BBLUE"__/ /";
		info.dcol5 = BBLUE" / "BWHITE"(_    _)"BBLUE"_/ ";
		info.dcol6 = BBLUE"/ /  "BWHITE"|  |     "BBLUE;
		info.dcol7 = BBLUE"\\ \\"BWHITE"__/  |     "BBLUE;
		info.dcol8 = BBLUE" \\"BWHITE"(_____/"BBLUE;
		info.getpkg = "[[ $(which sqlite3 2>/dev/null) && $? -ne 1 ]] && (sqlite3 /var/lib/rpm/rpmdb.sqlite \"select * from Name\"|wc -l) || rpm -qa | wc -l";
		break;
	} else if (strncmp(dist, "Gentoo", 6) == 0) {
		info.dcol1 = BMAGENTA"   _-----_ \n";
		info.dcol2 = BMAGENTA"  (       \\  ";
		info.dcol3 = BMAGENTA"  \\    0   \\ ";
		info.dcol4 = BMAGENTA"   \\        )";
		info.dcol5 = BMAGENTA"   /      _/ ";
		info.dcol6 = BMAGENTA"  (     _-   ";
		info.dcol7 = BMAGENTA"  \\____-     ";
		info.dcol8 = BWHITE"\n";
		info.getpkg = "qlist -IRv | wc -l";
		break;
	} else if (strncmp(dist, "KDE neon", 8) == 0) {
		info.dcol1 = BGREEN"";
		info.dcol2 = BGREEN"            ";
		info.dcol3 = BGREEN"     --- _  ";
		info.dcol4 = BGREEN"  /  ---  \\ ";
		info.dcol5 = BGREEN" |  |   |  |";
		info.dcol6 = BGREEN"  \\  --- _/ ";
		info.dcol7 = BGREEN"     ---    ";
		info.dcol8 = BGREEN"";
		info.getpkg = "dpkg -l | tail -n+6 | wc -l";
		break;
	} else if (strncmp(dist, "Manjaro", 7) == 0) {
		info.dcol1 = BGREEN" ________  __ \n";
		info.dcol2 = BGREEN"|       | |  |";
		info.dcol3 = BGREEN"|   ____| |  |";
		info.dcol4 = BGREEN"|  |  __  |  |";
		info.dcol5 = BGREEN"|  | |  | |  |";
		info.dcol6 = BGREEN"|  | |  | |  |";
		info.dcol7 = BGREEN"|  | |  | |  |";
		info.dcol8 = BGREEN"|__| |__| |__|\n";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "NixOS", 5) == 0) {
		info.dcol1 = BMAGENTA"            \n";
		info.dcol2 = BMAGENTA"  \\\\  \\\\ //     ";
		info.dcol3 = BMAGENTA" ==\\\\__\\\\/ //   ";
		info.dcol4 = BMAGENTA"   //   \\\\//    ";
		info.dcol5 = BMAGENTA"==//     //==   ";
		info.dcol6 = BMAGENTA" //\\\\___//      ";
		info.dcol7 = BMAGENTA"// /\\\\  \\\\==    ";
		info.dcol8 = BMAGENTA"  // \\\\  \\\\     ";
		info.getpkg = "nix-store -q --requisites /run/current-system/sw | wc -l";
		break;
	} else if (strncmp(dist, "openSUSE Leap", 10) == 0 || strncmp(dist, "openSUSE Tumbleweed", 19) == 0) {
		info.dcol1 = BGREEN"  _______\n";
		info.dcol2 = BGREEN"__|   __ \\ ";
		info.dcol3 = BGREEN"     / .\\ \\";
		info.dcol4 = BGREEN"     \\__/ |";
		info.dcol5 = BGREEN"   _______|";
		info.dcol6 = BGREEN"   \\_______";
		info.dcol7 = BGREEN"__________/";
		info.dcol8 = BGREEN"";
		info.getpkg = "rpm -qa | wc -l";
		break;
	} else if (strncmp(dist, "Parabola", 8) == 0) {
		info.dcol1 = BMAGENTA"";
		info.dcol2 = BMAGENTA"  __ __ __  _  ";
		info.dcol3 = BMAGENTA".`_//_//_/ / `.";
		info.dcol4 = BMAGENTA"          /  .`";
		info.dcol5 = BMAGENTA"         / .`  ";
		info.dcol6 = BMAGENTA"        /.`    ";
		info.dcol7 = BMAGENTA"       /`      ";
		info.dcol8 = BMAGENTA"";
		info.getpkg = "pacman -Qq | wc -l";
		break;
	} else if (strncmp(dist, "Pop!_OS", 7) == 0) {
		info.dcol1 = BCYAN"______\n";
		info.dcol2 = BCYAN"\\   _ \\        __";
		info.dcol3 = BCYAN" \\ \\ \\ \\      / /";
		info.dcol4 = BCYAN"  \\ \\_\\ \\    / / ";
		info.dcol5 = BCYAN"   \\  ___\\  /_/  ";
		info.dcol6 = BCYAN"    \\ \\    _     ";
		info.dcol7 = BCYAN"   __\\_\\__(_)_   ";
		info.dcol8 = BCYAN"  (___________)";
		info.getpkg = "dpkg -l | tail -n+6 | wc -l";
		break;
	} else if (strncmp(dist, "Slackware", 10) == 0) {
		info.dcol1 = BBLUE"   ________\n";
		info.dcol2 = BBLUE"  /  ______| ";
		info.dcol3 = BBLUE"  | |______  ";
		info.dcol4 = BBLUE"  \\______  \\ ";
		info.dcol5 = BBLUE"   ______| | ";
		info.dcol6 = BBLUE"| |________/ ";
		info.dcol7 = BBLUE"|____________";
		info.dcol8 = BBLUE"";
		info.getpkg = "ls /var/log/packages | wc -l";
		break;
	} else if (strncmp(dist, "Solus", 5) == 0) {
		info.dcol1 = BMAGENTA"    __________\n";
		info.dcol2 = BMAGENTA"   /          \\   ";
		info.dcol3 = BMAGENTA"  /   /\\ \\     \\  ";
		info.dcol4 = BMAGENTA" /   /  \\ \\     \\ ";
		info.dcol5 = BMAGENTA"|   /    \\ \\     |";
		info.dcol6 = BMAGENTA" \\--------------/ ";
		info.dcol7 = BMAGENTA"  \\------------/  ";
		info.dcol8 = BMAGENTA"   \\----------/";
		info.getpkg = "ls /var/lib/eopkg/package/ | wc -l";
		break;
	} else if (strncmp(dist, "Ubuntu", 6) == 0) {
		info.dcol1 = BRED"";
		info.dcol2 = BRED"         _  ";
		info.dcol3 = BRED"     ---(_) ";
		info.dcol4 = BRED" _/  ---  \\ ";
		info.dcol5 = BRED"(_) |   |   ";
		info.dcol6 = BRED"  \\  --- _/ ";
		info.dcol7 = BRED"     ---(_) ";
		info.dcol8 = BRED"";
		info.getpkg = "dpkg -l | tail -n+6 | wc -l";
		break;
	} else if (strncmp(dist, "void", 4) == 0) {
		info.dcol1 = BGREEN"     _______\n";
		info.dcol2 = BGREEN"  _ \\______ - ";
		info.dcol3 = BGREEN" | \\  ___  \\ |";
		info.dcol4 = BGREEN" | | /   \\ | |";
		info.dcol5 = BGREEN" | | \\___/ | |";
		info.dcol6 = BGREEN" | \\______ \\_|";
		info.dcol7 = BGREEN "  -_______\\   ";
		info.dcol8 = "";
		info.getpkg = "xbps-query -l | wc -l";
		break;

	}
#else
	/* All operating systems that aren't Linux distros go under here. */
	if (strncmp(dist, "DragonFly", 9) == 0) {
		info.dcol1 = BCYAN"   ,"BBLUE"_"BCYAN",   \n";
		info.dcol2 = BCYAN"('-_"BBLUE"|"BCYAN"_-')";
		info.dcol3 = BCYAN" >--"BBLUE"|"BCYAN"--< ";
		info.dcol4 = BCYAN"(_-'"BBLUE"|"BCYAN"'-_)";
		info.dcol5 = BCYAN"    "BBLUE"|"BCYAN"    ";
		info.dcol6 = BCYAN"    "BBLUE"|"BCYAN"    ";
		info.dcol7 = BCYAN"    "BBLUE"|"BCYAN"    ";
		info.dcol8 = BCYAN"";
		info.getpkg = "pkg info | wc -l | tr -d ' '";
		break;
	} else if (strncmp(dist, "FreeBSD", 7) == 0) {
		info.dcol1 = BRED"";
		info.dcol2 = BRED"/\\,-'''''-,/\\";
		info.dcol3 = BRED"\\_)       (_/";
		info.dcol4 = BRED"|           |";
		info.dcol5 = BRED"|           |";
		info.dcol6 = BRED" ;         ; ";
		info.dcol7 = BRED"  '-_____-'  ";
		info.dcol8 = BRED"";
		info.getpkg = "pkg info | wc -l | tr -d ' '";
		break;
	} else if (strncmp(dist, "NetBSD", 6) == 0) {
		info.dcol1 = BWHITE"\\\\"BYELLOW"\\`-______,----__\n";
		info.dcol2 = BWHITE" \\\\"BYELLOW"        __,---\\`_";
		info.dcol3 = BWHITE"  \\\\"BYELLOW"       \\`.____  ";
		info.dcol4 = BWHITE"   \\\\"BYELLOW"-______,----\\`-";
		info.dcol5 = BWHITE"    \\\\"BYELLOW"              ";
		info.dcol6 = BWHITE"     \\\\"BYELLOW"             ";
		info.dcol7 = BWHITE"      \\\\"BYELLOW"            ";
		info.dcol8 = BWHITE"";
		info.getpkg = "pkg_info | wc -l | tr -d ' '";
		break;
	} else if (strncmp(dist, "OpenBSD", 7) == 0) {
		info.dcol1 = BYELLOW"      _____    \n";
		info.dcol2 = BYELLOW"    \\-     -/  ";
		info.dcol3 = BYELLOW" \\_/         \\ ";
		info.dcol4 = BYELLOW" |        "BWHITE"O O"BYELLOW" |";
		info.dcol5 = BYELLOW" |_  <   )  3 )";
		info.dcol6 = BYELLOW" / \\         / ";
		info.dcol7 = BYELLOW"    /-_____-\\  ";
		info.dcol8 = BYELLOW"";
		info.getpkg = "pkg_info | wc -l | tr -d ' '";
		break;
	}
#ifdef __APPLE__
	 else if (strncmp(dist, "macOS", 5) == 0) {
		/* ascii art author: jgs */
		info.dcol1 = ""BYELLOW;
		info.dcol2 = BGREEN   "          .:'   "BYELLOW;
		info.dcol3 = BGREEN   "      __ :'__   "BYELLOW;
		info.dcol4 = BYELLOW  "   .'`__`-'__``."BYELLOW;
		info.dcol5 = BRED     "  :__________.-'"BYELLOW;
		info.dcol6 = BRED     "  :_________:   "BYELLOW;
		info.dcol7 = BMAGENTA "   :_________`-;"BYELLOW;
		info.dcol8 = BBLUE    "    `.__.-.__.' "BYELLOW;

		char *homebrewPath = pipeRead("which brew");
		if (homebrewPath == NULL || *homebrewPath == '\0')
			info.getpkg = "echo \"Warning: only Homebrew is supported.\"";
		else
			info.getpkg = "ls /usr/local/Cellar/* | grep ':' | wc -l | xargs";
		free(homebrewPath);
		break;
	}
#endif
#endif
	else {
		info.dcol1 = BWHITE"     ___   \n";
		info.dcol2 = BWHITE" ___/   \\___ ";
		info.dcol3 = BWHITE"/   '---'   \\";
		info.dcol4 = BWHITE"'--_______--'";
		info.dcol5 = BWHITE"     / \\     ";
		info.dcol6 = BWHITE"    /   \\    ";
		info.dcol7 = BWHITE"   /     \\   ";
		info.dcol8 = BWHITE"";
		info.getpkg = "echo unsupported";
		break; }}
	if (CUSTOMART == 0) {
		info.dcol1 = COL1;
		info.dcol2 = COL2;
		info.dcol3 = COL3;
		info.dcol4 = COL4;
		info.dcol5 = COL5;
		info.dcol6 = COL6;
		info.dcol7 = COL7;
		info.dcol8 = COL8;
	}
	if (CUSTOMCMD == 0) {
		info.getpkg = PKGCMD;
	}
	free(dist);
	return info;
}

char * shell() {
	if (SHELLPATH == 0) {
		return getenv("SHELL"); }


	char * shell = getenv("SHELL");

	/* get basename of shell by looking for last '/' */
	char * slash = strrchr(shell, '/');
	if (slash) {
		shell = slash + 1;
	}

	return shell;
}

int main(){
	struct utsname ui;
	uname(&ui);
	struct timespec si;
	/* There doesn't seem to be a standard way to get the time, but
	   CLOCK_BOOTTIME or CLOCK_UPTIME are usually defined. If neither
	   are defined then the uptimealt() function reads from /proc/uptime
	   to get it. */

#ifdef CLOCK_BOOTTIME
	clock_gettime(CLOCK_BOOTTIME, &si);
#elif CLOCK_UPTIME
	clock_gettime(CLOCK_UPTIME, &si);
#elif __APPLE__
	clock_gettime(CLOCK_MONOTONIC_RAW, &si);
#else
	long long uptime = uptimealt(); //  uptime/3600 for minutes, (uptime/60)-(uptime/3600*60) for hours
#endif
	struct distinfo ascii = asciiart();
	char *os_string = os();
	printf("%s", ascii.dcol1);
	printf("%s %s %s%s\n",ascii.dcol2,USERTEXT, TEXTCOLOUR, lowercase(getenv("USER")));
	printf("%s %s %s%s\n",ascii.dcol3,DISROTEXT, TEXTCOLOUR, lowercase(os_string));
	printf("%s %s %s%s\n",ascii.dcol4,KERNELTEXT, TEXTCOLOUR, ui.release);
#if defined(CLOCK_BOOTTIME) || defined(CLOCK_UPTIME) || defined(__APPLE__)
	printf("%s %s %s%ldh %ldm\n", ascii.dcol5,lowercase(UPTIMETEXT), TEXTCOLOUR, si.tv_sec / 3600, (si.tv_sec / 60) - (si.tv_sec / 3600 * 60));
#else
	printf("%s %s %s%ldh %ldm\n", ascii.dcol5,lowercase(UPTIMETEXT), TEXTCOLOUR, uptime / 3600, (uptime / 60) - (uptime / 3600 * 60));
#endif
	printf("%s %s %s%s\n",ascii.dcol6, SHELLTEXT,TEXTCOLOUR, shell());
	printf("%s %s %s",ascii.dcol7, PACKAGETEXT, TEXTCOLOUR);

	/* Open the process that displays the number of packages,
	   then read the output and display characters.        */
	char *pkgString = pipeRead(ascii.getpkg);

	printf("%s \n%s",pkgString, ascii.dcol8);
	printf("\n");
	if (BLOCKS == 0) {
		blockdraw();
	}
	printf("%s", RESET); // Reset terminal's colors
	free(os_string);
	free(pkgString);
	return 0;
}

