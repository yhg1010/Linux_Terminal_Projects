#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <iostream>
using namespace std;
#define BUFES 1024
int main(void)
{
   int fd;
   int len;
   char buf[BUFES];
   mode_t mode = 0666;    

   int signal = fork();
   if(signal == 0){
      execl("FIFO_write", NULL);
   }


   if ((fd = open("../testMkfifo", O_RDONLY)) < 0) 
   {
      printf("open failed!\n");
      exit(1);
   }
   while ((len = read(fd, buf, BUFES)) > 0) 
      cout << buf << endl;
   close(fd); 
   exit(0);
}
