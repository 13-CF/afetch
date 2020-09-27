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

char * os()
{
	FILE *f;
	char *str = malloc(50);
	char dist[50];
	
	f = fopen("/etc/os-release", "r");
	if (f == NULL) {
		f = fopen("/var/run/os-release", "r"); } //for *BSD
		if (f == NULL) {
			return "unknown"; }
//	fscanf(f, "%s", dist);

	fgets(dist, 50, f);
	fclose(f);
	str = strtok(dist, "NAME=\""); //if dist is Arch Linux, it seems to return rch Linux, so the next to lines fix it
	if (strncmp(str, "rch Linux", 9) == 0) {
		str = "Arch Linux"; }
	return str;
}


char * pkg() {
	char *distro = os();
	
	if (strncmp(distro, "void", 4) == 0) {
		return "xbps-query -l | wc -l"; }
	else if (strncmp(distro, "Fedora", 6) == 0) {
		return "rpm -qa | wc -l"; }
	else if (strncmp(distro, "Arch Linux", 10) == 0) { //something I'm doing seems to make 'Arch Linux' not work. I think it might be the strtok() in the os() function
		return "pacman -Qq | wc -l"; }
	else if (strncmp(distro, "Gentoo", 6) == 0) {
		return "equery list \"*\""; } //not sure if this is how to do it on gentoo
	else if (strncmp(distro, "FreeBSD", 7) == 0) {
		return "pkg list -i | wc -l"; }//I think this is the correct command? 

	
	return "echo unknown";
}

	
int main(){
	/* initialise system info */
	struct sysinfo si; //used for uptime
	struct utsname ui; //used for hostname, system name and system release
	uname(&ui);
	sysinfo(&si);
   /* Print info + void logo (\033 is used for colours) */
	printf(BGREEN"     _______\n" );
	printf(BGREEN"  _ \\______ -      USER %s%s\n",WHITE, getenv("USER"));
	printf(BGREEN"| \\  ___  \\ |    DISTRO %s%s\n",WHITE,os());
	printf(BGREEN"| | /   \\ | |    KERNEL %s%s %s\n", WHITE, ui.sysname, ui.release);
	printf(BGREEN"| | \\___/ | |    UPTIME %s%lih %lim\n", WHITE, si.uptime / 3600, (si.uptime / 60) - (si.uptime / 3600 * 60));
	printf(BGREEN"| \\______ \\_|     SHELL %s%s\n",WHITE, strtok(getenv("SHELL"), "/bin"));
	//system("echo \" -_______\\     \033[1;33mPACKAGES\033[0;37m $(xbps-query -l | wc -l) (xbps)\n\""); 
	//printf(GREEN" -_______\\     %s \n", pkg());

	// code that runs the code that the pkg() function returns 
	FILE *pkgs;
	char p;
	pkgs = popen(pkg(), "r");
	if (pkgs == NULL) {
		puts("\0"); }
	printf(BGREEN" -_______\\         PKGS "WHITE);
	while ( (p=fgetc(pkgs)) != EOF) {
		putchar(p); }
	printf("\n");
	return 0;
}
