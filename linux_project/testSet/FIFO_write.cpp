#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <iostream>
#define BUFES 1024
using namespace std;
int main(void)
{
    //int fd;
    int n;
    char buf[BUFES];
    time_t tp;
    printf("I am %d\n", getpid());

    int i = 0;
    int filesize = 0;
    DIR *dir = NULL;
    char pwd[512];
    getcwd(pwd, sizeof(pwd));
    struct dirent *entry;

    // if ((fd = open("../testMkfifo", O_WRONLY)) < 0)
    // {
    //     printf("Open failed!\n");
    //     exit(1);
    // }
    //for (i = 0; i < 10; i++)
    //{
        // time(&tp);                                                        
        // n = sprintf(buf, "write_fifo %d sends %s", getpid(), ctime(&tp)); 
        // printf("send msg:%s\n", buf);
        // if ((write(fd, buf, n + 1)) < 0)
        // { 
        //     printf("write failed!\n");
        //     close(fd); 
        //     exit(1);
        // }
    //     dir = opendir(pwd);
    //     //struct dirent *entry;
    //     while((entry = readdir(dir)) && entry){
    //         n = sprintf(buf, "%s", entry->d_name);
    //         cout << n << endl;
    //         write(fd, buf, n + 1);
    //     }
    //     closedir(dir);
    //   //  sleep(3); 
    // //}
    // close(fd); 
    FILE * fp;
    fp = popen("ls", "r");
    int fd = open("../testMkfifo", O_WRONLY);
    while(fgets(buf, sizeof(buf), fp) != 0)
        write(fd, buf, sizeof(buf));
    pclose(fp);
    exit(0);
}
