#ifndef ENTITIES_RIDE_H
#define ENTITIES_RIDE_H

#include <ctime>  // For timestamp handling
#include <string>

typedef enum Rating {
    POOR = 1,
    AVERAGE = 2,
    GOOD = 3,
    VERY_GOOD = 4,
    EXCELLENT = 5
} Rating;

// Ride class
class Ride {
   private:
    int rideId;
    int userId;
    int driverId;
    std::string startLocation;
    std::string endLocation;
    std::time_t timestamp;  // Stores the time of the ride
    double fare;
    Rating driverRating;

   public:
    // Constructor
    Ride(int rideId, int userId, int driverId, const std::string& startLocation, const std::string& endLocation, std::time_t timestamp, double fare);

    // Getters
    int getRideId() const;
    int getUserId() const;
    int getDriverId() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;
    std::time_t getTimestamp() const;
    double getFare() const;

    // Print ride details
    void printRideDetails() const;
};

#endif  // RIDE_H
