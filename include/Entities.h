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

class Passenger: public Person {
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

class Driver: public Person {
public:
    Driver();
    Driver(string name, string email, string password, string carModel, string carPlate);
    string getCarModel();
    string getCarPlate();
    void setCarModel(string carModel);
    void setCarPlate(string carPlate);
};

class Ride {
public:
    Ride();
    Ride(string driverID, string passengerID, string origin, string destination, double price, double timeTaken, double distance);
    string getDriverName();
    string getDriverEmail();
    string getDriverCarModel();
    string getDriverCarPlate();
    string getPassengerName();
    string getPassengerEmail();
    string getOrigin();
    string getDestination();
    double getPrice();
    void setDriverName(string driverName);
    void setDriverEmail(string driverEmail);
    void setDriverCarModel(string driverCarModel);
    void setDriverCarPlate(string driverCarPlate);
    void setPassengerName(string passengerName);
    void setPassengerEmail(string passengerEmail);
    void setOrigin(string origin);
    void setDestination(string destination);
    void setPrice(double price);
};

//ALI CHETI KAR SARAIKI JAYE