#include <pthread.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <queue>
#include <vector>
#include <string>

typedef void (*MessageHandler)(std::string str) ;
class MessageQueue{
    private:
        std::queue<std::string> _queue;
        std::vector<MessageHandler> _handlers;

    public:
        MessageQueue();
        //Post messages by pushing them into queue
        void PostMessage(std::string);
        //Push into handlers
        void RegisterHandler(MessageHandler);

        friend void* MessageHand(void* par);
        //Notifies all functions
        friend void* MessageBroadcaster(void* par);
};
