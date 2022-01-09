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
#define BUFES PIPE_BUF
#define MAXMSG 512
using namespace std;

struct my_msg {
    int i;
    long int my_msg_type;
    char text[MAXMSG];
}msg;

void print_() {
    //通过消息队列接收转换后的命令
    int msgId;
    msgId = msgget(12, 0666 | IPC_CREAT);
    msg.my_msg_type = 3;
    //执行具体的命令(popen)

    //将执行的结果传入命名管道

    cout << "hello world" << endl;
    exit(0);
}


int main(int argc, char ** argv){
    print_();
    return 0;
}