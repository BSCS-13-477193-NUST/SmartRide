#ifndef STRUCTURES_RIDE_H
#define STRUCTURES_RIDE_H
#include <iostream>

#include "Entities/Ride.h"
#include "Structures/DynamicRidePricing.h"
#include "Structures/Person.h"
class DriverRepository;

// Node class for doubly linked list
struct RideNode {
    std::shared_ptr<Ride> ride;
    RideNode* prev;
    RideNode* next;

    RideNode(const std::shared_ptr<Ride> ride);
};

// RideHistory class
class RideHistory {
   private:
    std::shared_ptr<User> user;  // The ID of the user whose ride history this is
    RideNode* head;              // Pointer to the first ride
    RideNode* tail;              // Pointer to the last ride

   public:
    // Constructor
    RideHistory(std::shared_ptr<User> user);

    // Destructor
    ~RideHistory();

    // Add a new ride
    void addRide(const std::shared_ptr<Ride> ride);

    std::shared_ptr<Ride> getLastRide();

    // Retrieve all rides (forward)
    void printAllRidesForward() const;

    // Retrieve all rides (backward)
    void printAllRidesBackward() const;

    // Search for a ride by ride ID
    std::shared_ptr<Ride> findRideById(int rideId);
};

class RideWaitingQueue {
   private:
    RideNode* head;
    RideNode* tail;

   public:
    RideWaitingQueue();
    ~RideWaitingQueue();

    void addRide(const std::shared_ptr<Ride> ride);
    std::shared_ptr<Ride> topRide();
    void popRide();
    void printAllRides() const;
    int getRideCount() const;
    std::shared_ptr<Ride> findRideById(int rideId);
    std::shared_ptr<Ride> removeRideById(int rideId);
};

class RideRepository {
   private:
    std::shared_ptr<RideWaitingQueue> waitingRides;
    std::unordered_map<int, std::shared_ptr<RideHistory>> rideHistory;  // Mapping of user ID to ride history
    std::unordered_map<int, std::shared_ptr<Ride>> currentRide;         // Mapping of driver ID to current ride
    std::shared_ptr<MapGraph> mapGraph;
    std::shared_ptr<DriverRepository> driverRepository;
    std::shared_ptr<DynamicRidePricing> pricing;

   public:
    RideRepository(std::shared_ptr<MapGraph> mapGraph, std::shared_ptr<DriverRepository> driverRepository);
    ~RideRepository();

    std::shared_ptr<Ride> addRideToQueue(std::shared_ptr<Site> startLocation, int timestamp, std::vector<Ride::UserStops> usersStops);

    std::shared_ptr<Ride> topRide();
    void popRide();
    void cancelRide(std::shared_ptr<Ride> ride);
    void completeRide(std::vector<Ride::UserStops> usersStops, std::shared_ptr<Ride> ride);
    std::shared_ptr<RideWaitingQueue> getWaitingRides() const;

    std::shared_ptr<RideHistory> getRideHistory(std::shared_ptr<User> user);
    std::shared_ptr<Ride> getCurrentRide(std::shared_ptr<Driver> driver) const;
    void setCurrentRide(std::shared_ptr<Driver> driver, std::shared_ptr<Ride> ride);
    std::shared_ptr<Ride> getLastRide(std::shared_ptr<User> user);

    std::shared_ptr<Driver> getDriverForRide(std::shared_ptr<Ride> ride);
    void mergeUsersStops(std::shared_ptr<Ride> ride, std::vector<std::pair<std::shared_ptr<User>, std::vector<std::shared_ptr<Site>>>> usersStops);

    void displayRideHistory(std::shared_ptr<User> user) const;
    void displayCurrentRide(std::shared_ptr<Driver> driver) const;
    void displayWaitingRides() const;

    void setRideFares(std::shared_ptr<Ride> ride);
};
#endif  // STRUCTURES_RIDE_H