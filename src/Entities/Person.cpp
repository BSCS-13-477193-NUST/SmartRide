#include "Entities/Person.h"

#include <iostream>

#include "Entities/Person.h"
#include "Misc.h"

// Person class implementation
Person::Person(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password)
    : id(id), name(name), email(email), phone(phone), password(password), location(Coordinate(0, 0)) {}

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

std::string Person::getPassword() const {
    return password;
}

Coordinate Person::getLocation() const {
    return location;
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

void Person::setPassword(const std::string& password) {
    this->password = password;
}

void Person::setLocation(double x, double y) {
    location = Coordinate(x, y);
}

bool Person::verifyPassword(const std::string& password) const {
    return this->password == password;
}

// User class implementation
User::User(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, double x, double y)
    : Person(id, name, email, phone, password) {
    location = Coordinate(x, y);
}

void User::displayInfo() const {
    std::cout << "=== User Information ===" << std::endl;
    std::cout << "🆔 User ID: " << getId() << std::endl;
    std::cout << "👤 Name: " << getName() << std::endl;
    std::cout << "📧 Email: " << getEmail() << std::endl;
    std::cout << "📞 Phone: " << getPhone() << std::endl;
    std::cout << "📍 Location: (" << location.getX() << ", " << location.getY() << ")" << std::endl;
    std::cout << "========================" << std::endl;
}

// Driver class implementation
Driver::Driver(int id, const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& vehicleDetails, double x, double y)
    : Person(id, name, email, phone, password), vehicleDetails(vehicleDetails), isAvailable(true) {
    location = Coordinate(x, y);
}

void Driver::setAvailability(bool available) {
    isAvailable = available;
}

bool Driver::getAvailability() const {
    return isAvailable;
}

std::string Driver::getVehicleDetails() const {
    return vehicleDetails;
}

void Driver::displayInfo() const {
    std::cout << "=== Driver Information ===" << std::endl;
    std::cout << "🆔 Driver ID: " << getId() << std::endl;
    std::cout << "👤 Name: " << getName() << std::endl;
    std::cout << "📧 Email: " << getEmail() << std::endl;
    std::cout << "📞 Phone: " << getPhone() << std::endl;
    std::cout << "🚗 Vehicle Details: " << vehicleDetails << std::endl;
    std::cout << "📍 Location: (" << location.getX() << ", " << location.getY() << ")" << std::endl;
    std::cout << "🟢 Status: " << (isAvailable ? "Available" : "Not Available") << std::endl;
    std::cout << "==========================" << std::endl;
}
