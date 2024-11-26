#ifndef STRUCTURES_RIDE_H
#define STRUCTURES_RIDE_H
#include "Entities/Ride.h"

// Node class for doubly linked list
struct RideNode {
    Ride ride;
    RideNode* prev;
    RideNode* next;

    RideNode(const Ride& ride) : ride(ride), prev(nullptr), next(nullptr) {}
};

// RideHistory class
class RideHistory {
   private:
    int userId;      // The ID of the user whose ride history this is
    RideNode* head;  // Pointer to the first ride
    RideNode* tail;  // Pointer to the last ride

   public:
    // Constructor
    RideHistory(int userId);

    // Destructor
    ~RideHistory();

    // Add a new ride
    void addRide(const Ride& ride);

    // Retrieve all rides (forward)
    void printAllRidesForward() const;

    // Retrieve all rides (backward)
    void printAllRidesBackward() const;

    // Search for a ride by ride ID
    Ride* findRideById(int rideId);
};

#endif  // STRUCTURES_RIDE_H