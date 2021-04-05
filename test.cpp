#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

enum testresults {
    success,
    failed,
    unresolved
};

void LogError (const char*);
testresults Test1();
testresults Test2();
testresults Test3();

testresults(*testarr[])() = {
    Test1, Test2, Test3
};

const int process_number = 3;

int main () {

    for (int i = 0; i < process_number; i++)
    {
        int fds[2];
        if (pipe(fds) == -1) {
            LogError("Cannot create pipe");
        }
        
        pid_t child_id = fork();

        if (-1 == child_id) {
            LogError("Cannot fork");
        }

        if (child_id == 0) {
            //disable output on child by closing write descriptor
            close(1);
            //duplicate file descriptor for redirecting child output to parent
            dup(fds[1]);
            close(fds[0]);
            close(fds[1]);
            return testarr[i](); 
        } else {
            const int result_size = 100;
            char result[result_size];

            //TODO:enhancement to read dynamically
            // while(ssize_t current_size = read(fds[0], result, result_size) != 0) {
            //     if (current_size == -1 ) {
            //         LogError("Cannot read from pipe");
            //         return 1;
            //     }
            // }
            if (read(fds[0], result, result_size) == -1 ) {
                LogError("Cannot read from pipe");
                return 1;
            }

            int status;  
            wait(&status);

            //status macros
            if (WIFEXITED(status)) {
                status = WEXITSTATUS(status);
                std::cout << "Child status: " << status << "\t" << result << std::endl;
            }            
        }
    }
    
    return 0;
} 

void LogError (const char* message) {
    std::cerr<< getpid() << " - Error: " << message << strerror(errno) << std::endl;
}

testresults Test1 () {
    std::cout << "Test1" << std::endl;
    //abnormal process termination
    abort();
    return success;
}

testresults Test2 () {
    std::cout << "Test2" << std::endl;
    return failed;
}

testresults Test3 () {
    std::cout << "Test3" << std::endl;
    return unresolved;
}