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
#define BUFES PIPE_BUF
#define MAXMSG 512
using namespace std;

struct my_msg {
    int i;
    long int my_msg_type;
    char text[MAXMSG];
}msg;

void rm_(char *pwd) {
    //将执行的结果传入命名管道
    int fd = open("testMkfifo", O_WRONLY);
    char buf[BUFES];
    FILE * fp;
    
    //判断文件是否存在
    if(access(pwd, 0)){
        sprintf(buf, "file not exist");
        write(fd, buf, sizeof(buf));
        exit(0);
    }
    
    string tem = string(&pwd[0], &pwd[strlen(pwd)]);
    string code = "rm " + tem;

    fp = popen(code.c_str(), "w");

    sprintf(buf, "delete success");
    write(fd, buf, sizeof(buf));
    pclose(fp);
    exit(0);
}


int main(int argc, char ** argv){
    rm_(argv[1]);
    return 0;
}