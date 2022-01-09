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

void cd() {

    //将执行的结果传入命名管道
    int fd = open("testMkfifo", O_WRONLY);

    //获取当前目录
    char bufCwd[80];
    getcwd(bufCwd, sizeof(bufCwd));
    //sprintf(buf, "rename success");
    write(fd, bufCwd, sizeof(bufCwd));
    //pclose(fp);
    //cout << "hello world" << endl;
    exit(0);
}


int main(int argc, char ** argv){
    cd();
    return 0;
}