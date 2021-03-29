#ifndef person_h
#define person_h

class Person {
    private:
        static int shm_id;
        int age;
        const char* name;
        // for storing the instance
        static Person* instance;
        // private constructor to prevent additional instances
        Person();
        ~Person();
        // private copy constructor
        Person(const Person&);
        // private = operator
        Person& operator=(const Person&);
    public:
        static Person* getInstance();
        void setAge(int theAge);
        int getAge();
        void setName(const char* theName);
        const char* getName();
        static void LogError (const char*);
};
#endif