#include "Entities/Person.h"
#include <iostream>
using namespace std;

class Driver: public Person {
public:
    Driver();
    Driver(string name, string email, string password, string carModel, string carPlate);
    string getCarModel();
    string getCarPlate();
    void setCarModel(string carModel);
    void setCarPlate(string carPlate);
};