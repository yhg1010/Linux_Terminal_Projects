#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
    int signal = fork();
    if (signal == 0) {
        execl("test_backend", "print_", "jones", NULL);
    }
    else {
        int childPid;
        childPid = wait(NULL);
        cout << childPid << endl;
    }
    int i;
    cin >> i;
    return 0;
}