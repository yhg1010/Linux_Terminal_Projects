#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char **argv){
    mode_t mode = 0666;
    if (argc != 2){
        printf("at least one argument\n");
        return 0;
    }
    if((mkfifo(argv[1], mode)) < 0){
        printf("fail to mkfifo\n");
        return 0;
    }
    else {
        printf("successfully create the mkfifo %s\n", argv[1]);
    }
    return 0;
}