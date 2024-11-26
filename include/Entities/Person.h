#ifndef ENTITIES_PERSON_H
#define ENTITIES_PERSON_H

#include <string>

#include "Entities/Ride.h"  // Include RideHistory header
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

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);

    // Virtual methods
    virtual void displayInfo() const = 0;  // Pure virtual method for polymorphism
};

// Derived class User
class User : public Person {
   private:
    RideHistory rideHistory;  // User's ride history

   public:
    // Constructor
    User(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password);

    // Overriding displayInfo
    void displayInfo() const override;

    // Add a ride to the user's history
    void addRideToHistory(const Ride& ride);
};

// Derived class Driver
class Driver : public Person {
   private:
    std::string vehicleDetails;          // Information about the vehicle
    std::pair<double, double> location;  // Current location (latitude, longitude)
    double rating;                       // Average rating
    bool isAvailable;                    // Availability status
    RideHistory rideHistory;             // Driver's ride history

   public:
    // Constructor
    Driver(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& vehicleDetails);

    // Location and availability operations
    void updateLocation(double latitude, double longitude);
    void setAvailability(bool available);
    bool getAvailability() const;

    // Rating operations
    void updateRating(double newRating);
    double getRating() const;

    // Overriding displayInfo
    void displayInfo() const override;

    // Add a ride to the driver's history
    void addRideToHistory(const Ride& ride);
};

#endif  // PERSON_H
