#ifndef ENTITIES_PERSON_H
#define ENTITIES_PERSON_H

#include <string>

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
    std::string password;  // For simplicity, password is stored as plain text; in practice, it should be hashed.

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

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setPassword(const std::string& password);

    // Password verification
    bool verifyPassword(const std::string& password) const;

    // Virtual methods
    virtual void displayInfo() const = 0;  // Pure virtual method for polymorphism
};

// Derived class User
class User : public Person {
   private:
    Coordinate location;  // Current location (latitude, longitude)
   public:
    // Constructor
    User(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, double x, double y);

    // Overriding displayInfo
    void displayInfo() const override;
};

// Derived class Driver
class Driver : public Person {
   private:
    std::string vehicleDetails;  // Information about the vehicle
    Coordinate location;         // Current location (latitude, longitude)
    bool isAvailable;            // Availability status

   public:
    // Constructor
    Driver(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& vehicleDetails, double x, double y);

    // Location and availability operations
    void updateLocation(double x, double y);
    void setAvailability(bool available);
    bool getAvailability() const;
    Coordinate getLocation() const;

    // Overriding displayInfo
    void displayInfo() const override;
};

#endif  // PERSON_H
