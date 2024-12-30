#include "Entities/Ride.h"

#include <iostream>

#include "Entities/Person.h"
#include "Structures/MapGraph.h"
#include "Structures/Ride.h"

// Ride class implementation
Ride::Ride(int rideId, std::shared_ptr<Site> startLocation, int timestamp)
    : rideId(rideId), startLocation(startLocation), timestamp(timestamp) {}

int Ride::getRideId() const {
    return rideId;
}

std::shared_ptr<Driver> Ride::getDriver() const {
    return driver;
}

std::shared_ptr<Site> Ride::getStartLocation() const {
    return startLocation;
}

std::time_t Ride::getTimestamp() const {
    return timestamp;
}

double Ride::getFare(std::shared_ptr<User> user) const {
    return userFare.at(user->getId());
}

void Ride::setFare(std::shared_ptr<User> user, double fare) {
    userFare[user->getId()] = fare;
}

void Ride::setDriver(const std::shared_ptr<Driver> driver) {
    this->driver = driver;
}

void Ride::addStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation) {
    for (auto& userStops : usersStops) {
        if (userStops.first == user) {
            userStops.second.push_back(endLocation);
            return;
        }
    }
}

void Ride::removeStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation) {
    for (auto& userStops : usersStops) {
        if (userStops.first == user) {
            userStops.second.erase(std::remove(userStops.second.begin(), userStops.second.end(), endLocation), userStops.second.end());
            return;
        }
    }
}

void Ride::addUsersStops(std::vector<UserStops> usersStops) {
    this->usersStops = usersStops;
}

void Ride::removeUsersStops() {
    usersStops.clear();
}

std::vector<Ride::UserStops> Ride::getUsersStops() const {
    return usersStops;
}

void Ride::addFinalStop(std::shared_ptr<User> user, std::shared_ptr<Site> site) {
    finalStops.push_back({user, site});
}

std::vector<std::pair<std::shared_ptr<User>, std::shared_ptr<Site>>> Ride::getFinalStops() const {
    return finalStops;
}

bool Ride::IsAssigned() {
    return driver != nullptr;
}

void Ride::displayInfo() const {
    std::cout << "=== 🚗 Ride Information ===" << std::endl;
    std::cout << "🆔 Ride ID: " << rideId << std::endl;
    std::cout << "👨‍✈️ Driver: " << (driver ? driver->getName() : "Unassigned") << std::endl;
    std::cout << "📍 Start Location: " << startLocation->getName() << std::endl;
    std::cout << "⏰ Timestamp: " << std::asctime(std::localtime(&timestamp));
    std::cout << "=== 👥 Users and Stops ===" << std::endl;
    for (const auto& userStops : usersStops) {
        std::cout << "👤 User: " << userStops.first->getName() << std::endl;
        for (const auto& stop : userStops.second) {
            std::cout << "🛑 Stop: " << stop->getName() << std::endl;
        }
    }
    std::cout << "=== 💵 Fares ===" << std::endl;
    for (const auto& fare : userFare) {
        std::cout << "👤 User ID: " << fare.first << ", 💵 Fare: " << fare.second << std::endl;
    }
    std::cout << "==========================" << std::endl;
}