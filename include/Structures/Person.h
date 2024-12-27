#ifndef STRUCTURES_PERSON_H
#define STRUCTURES_PERSON_H

#include <unordered_map>  // For unordered_map

#include "Entities/Person.h"  // Include Person header

// Forward declarations
class User;
class Driver;

// Repository class for storing Users and Drivers
class PersonRepository {
   private:
    std::unordered_map<int, User*> users;      // Stores User objects by their IDs
    std::unordered_map<int, Driver*> drivers;  // Stores Driver objects by their IDs

   public:
    // Add a user to the repository
    void addUser(User* user);

    // Add a driver to the repository
    void addDriver(Driver* driver);

    // Retrieve a user by ID
    User* getUserById(int id) const;

    // Retrieve a driver by ID
    Driver* getDriverById(int id) const;

    void saveUsersToFile(const std::string& filename) const;
    void loadUsersFromFile(const std::string& filename);

    // Destructor: Clean up dynamically allocated users and drivers
    ~PersonRepository();
};

#endif