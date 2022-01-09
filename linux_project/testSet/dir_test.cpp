#include <stdio.h>
#include "dirent.h"
#include <unistd.h>
#include <iostream>
#define FilePath "/opt/test"
using namespace std;
int main()
{
    int i = 0;
    int filesize = 0;
    DIR *dir = NULL;
    char buf[80];
    getcwd(buf, sizeof(buf));
    struct dirent *entry;
    cout << buf << endl;


    if ((dir = opendir(buf)) == NULL)
    {
        printf("opendir failed!");
        return -1;
    }
    else
    {
        while ((entry = readdir(dir)) && entry)
        {
            i++;
            printf("filename%d = %s", i, entry->d_name); //输出文件或者目录的名称
            printf("filetype = %d\n", entry->d_type);    //输出文件类型
        }

        closedir(dir);
    }
    return 0;
}
