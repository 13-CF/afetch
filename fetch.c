#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include "config.h"

char * os()
{
	FILE *f;
	char *str = malloc(100);
	
	f = fopen("/etc/os-release", "r");
	if (f == NULL) {
		f = fopen("/var/run/os-release", "r"); }
		if (f == NULL) {
			return "unknown"; }
//	fscanf(f, "%s", dist);

	fgets(str, 100, f);
	fclose(f);
	str = strtok(str, "NAME=\""); //if dist is Arch Linux, it seems to return rch Linux, so the next to lines fix it
	if (strncmp(str, "rch Linux", 9) == 0) {
		return "Arch Linux"; }
	else if (strncmp(str, "Gentoo\n", 7) == 0) {
		return "Gentoo"; }
	else if (strncmp(str, "rtix Linux\n", 10) == 0) {
		return "Artix Linux"; }
	else if (strncmp(str, "PR", 2) == 0) { 
		return "Debian"; } //PRETTY_NAME is on the first line on debian, but not sure about other distros
	return str;
}


Dist asciiart() {
	char * dist = os();
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
		return info; }
	else if (strncmp(dist, "Gentoo", 6) == 0) {
       		info.dcol1=BMAGENTA"   _-----_ \n";
      		info.dcol2=BMAGENTA"  (       \\  ";
      		info.dcol3=BMAGENTA"  \\    0   \\ ";
      		info.dcol4=BMAGENTA"   \\        )";
    		info.dcol5=BMAGENTA"   /      _/ ";
   		info.dcol6=BMAGENTA"  (     _-   ";
   		info.dcol7=BMAGENTA"  \\____-     ";
   		info.dcol8=BWHITE"\n";
		info.getpkg = "ls -d /var/db/pkg/*/* | wc -l";
		return info; }
	else if (strncmp(dist, "Arch Linux", 10)==0) {
       		info.dcol1=BCYAN"";
      		info.dcol2=BCYAN"      /\\      ";
      		info.dcol3=BCYAN"     /  \\     ";
      		info.dcol4=BCYAN"    /\\   \\    ";
    		info.dcol5=BCYAN"   /      \\   ";
   		info.dcol6=BCYAN"  /   ,,   \\  ";
   		info.dcol7=BCYAN" /   |  |  -\\ ";
   		info.dcol8=BCYAN"/_-''    ''-_\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		return info; }
	else if (strncmp(dist, "Artix Linux", 11)==0) {
       		info.dcol1=BCYAN"";
      		info.dcol2=BCYAN"      /\\      ";
      		info.dcol3=BCYAN"     /  \\     ";
      		info.dcol4=BCYAN"    /`'.,\\    ";
    		info.dcol5=BCYAN"   /     ',   ";
   		info.dcol6=BCYAN"  /      ,`\\  ";
   		info.dcol7=BCYAN" /   ,.'`.  \\ ";
   		info.dcol8=BCYAN"/.,'`     `'.\\\n";
		info.getpkg = "pacman -Qq | wc -l";
		return info;  }
	else if (strncmp(dist, "Fedora", 6)==0) {
       		info.dcol1=BBLUE"      _____\n";
      		info.dcol2=BBLUE"     /   __)\\ ";
      		info.dcol3=BBLUE"     |  /  \\ \\";
      		info.dcol4=BBLUE"  ___|  |__/ /";
    		info.dcol5=BBLUE" / (_    _)_/ ";
   		info.dcol6=BBLUE"/ /  |  |     ";
   		info.dcol7=BBLUE"\\ \\__/  |     ";
   		info.dcol8=BBLUE" \\(_____/";
		info.getpkg="rpm -qa | wc -l";	//this command is really slow, should probably find a faster way to find the packages
		return info; }
	else if (strncmp(dist, "FreeBSD", 7)==0) {
       		info.dcol2=BRED"/\\,-'''''-,/\\";
      		info.dcol3=BRED"\\_)       (_/";
      		info.dcol4=BRED"|           |";
      		info.dcol5=BRED"|           |";
    		info.dcol6=BRED" ;         ; ";
   		info.dcol7=BRED"  '-_____-'  ";
   		info.dcol8=BRED"";
   		info.dcol1=BRED"";
		info.getpkg="pkg info | wc -l";
		return info; }

	else if (strncmp(dist, "Debian", 6)==0) {
       		info.dcol1=BRED"  _____\n";
      		info.dcol2=BRED" /  __ \\ ";
      		info.dcol3=BRED"|  /    |";
      		info.dcol4=BRED"|  \\___- ";
    		info.dcol5=BRED"-_       ";
   		info.dcol6=BRED"  --_    ";
   		info.dcol7=BRED"         ";
   		info.dcol8=BRED"";

		info.getpkg="apt list --installed | wc -l";
		return info;}
	else {
       		info.dcol1=BWHITE"     .---. \n";
      		info.dcol2=BWHITE"    /     \\     ";
      		info.dcol3=BWHITE"    \\.@-@./     ";
      		info.dcol4=BWHITE"    /`\\_/`\\     ";
    		info.dcol5=BWHITE"   //  _  \\\\    ";
   		info.dcol6=BWHITE"  | \\     )|_   ";
   		info.dcol7=BWHITE" /`\\_`>  <_/ \\  ";
   		info.dcol8=BWHITE" \\__/'---'\\__/\n";
		info.getpkg = "echo unknown";
		return info; }
}



char * shell() {
	char * shell = strtok(getenv("SHELL"), "/bin");
	//if your $SHELL is set to /usr/bin/*sh this will be run

	if (strncmp(getenv("SHELL"), "/bin/bash", 9)==0)  {
		return "bash"; }
	if (strncmp(shell, "usr", 3) == 0){
		while (strncmp(shell, "usr", 3)==0) {
			shell = strtok(NULL, "bin/");} }
	if (strncmp(getenv("SHELL"), "/usr/bin/bash", 13)==0) {
		return "bash"; }
	 
	return shell;
}
int main(){
	/* initialise system info */
	struct sysinfo si; //used for uptime
	struct utsname ui; //used for hostname, system name and system release
	uname(&ui);
	sysinfo(&si);
	Dist ascii = asciiart();

	printf("%s", ascii.dcol1);
	printf("%s %s %s%s\n",ascii.dcol2,USERTEXT, WHITE, getenv("USER"));
	printf("%s %s %s%s\n",ascii.dcol3,DISROTEXT, WHITE,os());
	printf("%s %s %s%s %s\n",ascii.dcol4,KERNELTEXT, WHITE, ui.sysname, ui.release);
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
	printf("%s", ascii.dcol8);
	printf("\n");
	return 0;
}
