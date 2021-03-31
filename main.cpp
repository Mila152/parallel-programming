#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "person.h"

void LogError (const char*);

int main() {
    //create child process
    pid_t child_id = fork();
    if (-1 == child_id) {
        LogError("Cannot fork");
        return 1;
    }

    Person* shared_class = shared_class->getInstance();

    if (0 == child_id) {
        std::cout << getpid() << " Hello from Child!" << std::endl;
        shared_class->setName("Artak");
        shared_class->setAge(56);
        std::cout << "Name: " << shared_class->getName() << std::endl << "Age: " << shared_class->getAge() << std::endl;
        return 0;
    } else {
        std::cout<< getpid() << " Hello from Parent!" << std::endl;
        shared_class->setName("Katra");
        shared_class->setAge(65);
        std::cout << "Name: " << shared_class->getName() << std::endl << "Age: " << shared_class->getAge() << std::endl;
        return 0;
    }

    return 0;
}

void LogError (const char* message) {
    std::cerr<< getpid() << " - Error: " << message << strerror(errno) << std::endl;
}