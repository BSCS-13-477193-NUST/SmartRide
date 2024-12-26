#ifndef ENTITIES_RIDE_H
#define ENTITIES_RIDE_H
#define SIZE 5 // No of users that can be accomodated for carpooling

#include <ctime>  // For timestamp handling
#include <string>
#include <vector>

// Ride class
class Ride {
   private:
    int rideId;
    int userId[SIZE];
    int driverId;
    std::string startLocation;
    std::vector<int> endLocation;
    std::time_t timestamp;  // Stores the time of the ride
    double fare;

   public:
    // Constructor
    Ride(int rideId, int userId, const std::string& startLocation, const std::string& endLocation, std::time_t timestamp, double fare);

    // Getters
    int getRideId() const;
    int getUserId() const;
    int getDriverId() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;
    std::time_t getTimestamp() const;
    double getFare() const;

    // Setters
    void setDriver(int driverId);

    // function to check if driver is assigned or not
    bool IsAssigned();

    // Print ride details
    void printRideDetails() const;
};

#endif  // RIDE_H
