#include "Structures/Person.h"

// Add a user to the repository
void PersonRepository::addUser(User* user) {
    users[user->getId()] = user;
}

// Add a driver to the repository
void PersonRepository::addDriver(Driver* driver) {
    drivers[driver->getId()] = driver;
}

// Retrieve a user by ID
User* PersonRepository::getUserById(int id) const {
    auto it = users.find(id);
    return it != users.end() ? it->second : nullptr;
}

// Retrieve a driver by ID
Driver* PersonRepository::getDriverById(int id) const {
    auto it = drivers.find(id);
    return it != drivers.end() ? it->second : nullptr;
}

// Destructor: Clean up dynamically allocated users and drivers
PersonRepository::~PersonRepository() {
    // Clean up dynamically allocated users and drivers
    for (auto& pair : users) {
        delete pair.second;
    }
    for (auto& pair : drivers) {
        delete pair.second;
    }
}
