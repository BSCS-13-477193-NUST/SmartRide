#ifndef ENTITIES_RIDE_H
#define ENTITIES_RIDE_H

#include <ctime>  // For timestamp handling
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class User;
class Driver;
class Site;
class MapGraph;

#include "Misc.h"
// Ride class
class Ride {
   public:
    // Constructor
    using UserStops = std::pair<std::shared_ptr<User>, std::vector<std::shared_ptr<Site>>>;
    Ride(int rideId, std::shared_ptr<Site> startLocation, int timestamp);

    // Getters
    int getRideId() const;
    std::shared_ptr<Driver> getDriver() const;
    std::shared_ptr<Site> getStartLocation() const;
    std::time_t getTimestamp() const;
    double getFare(std::shared_ptr<User>) const;
    void setFare(std::shared_ptr<User>, double);

    // Setters
    void setDriver(const std::shared_ptr<Driver> driver);

    void addStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation);
    void removeStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation);
    void addUsersStops(std::vector<UserStops> usersStops);
    void removeUsersStops();
    std::vector<UserStops> getUsersStops() const;
    void addFinalStop(std::shared_ptr<User>, std::shared_ptr<Site>);
    std::vector<std::pair<std::shared_ptr<User>, std::shared_ptr<Site>>> getFinalStops() const;

    // function to check if driver is assigned or not
    bool IsAssigned();

    // Function to display ride information
    void displayInfo() const;

   private:
    int rideId;
    std::shared_ptr<Driver> driver;
    std::shared_ptr<Site> startLocation;
    std::vector<UserStops> usersStops;
    std::vector<std::pair<std::shared_ptr<User>, std::shared_ptr<Site>>> finalStops;
    std::time_t timestamp;  // Stores the time of the ride
    std::unordered_map<int, double> userFare;
    Rating driverRating;
};

#endif  // RIDE_H
