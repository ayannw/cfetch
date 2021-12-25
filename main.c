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

  const char * red = "\x1B[31m";
  const char * green = "\x1B[32m";
  const char * blue = "\x1B[34m";
  const char * magenta = "\x1B[35m";
  const char * cyan = "\x1B[36m";
  const char * yellow = "\x1B[33m";
  const char * white = "\x1B[37m";

  const char * normal = "\x1B[0m";

  const char * bold = "\x1B[1m";

  if(uname(&name)) exit(-1);
  gethostname(hostname, HOST_NAME_MAX + 1);

  Info info;

  info.os = name.sysname;
  info.host = hostname;
  info.uptime = getUptime();
  info.user = getlogin();

  printf("%s", bold);
  printf("%sOS%s:     \t%s\n", green, white, info.os);
  printf("%sHost%s:   \t%s\n", blue, white, info.host);
  printf("%sUptime%s: \t%s\n", yellow, white, info.uptime);
  printf("%sUser%s:   \t%s\n", red, white, info.user);

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
