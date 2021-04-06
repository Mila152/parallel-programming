#include <pthread.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>

int main(int argc, char** argv) {
    //string to int conversion
    //+2 to discard last two symbols` /0
    int num = atoi(argv[0] + 2);
    std::cout << "num is: " << num << std::endl;
    for( int i = 0; i < num; ++i ) {
        std::cout << "Is working: " << i << "/" << num << std::endl;
    }
}