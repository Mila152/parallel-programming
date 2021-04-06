#include <pthread.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <vector>
#include <string>
#include <unistd.h>
#include "MessageQueue.h"

void User1(std::string);
void User2(std::string);

int main() {
    MessageQueue *obj = new MessageQueue;
    obj->RegisterHandler(User1);
    obj->RegisterHandler(User2);
    sleep(1);
    obj->PostMessage("message 1");
    obj->PostMessage("message 2");
    
    int x;
    std::cin>>x;
    return 0;
}

void User1(std::string message) {
    std::cout<<"User1 "<<message<<std::endl;
}

void User2(std::string message) {
    std::cout<<"User2 "<<message<<std::endl;
}    