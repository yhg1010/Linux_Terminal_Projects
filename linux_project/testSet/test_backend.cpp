#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
using namespace std;

void print_(char name[]) {
    printf("hello, %s\n", name);
}
int main(int argc, char **argv) {
    print_(argv[1]);
    exit(0);
    return 0;
}