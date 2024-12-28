#ifndef STRUCTURES_RIDE_H
#define STRUCTURES_RIDE_H
#include "Entities/Ride.h"
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
    std::shared_ptr<Ride> findRideById(int rideId);
    std::shared_ptr<Ride> removeRideById(int rideId);
};

class RideRepository {
   private:
    RideWaitingQueue waitingRides;
    std::unordered_map<int, std::shared_ptr<RideHistory>> rideHistory;  // Mapping of user ID to ride history
    std::unordered_map<int, std::shared_ptr<Ride>> currentRide;         // Mapping of driver ID to current ride
    std::shared_ptr<MapGraph> mapGraph;
    std::shared_ptr<DriverRepository> driverRepository;

   public:
    RideRepository(std::shared_ptr<MapGraph> mapGraph, std::shared_ptr<DriverRepository> driverRepository);
    ~RideRepository();

    void addRideToQueue(std::shared_ptr<Site> startLocation, std::time_t timestamp, double fare);
    std::shared_ptr<Ride> topRide();
    void popRide();
    void cancelRide(std::shared_ptr<Ride> ride);
    void completeRide(std::shared_ptr<User> user, std::shared_ptr<Ride> ride);

    std::shared_ptr<RideHistory> getRideHistory(std::shared_ptr<User> user);
    std::shared_ptr<Ride> getCurrentRide(std::shared_ptr<Driver> driver) const;
    void setCurrentRide(std::shared_ptr<Driver> driver, std::shared_ptr<Ride> ride);

    std::shared_ptr<Driver> getDriverForRide(std::shared_ptr<Ride> ride);
};
#endif  // STRUCTURES_RIDE_H