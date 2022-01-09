#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <map>
#include <sys/msg.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <signal.h>
#define BUFES PIPE_BUF
#define MAXMSG 512
using namespace std;


map<string, string> codeTable;

struct my_msg {
    int i;
    long int my_msg_type;
    char text[MAXMSG];
}msg;

void init(){
    //指令映射
    codeTable["dir"] = "ls";
    codeTable["rename"] = "mv";
    codeTable["move"] = "mv2";
    codeTable["del"] = "rm";
    codeTable["cd"] = "cd";
    codeTable["exit"] = "exit";
    //界面初始化
    cout << "----------------------" << endl;
    cout << "code map :" << endl;
    cout << endl;
    for (map<string, string>::iterator it = codeTable.begin(); it != codeTable.end(); it++)
        cout << it->first << " " << it->second << endl;
    cout << endl;
    cout << "process start" << endl;
    cout << "----------------------" << endl;
}

int mainProcess(){
    //主逻辑，接收键盘输入，转换为linux指令，传递到后台程序进行处理，返回结果并显示到终端
    char code[80];
    char *p = NULL;
    char mainCode[80];

    //存储子进程号
    int pidIndex = 0;
    vector<int> pidSet;
    
    //接收命令，进行转换并处理
    while (1) {
        //输入win指令，转换为linux指令
        cout << ">>> ";
        gets(code);

        //命令分词
        p = strtok(code, " ");
        if(p){
            strcpy(mainCode, p);
        }
        
        string mainCodeTrans = string(&mainCode[0], &mainCode[strlen(mainCode)]);
        string mapTrans = codeTable[mainCodeTrans];

        //fork调起后台程序，execl装载可执行程序
        if(mapTrans == "ls"){
            //fork子进程，execl装入对应的可执行文件
            int signal = fork();
            if(signal == 0){

                int index = 0;
                char **para;
                while((p = strtok(NULL, " ")) && p){
                    cout << p << endl;
                    strcpy(para[index++], p);
                }
                if(index == 0)
                    execl("lsBackend", "print_", NULL);
                else if(index == 1)
                    execl("lsBackend", "print_", para, NULL);

            }
            else {
                //存储子进程的PID
                cout << signal << endl;
                pidSet.push_back(signal);
            
            }
            //建立命名管道
            int fd;
            if((fd = open("testMkfifo", O_RDONLY)) < 0){
                cout << "can not open the testMkfifo";
                return 0;
            }        
            //从命名管道中获取结果并显示到终端
            char buf[BUFES];
            int len;
            while((len = read(fd, buf, BUFES)) > 0)
                cout << buf;
            close(fd);

        }
        else if(mapTrans == "cd"){
            
            int signal = fork();
            if(signal == 0){
                execl("cdBackend", "cd", NULL);
            }
            else {
                cout << signal << endl;
                pidSet.push_back(signal);
            }

            //建立命名管道
            int fd;
            if((fd = open("testMkfifo", O_RDONLY)) < 0){
                cout << "can not open the testMkfifo";
                return 0;
            }        
            //从命名管道中获取结果并显示到终端
            char buf[BUFES];
            int len;
            while((len = read(fd, buf, BUFES)) > 0)
                cout << buf << endl;
            close(fd);

        }
        else if(mapTrans == "mv"){

            //命令分词分出源文件和改名后的文件
            char codeComplete[2][80];
            int i = 0;
            while((p = strtok(NULL, " ")) && p)
                strcpy(codeComplete[i++], p);
            //cout << codeComplete << endl;
            int signal = fork();
            if(signal == 0){
                execl("mvBackend", "rename", codeComplete[0], codeComplete[1], NULL);
            }
            else {
                cout << signal << endl;
                pidSet.push_back(signal);
            }
            //建立管道
            int fd;
            if((fd = open("testMkfifo", O_RDONLY)) < 0){
                cout << "can not open the testMkfifo" << endl;
                return 0;
            }        
            //从命名管道中获取结果并显示到终端
            char buf[BUFES];
            int len;
            while((len = read(fd, buf, BUFES)) > 0)
                cout << buf << endl;
            close(fd);

        }
        else if(mapTrans == "mv2"){
            //命令分词分出文件和移动后的路径
            char codeComplete[2][80];
            int i = 0;
            while((p = strtok(NULL, " ")) && p)
                strcpy(codeComplete[i++], p);
          
            int signal = fork();
            if(signal == 0){
                execl("mv2Backend", "mv", codeComplete[0], codeComplete[1], NULL);
            }
            else {
                cout << signal << endl;
                pidSet.push_back(signal);
            }
            //建立管道
            int fd;
            if((fd = open("testMkfifo", O_RDONLY)) < 0){
                cout << "can not open the testMkfifo" << endl;
                return 0;
            }        
            //从命名管道中获取结果并显示到终端
            char buf[BUFES];
            int len;
            while((len = read(fd, buf, BUFES)) > 0)
                cout << buf << endl;
            close(fd);

        }
        else if(mapTrans == "rm"){

            char codeComplete[80];
            while((p = strtok(NULL, " ")) && p)
                strcpy(codeComplete, p);
    
            int signal = fork();
            if(signal == 0){
                execl("rmBackend", "rm_", codeComplete, NULL);
            }
            else {
                cout << signal << endl;
                pidSet.push_back(signal);
            }

            int fd;
            if((fd = open("testMkfifo", O_RDONLY)) < 0){
                cout << "can not open the testMkfifo" << endl;
                return 0;
            }        
            //从命名管道中获取结果并显示到终端
            char buf[BUFES];
            int len;
            while((len = read(fd, buf, BUFES)) > 0)
                cout << buf << endl;
            close(fd);

        }
        else if(mapTrans == "exit"){

            //从存储的子程序进程号中依次kill掉后台程序
            char temPid[10];
            for(vector<int>::iterator it = pidSet.begin(); it != pidSet.end(); it++){
                sprintf(temPid, "%d", *it);
                string killTem = string(&temPid[0], &temPid[strlen(temPid)]);
                string killComplete = "kill -9 " + killTem;
                cout << "kill " << *it << endl;
                //popen(killComplete.c_str(), "w");
                kill(*it, SIGKILL);
            }
    
            cout << "exit success" << endl;
            break;
        }
 
    }  
    return 0;
}

int main(){
    init();
    mainProcess();
    return 0;
}