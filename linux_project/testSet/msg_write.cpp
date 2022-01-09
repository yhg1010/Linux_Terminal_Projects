/*************************************************************************
	> File Name: msg_send.c
	> Author: kid
	> Mail: 280197326@qq.com 
	> Created Time: 2014年03月01日 星期六 23时15分47秒
 ************************************************************************/
 
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <iostream>
#define MAXMSG 512
using namespace std;
struct my_msg   //消息队列结构体
{
	long int my_msg_type;
	int i;
	char some_text[MAXMSG];
}msg;
int main()
{
	int msgid;
	char buffer[BUFSIZ];
	msgid=msgget(13,0666|IPC_CREAT);  //创建消息队列
 
	//while(1){
		//puts("Enter some text:");
		//fgets(buffer,BUFSIZ,stdin);
		msg.i++;
		//printf("i=%d\n",msg.i);
		msg.my_msg_type=3;
		string s = "ls";
		strcpy(buffer, s.c_str());
		strcpy(msg.some_text,buffer);
		msgsnd(msgid,&msg,MAXMSG,0);   //发送数据到缓冲区
		//if(strncmp(msg.some_text,"end",3)==0){   //比较输入，若为end则跳出循环
		  //  break;
        //}
    //}
	exit(0);
}