#include "Entities/Ride.h"

#include <iostream>

#include "Entities/Person.h"
#include "Structures/MapGraph.h"
#include "Structures/Ride.h"

// Ride class implementation
Ride::Ride(int rideId, std::shared_ptr<Site> startLocation, std::time_t timestamp, double fare)
    : rideId(rideId), startLocation(startLocation), timestamp(timestamp), fare(fare) {}

int Ride::getRideId() const {
    return rideId;
}

std::shared_ptr<Driver> Ride::getDriver() const {
    return driver;
}

std::shared_ptr<Site> Ride::getStartLocation() const {
    return startLocation;
}

std::shared_ptr<Site> Ride::getEndLocation(int userId) const {
    for (const auto& userEndLocation : userEndLocationID) {
        if (userEndLocation.first->getId() == userId) {
            return userEndLocation.second;
        }
    }
    return nullptr;
}

std::time_t Ride::getTimestamp() const {
    return timestamp;
}

double Ride::getFare() const {
    return fare;
}

void Ride::setDriver(const std::shared_ptr<Driver> driver) {
    this->driver = driver;
}

void Ride::addStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation) {
    userEndLocationID.push_back(std::make_pair(user, endLocation));
}

void Ride::removeStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation) {
    for (auto it = userEndLocationID.rbegin(); it != userEndLocationID.rend(); ++it) {
        if (it->first == user && it->second == endLocation) {
            userEndLocationID.erase(std::next(it).base());
            return;
        }
    }
}

bool Ride::IsAssigned() {
    return driver != nullptr;
}

void Ride::displayInfo() const {
    std::cout << "Ride ID: " << rideId << std::endl;
    std::cout << "Start Location: " << startLocation->getName() << std::endl;
    std::cout << "Timestamp: " << std::asctime(std::localtime(&timestamp));
    std::cout << "Fare: " << fare << std::endl;
    if (driver) {
        std::cout << "Driver: " << driver->getName() << std::endl;
    } else {
        std::cout << "Driver: Not assigned" << std::endl;
    }
    std::cout << "Passengers:" << std::endl;
    for (const auto& userEndLocation : userEndLocationID) {
        std::cout << " - " << userEndLocation.first->getName() << " to " << userEndLocation.second->getName() << std::endl;
    }
}