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

void LogError (const char*);

int main () {
    const char filename[] = "./orders"; 
    //make fifo pipe file
    if( mkfifo(filename,0660) == -1 ) {
        LogError("Cannot create fifo ");
        return 1;
    }
    //open file read only
    while(true) {
        int fd;
        if ( fd = open(filename,O_RDONLY) == -1 ) {
            LogError("Cannot open ");
            return 1;
        }
        int jobnum = -1;
        //read opened file into jobnum
        if ( read(fd,&jobnum,sizeof(int)) != sizeof(int) ) {
            LogError("Cannot read ");
            close(fd);
            return 1;
        }
        close(fd);
        pid_t child = fork();

        if( child == -1 ) {
            LogError("Cannot fork");
            return 1;
        } 
        //inside child execute job specified in FIFO
        if( child == 0 ) {
            char arr[4];
            //number to string conversion
            if( sprintf(arr,"./%d",jobnum) < 0 ) {
                LogError("Cannot format jobname ");
            }
            if ( execlp(arr,arr,NULL) == -1 ) {
                LogError("Cannot Execute ");
                return 1;
            }
        } 
    }

    return 0;
} 

void LogError (const char* message) {
    std::cerr<< getpid() << " - Error: " << message << strerror(errno) << std::endl;
}