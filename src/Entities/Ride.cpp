#include "Entities/Ride.h"

#include <iostream>

#include "Structures/Ride.h"

// Ride class implementation
Ride::Ride(int rideId, int userId, int driverId, const std::string& startLocation, const std::string& endLocation, std::time_t timestamp, double fare)
    : rideId(rideId), userId(userId), driverId(driverId), startLocation(startLocation), endLocation(endLocation), timestamp(timestamp), fare(fare) {}

int Ride::getRideId() const { return rideId; }
int Ride::getUserId() const { return userId; }
int Ride::getDriverId() const { return driverId; }
std::string Ride::getStartLocation() const { return startLocation; }
std::string Ride::getEndLocation() const { return endLocation; }
std::time_t Ride::getTimestamp() const { return timestamp; }
double Ride::getFare() const { return fare; }

void Ride::printRideDetails() const {
    std::cout << "Ride ID: " << rideId << "\n"
              << "User ID: " << userId << "\n"
              << "Driver ID: " << driverId << "\n"
              << "Start Location: " << startLocation << "\n"
              << "End Location: " << endLocation << "\n"
              << "Timestamp: " << timestamp << "\n"
              << "Fare: $" << fare << "\n";
}
