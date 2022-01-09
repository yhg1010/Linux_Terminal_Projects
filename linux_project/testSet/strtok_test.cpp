#include <iostream>
#include <string.h>
using namespace std;
int main(){
    char buf[] = "i like";
    char *p = strtok(buf, " ");
    if(p){
        cout << p << endl;
    }
    while((p = strtok(NULL, " ")) && p){
        cout << p << endl;
    }
    return 0;
}