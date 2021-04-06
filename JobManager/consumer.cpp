#include <pthread.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void LogError (const char*);

int main(){
    const char  filename[]="./orders";

    int fd;
    int jobnum;
    std::cout << "enter jobnum " << std::endl;
    std::cin >> jobnum;
    //open FIFO for writing
    if((fd=open(filename,O_WRONLY)) == -1){
        LogError("cannot open");
        return 1;
    };
    
    //write inputed job number into FIFO 
    if(write(fd,&jobnum,sizeof(int)) != sizeof(int)){
        LogError("cannot write");
        close(fd);
        return 1;
    }
    close(fd);

    return 0;
}

void LogError(const char* message){
    std::cerr<<getpid() << "   Error: " << message << "  :  "<< strerror(errno) << std::endl;
}
