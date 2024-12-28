#ifndef ENTITIES_RIDE_H
#define ENTITIES_RIDE_H

#include <ctime>  // For timestamp handling
#include <string>
#include <vector>

class User;
class Driver;
class Coordinate;
class Site;
class MapGraph;

#include "Misc.h"
// Ride class
class Ride {
   private:
    int rideId;
    std::shared_ptr<Driver> driver;
    std::shared_ptr<Site> startLocation;
    using UserEndLocation = std::pair<std::shared_ptr<User>, std::shared_ptr<Site>>;
    std::vector<UserEndLocation> userEndLocationID;
    std::time_t timestamp;  // Stores the time of the ride
    double fare;
    Rating driverRating;

   public:
    // Constructor
    Ride(int rideId, std::shared_ptr<Site> startLocation, std::time_t timestamp, double fare);

    // Getters
    int getRideId() const;
    std::shared_ptr<Driver> getDriver() const;
    std::shared_ptr<Site> getStartLocation() const;
    std::shared_ptr<Site> getEndLocation(int userId) const;
    std::time_t getTimestamp() const;
    double getFare() const;

    // Setters
    void setDriver(const std::shared_ptr<Driver> driver);

    void addStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation);
    void removeStop(std::shared_ptr<User> user, const std::shared_ptr<Site> endLocation);

    // function to check if driver is assigned or not
    bool IsAssigned();

    // Function to display ride information
    void displayInfo() const;
};

#endif  // RIDE_H
