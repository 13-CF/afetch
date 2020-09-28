#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

/* COLOUR CODES */
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





char * os()
{
	FILE *f;
	char *str = malloc(50);
	
	f = fopen("/etc/os-release", "r");
	if (f == NULL) {
		f = fopen("/var/run/os-release", "r"); }
		if (f == NULL) {
			return "unknown"; }
//	fscanf(f, "%s", dist);

	fgets(str, 50, f);
	fclose(f);
	str = strtok(str, "NAME=\""); //if dist is Arch Linux, it seems to return rch Linux, so the next to lines fix it
	if (strncmp(str, "rch Linux", 9) == 0) {
		str = "Arch Linux"; }
	else if (strncmp(str, "Gentoo\n", 7) == 0) {
		str = "Gentoo"; }
	else if (strncmp(str, "rtix Linux\n", 10) == 0) {
		str = "Artix Linux"; }
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
		info.getpkg = "xbps-query -l | wc -l"; }
	else if (strncmp(dist, "Gentoo", 6) == 0) {
       		info.dcol1=BMAGENTA"   _-----_ \n";
      		info.dcol2=BMAGENTA"  (       \\  ";
      		info.dcol3=BMAGENTA"  \\    0   \\ ";
      		info.dcol4=BMAGENTA"   \\        )";
    		info.dcol5=BMAGENTA"   /      _/ ";
   		info.dcol6=BMAGENTA"  (     _-   ";
   		info.dcol7=BMAGENTA"  \\____-     ";
   		info.dcol8=BWHITE"\n";
		info.getpkg = "ls -d /var/db/pkg/*/* | wc -l"; }
	else if (strncmp(dist, "Arch Linux", 10)==0) {
       		info.dcol1=BCYAN"";
      		info.dcol2=BCYAN"      /\\      ";
      		info.dcol3=BCYAN"     /  \\     ";
      		info.dcol4=BCYAN"    /\\   \\    ";
    		info.dcol5=BCYAN"   /      \\   ";
   		info.dcol6=BCYAN"  /   ,,   \\  ";
   		info.dcol7=BCYAN" /   |  |  -\\ ";
   		info.dcol8=BCYAN"/_-''    ''-_\\\n";
		info.getpkg = "pacman -Qq | wc -l";  }
	else if (strncmp(dist, "Artix Linux", 11)==0) {
       		info.dcol1=BCYAN"";
      		info.dcol2=BCYAN"      /\\      ";
      		info.dcol3=BCYAN"     /  \\     ";
      		info.dcol4=BCYAN"    /`'.,\\    ";
    		info.dcol5=BCYAN"   /     ',   ";
   		info.dcol6=BCYAN"  /      ,`\\  ";
   		info.dcol7=BCYAN" /   ,.'`.  \\ ";
   		info.dcol8=BCYAN"/.,'`     `'.\\\n";
		info.getpkg = "pacman -Qq | wc -l";  }
	else if (strncmp(dist, "Fedora", 6)==0) {
       		info.dcol1=BBLUE"      _____\n";
      		info.dcol2=BBLUE"     /   __)\\ ";
      		info.dcol3=BBLUE"     |  /  \\ \\";
      		info.dcol4=BBLUE"  ___|  |__/ /";
    		info.dcol5=BBLUE" / (_    _)_/ ";
   		info.dcol6=BBLUE"/ /  |  |     ";
   		info.dcol7=BBLUE"\\ \\__/  |     ";
   		info.dcol8=BBLUE" \\(_____/";
		info.getpkg="rpm -qa | wc -l";	}
	else if (strncmp(dist, "FreeBSD", 7)==0) {
       		info.dcol2=BRED"/\\,-'''''-,/\\";
      		info.dcol3=BRED"\\_)       (_/";
      		info.dcol4=BRED"|           |";
      		info.dcol5=BRED"|           |";
    		info.dcol6=BRED" ;         ; ";
   		info.dcol7=BRED"  '-_____-'  ";
   		info.dcol8=BRED"";
   		info.dcol1=BRED"";
		info.getpkg="pkg info | wc -l"; }

	else {
       		info.dcol1=BWHITE"     .---. \n";
      		info.dcol2=BWHITE"    /     \\     ";
      		info.dcol3=BWHITE"    \\.@-@./     ";
      		info.dcol4=BWHITE"    /`\\_/`\\     ";
    		info.dcol5=BWHITE"   //  _  \\\\    ";
   		info.dcol6=BWHITE"  | \\     )|_   ";
   		info.dcol7=BWHITE" /`\\_`>  <_/ \\  ";
   		info.dcol8=BWHITE" \\__/'---'\\__/\n";
		info.getpkg = "echo unknown";}
	return info;
}



char * shell() {
	char * shell = strtok(getenv("SHELL"), "/bin");
	//if your $SHELL is set to /usr/bin/*sh this will be run

	if (strncmp(getenv("SHELL"), "/bin/bash", 9)==0)  {
		return "bash"; }
	if (strncmp(getenv("SHELL"), "/usr", 4)==0) {
		return "bash"; }
	if (strncmp(shell, "usr", 3) == 0){
		while (strncmp(shell, "usr", 3)==0) {
			shell = strtok(NULL, "bin/");} }
	 
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
	printf("%s      USER %s%s\n",ascii.dcol2, WHITE, getenv("USER"));
	printf("%s    DISTRO %s%s\n",ascii.dcol3,WHITE,os());
	printf("%s    KERNEL %s%s %s\n",ascii.dcol4, WHITE, ui.sysname, ui.release);
	printf("%s    UPTIME %s%lih %lim\n", ascii.dcol5, WHITE, si.uptime / 3600, (si.uptime / 60) - (si.uptime / 3600 * 60));
	printf("%s     SHELL %s%s\n",ascii.dcol6,WHITE, shell());
	printf("%s      PKGS "WHITE, ascii.dcol7);

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
