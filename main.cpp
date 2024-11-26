#include <ctime>
#include <iostream>

#include "Entities.h"
#include "Structures.h"

int main() {
    // Create a PersonRepository
    PersonRepository personRepo;

    // Create Users
    User* user1 = new User(1, "John Doe", "john@example.com", "123-456-7890", "password123");
    User* user2 = new User(2, "Jane Smith", "jane@example.com", "098-765-4321", "password456");

    // Add Users to the repository
    personRepo.addUser(user1);
    personRepo.addUser(user2);

    // Create Drivers
    Driver* driver1 = new Driver(1, "Alice Johnson", "alice@example.com", "555-555-5555", "password789", "Toyota Prius");
    Driver* driver2 = new Driver(2, "Bob Brown", "bob@example.com", "444-444-4444", "password101", "Honda Accord");

    // Add Drivers to the repository
    personRepo.addDriver(driver1);
    personRepo.addDriver(driver2);

    // Create Rides
    std::time_t now = std::time(0);
    Ride ride1(1, user1->getId(), driver1->getId(), "123 Main St", "456 Elm St", now, 15.50);
    Ride ride2(2, user2->getId(), driver2->getId(), "789 Oak St", "321 Pine St", now, 20.75);

    // Add Rides to Users' and Drivers' ride histories
    user1->addRideToHistory(ride1);
    driver1->addRideToHistory(ride1);

    user2->addRideToHistory(ride2);
    driver2->addRideToHistory(ride2);

    // Display User and Driver information
    std::cout << "User Information:" << std::endl;
    user1->displayInfo();
    std::cout << std::endl;
    user2->displayInfo();
    std::cout << std::endl;

    std::cout << "Driver Information:" << std::endl;
    driver1->displayInfo();
    std::cout << std::endl;
    driver2->displayInfo();
    std::cout << std::endl;

    // Display Ride details
    std::cout << "Ride Details:" << std::endl;
    ride1.printRideDetails();
    std::cout << std::endl;
    ride2.printRideDetails();
    std::cout << std::endl;

    // Clean up dynamically allocated memory
    delete user1;
    delete user2;
    delete driver1;
    delete driver2;

    return 0;
}