#include "person.h"

void Person::setAge(int theAge) {
    this->age = theAge;
}
int Person::getAge() {
    return this->age;
}

const char* Person::getName() {
    return this->name;
}

void Person::setName(const char* theName) {
    this->name = theName;
}

//singleton init on demand
Person* Person::instance = 0;

Person* Person::getInstance() {
    if (instance == 0) {
        //create new memory segment
        int shm_id = shmget(IPC_PRIVATE, sizeof(Person), IPC_CREAT | 0666);
        if (shm_id == -1) {
            LogError("Cannot get shared memory");
        }

        //attach shared memory by ID to the current process 
        void* shared_mem = shmat(shm_id, 0, 0);
        if (shared_mem == (void*)-1) {
            LogError("Cannot map shared memory");
        }

        //shared instance
        instance = (Person*)shared_mem;
    }
    return instance;
}

Person::~Person() {
    delete instance;
    shmdt(instance);
}
    
void Person::LogError (const char* message) {
    std::cerr<< getpid() << " - Error: " << message << strerror(errno) << std::endl;
}