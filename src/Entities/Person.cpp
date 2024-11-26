#include "Entities/Person.h"

#include <iostream>

// Person class implementation
Person::Person(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password)
    : id(id), name(name), email(email), phone(phone), password(password) {}

Person::~Person() {}

int Person::getId() const {
    return id;
}

std::string Person::getName() const {
    return name;
}

std::string Person::getEmail() const {
    return email;
}

std::string Person::getPhone() const {
    return phone;
}

void Person::setName(const std::string& name) {
    this->name = name;
}

void Person::setEmail(const std::string& email) {
    this->email = email;
}

void Person::setPhone(const std::string& phone) {
    this->phone = phone;
}

// User class implementation
User::User(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password)
    : Person(id, name, email, phone, password), rideHistory(id) {}

void User::displayInfo() const {
    std::cout << "User Info:\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Phone: " << phone << "\n";
}

// Add a ride to the user's ride history
void User::addRideToHistory(const Ride& ride) {
    rideHistory.addRide(ride);
}

// Driver class implementation
Driver::Driver(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& vehicleDetails)
    : Person(id, name, email, phone, password), vehicleDetails(vehicleDetails), location({0.0, 0.0}), rating(0.0), isAvailable(true), rideHistory(id) {}

void Driver::updateLocation(double latitude, double longitude) {
    location = {latitude, longitude};
}

void Driver::setAvailability(bool available) {
    isAvailable = available;
}

bool Driver::getAvailability() const {
    return isAvailable;
}

void Driver::updateRating(double newRating) {
    // Simple average calculation for demonstration (extend as needed)
    rating = (rating + newRating) / 2;
}

double Driver::getRating() const {
    return rating;
}

void Driver::displayInfo() const {
    std::cout << "Driver Info:\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Phone: " << phone << "\n";
    std::cout << "Vehicle: " << vehicleDetails << "\n";
    std::cout << "Rating: " << rating << "\n";
    std::cout << "Availability: " << (isAvailable ? "Yes" : "No") << "\n";
}

// Add a ride to the driver's ride history
void Driver::addRideToHistory(const Ride& ride) {
    rideHistory.addRide(ride);
}
