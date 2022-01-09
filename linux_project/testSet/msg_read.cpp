/*************************************************************************
	> File Name: msg_receive.c
	> Author: kid
	> Mail: 280197326@qq.com 
	> Created Time: 2014年03月01日 星期六 23时24分02秒
 ************************************************************************/
 
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
 
#define MAXMSG 512
struct my_msg
{
	long int my_msg_type;
	int i;
	char some_text[MAXMSG];
}msg;
int main()
{
	int msgid;
	msg.my_msg_type=3;
	msgid=msgget(13,0666|IPC_CREAT);
	//while(1)
	//{
		msgrcv(msgid,&msg,BUFSIZ,msg.my_msg_type,0);
		printf("You wrote:%s and i=%d\n",msg.some_text,msg.i);
		//if(strncmp(msg.some_text,"end",3)==0)
		//	break;
	//}
	msgctl(msgid,IPC_RMID,0);
	exit(0);
}