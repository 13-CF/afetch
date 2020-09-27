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
	fscanf(f, "%s", dist);
	fclose(f);
	
	
	char * del = "NAME=\"";
	str = strtok(dist, del);
	return str;
}


char * pkg() {
	char *distro = os();
	
	if (strncmp(distro, "void", 4) == 0) {
		return "xbps-query -l | wc -l";
	}
	
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
	printf(BGREEN"| \\______ \\_|     SHELL %s%s\n",WHITE, getenv("SHELL"));
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
