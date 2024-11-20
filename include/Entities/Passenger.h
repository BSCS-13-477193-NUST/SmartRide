#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

#include "Entities/Person.h"
using namespace std;

class Passenger : public Person {
   public:
    Passenger();
    Passenger(string name, string email, string password);
    string getName();
    string getEmail();
    string getPassword();
    void setName(string name);
    void setEmail(string email);
    void setPassword(string password);
};

#endif  // PASSENGER_H