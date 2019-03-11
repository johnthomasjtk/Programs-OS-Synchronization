#include <stdio.h>
#include <unistd.h>
int  main() {

char c;
pid_t pid;
 
FILE  *fd = fopen("test", "r");

read(fd, &c, 1);
printf("root process:%c\n",c);
 
pid = fork();

 
if (pid == 0) { /*child*/
  read(fd, &c, 1);
  printf("child:%c\n",c);
}
else { /*parent*/
  read(fd, &c, 1);
  printf("parent:%c\n",c);
}
