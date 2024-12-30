#ifndef ENTITIES_PERSON_H
#define ENTITIES_PERSON_H

#include <string>

class Coordinate;

#include "Entities/Ride.h"
#include "Misc.h"
#include "Structures/MapGraph.h"
#include "Structures/Person.h"
#include "Structures/Ride.h"

// Base class Person
class Person {
   protected:
    int id;
    std::string name;
    std::string email;
    std::string phone;
    std::string password;          // For simplicity, password is stored as plain text; in practice, it should be hashed.
    Coordinate location = {0, 0};  // Current location (latitude, longitude)

   public:
    // Constructor
    Person(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password);

    // Destructor
    virtual ~Person();

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getPassword() const;
    Coordinate getLocation() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setPassword(const std::string& password);
    void setLocation(double x, double y);

    // Password verification
    bool verifyPassword(const std::string& password) const;

    // Virtual methods
    virtual void displayInfo() const = 0;  // Pure virtual method for polymorphism
};

// Derived class User
class User : public Person {
   private:
   public:
    // Constructor
    User(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, double x, double y);

    // Overriding displayInfo
    void displayInfo() const override;

    // Getters
};

// Derived class Driver
class Driver : public Person {
   private:
    std::string vehicleDetails;  // Information about the vehicle
    bool isAvailable;            // Availability status

   public:
    // Constructor
    Driver(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& vehicleDetails, double x, double y);

    // Location and availability operations
    void setAvailability(bool available);
    bool getAvailability() const;
    std::string getVehicleDetails() const;
    // Overriding displayInfo
    void
    displayInfo() const override;
};

#endif  // PERSON_H
