#include <pthread.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <vector>
#include <string>
#include "MessageQueue.h"

//Initialize mutex and condition variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;

void MessageQueue::PostMessage(std::string message){
    pthread_mutex_lock(&mutex);
    std::cout<<"Post Message called with "<<message<<std::endl;

    _queue.push(message);

    //signal the waiting thread
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&mutex);
}

void MessageQueue::RegisterHandler(MessageHandler handler){
    _handlers.push_back(handler);
}

//global struct for Broadcast function
struct obprop{
    std::vector<MessageHandler>* _handlers;
    std::string _message;
};

void* MessageBroadcaster(void * par){
    obprop* ob = (obprop*)par;
    for(int i = 0; i < ob->_handlers->size(); ++i){
        //all handlers one message
        (*ob->_handlers)[i](ob->_message);
    }
    return 0;
}

void* MessageHand(void* par){
    MessageQueue* ob = (MessageQueue*)par;

    while(true){
        std::cout<<"Wait for message "<<std::endl;
        pthread_cond_wait(&cv,&mutex);

        while(!ob->_queue.empty()){
            std::string message = ob->_queue.front();
            ob->_queue.pop();
            //to pass two args to pthread_create use struct
            obprop *st = new obprop;
            st->_handlers = &ob->_handlers;
            st->_message = message;

            //call MessageBroadcaster in thread
            pthread_t thread;
            if( int error = pthread_create(&thread,NULL,MessageBroadcaster,st) != 0 ){
                std::cerr<<"Cannot create thread "<<strerror(error)<<std::endl;
            }
        }
        //waiting on conditional variable automatically locks mutex 
        pthread_mutex_unlock(&mutex);
    }
}

MessageQueue:: MessageQueue(){
    //cast to void* for feeding into pthread_create
    void* obcast = static_cast<void*>(this);
    pthread_t thread;
    pthread_cond_init(&cv,NULL);

    //call MessageHand using thread
    if( int error = pthread_create(&thread,NULL,MessageHand,obcast) != 0){
        std::cerr<<"Cannot create thread"<<strerror(error)<<std::endl;  
    }
}