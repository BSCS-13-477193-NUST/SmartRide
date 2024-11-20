#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class Person {
   public:
    Person();
    Person(string ID, string name, char gender, string phone);
    virtual string getName() = 0;
    virtual string getPhone() = 0;
    virtual void setName(string name) = 0;
    virtual void setPhone(string phone) = 0;

    string getID();
    char getGender();
    void setID(string ID);
    void setGender(char gender);
};

#endif  // PERSON_H