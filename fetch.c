#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include "config.h"
char * os()
{
	char *releasefileContents = malloc(100);
	char *os = malloc(100);
	
	if (releasefileContents == NULL || os == NULL) {
		perror("os(): ");
		exit(1);
	}

	FILE *f = fopen("/etc/os-release", "r");
	if (f == NULL) { f = fopen("/var/run/os-release", "r"); }
	if (f == NULL) {
		strncpy(os, "unknown", 7);
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
	} else if (strncmp(os, "FreeBSD\n", 8) == 0) {
		os[7] = '\0';
	} else if (strncmp(os, "Slackware\n", 10) == 0) {
		os[9] = '\0'; 
	}
	return os;
}

char * lowercase(char * str) {
	if (LOWERCASE == 0) {
		int i;
		for (i=0; i<strlen(str); i++) {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				str[i] += (32);
			}
		}
		return str;
	}
	return str;
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

Dist asciiart() {
	char* dist = os();
	Dist info;
	if (strncmp(dist, "void", 4) == 0) {
		info.dcol1 =    BGREEN "     _______\n";
		info.dcol2 =    BGREEN  "  _ \\______ - ";
		info.dcol3 =	BGREEN  " | \\  ___  \\ |";
		info.dcol4 = 	BGREEN" | | /   \\ | |";
		info.dcol5 =	BGREEN" | | \\___/ | |";
		info.dcol6 =	BGREEN" | \\______ \\_|";
		info.dcol7  =	BGREEN "  -_______\\   ";
		info.dcol8  =   "";
		info.getpkg = "xbps-query -l | wc -l";
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
	} else if (strncmp(dist, "Fedora", 6)==0) {
       		info.dcol1=BBLUE"      _____\n";
      		info.dcol2=BBLUE"     /   __)\\ ";
      		info.dcol3=BBLUE"     |  /  \\ \\";
      		info.dcol4=BBLUE"  ___|  |__/ /";
    		info.dcol5=BBLUE" / (_    _)_/ ";
   		info.dcol6=BBLUE"/ /  |  |     ";
   		info.dcol7=BBLUE"\\ \\__/  |     ";
   		info.dcol8=BBLUE" \\(_____/";
		info.getpkg="rpm -qa | wc -l";	//this command is really slow, should probably find a faster way to find the packages
	} else if (strncmp(dist, "FreeBSD", 7)==0) {
       		info.dcol2=BRED"/\\,-'''''-,/\\";
      		info.dcol3=BRED"\\_)       (_/";
      		info.dcol4=BRED"|           |";
      		info.dcol5=BRED"|           |";
    		info.dcol6=BRED" ;         ; ";
   		info.dcol7=BRED"  '-_____-'  ";
   		info.dcol8=BRED"";
   		info.dcol1=BRED"";
		info.getpkg="pkg info | wc -l | tr -d ' '";
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
	} else {
       		info.dcol1=BWHITE"     .---. \n";
      		info.dcol2=BWHITE"    /     \\     ";
      		info.dcol3=BWHITE"    \\.@-@./     ";
      		info.dcol4=BWHITE"    /`\\_/`\\     ";
    		info.dcol5=BWHITE"   //  _  \\\\    ";
   		info.dcol6=BWHITE"  | \\     )|_   ";
   		info.dcol7=BWHITE" /`\\_`>  <_/ \\  ";
   		info.dcol8=BWHITE" \\__/'---'\\__/\n";
		info.getpkg = "echo unknown";
	}
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
	/* initialise system info */
	struct sysinfo si; //used for uptime
	struct utsname ui; //used for hostname, system name and system release
	uname(&ui);
	sysinfo(&si);
	Dist ascii = asciiart();

	char *os_string = os();

	printf("%s", ascii.dcol1);
	printf("%s %s %s%s\n",ascii.dcol2,USERTEXT, WHITE, lowercase(getenv("USER")));
	printf("%s %s %s%s\n",ascii.dcol3,DISROTEXT, WHITE, lowercase(os_string));
	printf("%s %s %s%s %s\n",ascii.dcol4,KERNELTEXT, WHITE,lowercase(ui.sysname), ui.release);
	printf("%s %s %s%lih %lim\n", ascii.dcol5,UPTIMETEXT, WHITE, si.uptime / 3600, (si.uptime / 60) - (si.uptime / 3600 * 60));
	printf("%s %s %s%s\n",ascii.dcol6, SHELLTEXT,WHITE, shell());
	printf("%s %s %s",ascii.dcol7, PACKAGETEXT, WHITE);

	FILE *pkgs;
	char p;
	pkgs = popen(ascii.getpkg, "r");
	if (pkgs == NULL) {
		puts("\0"); }
	while ( (p=fgetc(pkgs)) != EOF) {
		putchar(p); }
	pclose(pkgs);
	printf("%s", ascii.dcol8);
	printf("\n");
	printf("\e[0m"); // Reset terminal's colors

	free(os_string);

	return 0;
}
