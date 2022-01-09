#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <iostream>
#include <sys/msg.h>
#include <dirent.h>
#include <vector>
#define BUFES PIPE_BUF
#define MAXMSG 512
using namespace std;

struct my_msg {
    int i;
    long int my_msg_type;
    char text[MAXMSG];
}msg;

void print_(char ** argv) {   
    //建立管道
    int fd = open("testMkfifo", O_WRONLY);
    char buf[BUFES];
    FILE * fp;

    //预处理
    if(argv[1] == NULL){
        //将执行的结果传入命名管道
        fp = popen("ls", "r");
        while(fgets(buf, sizeof(buf), fp) != 0)
            write(fd, buf, sizeof(buf));
    }
    else {
        char tem[] = "ls ";
        char *codeComplete = strcat(tem, argv[0]);
        fp = popen(codeComplete, "r");
        while(fgets(buf, sizeof(buf), fp) != 0)
            write(fd, buf, sizeof(buf));
        
    }
    pclose(fp);
    exit(0);
}


int main(int argc, char ** argv){
    //print_(argv[1]);
    print_(argv);
    return 0;
}