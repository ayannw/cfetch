#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <string.h>

char * getUptime();

int main() {
  typedef struct {
    char * os;
    char * host;
    char * uptime;
    char * user;
  } Info;
  struct utsname name;
  char hostname[HOST_NAME_MAX + 1];

  if(uname(&name)) exit(-1);
  gethostname(hostname, HOST_NAME_MAX + 1);

  Info info;

  info.os = name.sysname;
  info.host = hostname;
  info.uptime = getUptime();
  info.user = getlogin();

  printf("OS:     \t%s\n", info.os);
  printf("Host:   \t%s\n", info.host);
  printf("Uptime: \t%s\n", info.uptime);
  printf("User:   \t%s\n", info.user);

  return 0;
}

char * getUptime() {
  struct sysinfo si;
  const long minute = 60;
  const long hour = minute * 60;
  const long day = hour * 24;
  static char res[50];
  
  sysinfo (&si);

  sprintf(res, "%ldd %ldh %02ldm %02lds", 
     si.uptime / day, (si.uptime % day) / hour, 
     (si.uptime % hour) / minute, si.uptime % minute);


  return res;
}
