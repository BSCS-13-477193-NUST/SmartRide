
#include <queue>
#include "Structures.h"


// RideHistory class implementation
void Ride::setDriver(int driverId){
        this->driverId = driverId;
    }

bool Ride::IsAssigned(){
        return driverId != 0;
    }
    
RideHistory::RideHistory(int userId) : userId(userId), head(nullptr), tail(nullptr) {}

RideHistory::~RideHistory() {
    RideNode* current = head;
    while (current) {
        RideNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void RideHistory::addRide(const Ride& ride) {
    RideNode* newNode = new RideNode(ride);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void RideHistory::printAllRidesForward() const {
    RideNode* current = head;
    while (current) {
        current->ride.printRideDetails();
        std::cout << "-------------------\n";
        current = current->next;
    }
}

void RideHistory::printAllRidesBackward() const {
    RideNode* current = tail;
    while (current) {
        current->ride.printRideDetails();
        std::cout << "-------------------\n";
        current = current->prev;
    }
}

Ride* RideHistory::findRideById(int rideId) {
    RideNode* current = head;
    while (current) {
        if (current->ride.getRideId() == rideId) {
            return &current->ride;
        }
        current = current->next;
    }
    return nullptr;
}

// RideWaitingQueue class implementation
RideWaitingQueue::RideWaitingQueue() {
    head = tail = nullptr;
    std::queue<Ride> rideWaitingQueue;
    
}

void RideWaitingQueue::addRide(const Ride& ride) {
    RideNode* newNode = new RideNode(ride);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

Ride* RideWaitingQueue::removeRide() {
    if (!head) {
        return nullptr;
    }
    RideNode* temp = head;
    Ride* ride = &head->ride;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    return ride;
}

void RideWaitingQueue::printAllRides() const {
    RideNode* current = head;
    while (current) {
        current->ride.printRideDetails();
        std::cout << "-------------------\n";
        current = current->next;
    }
}


Ride* RideWaitingQueue::findRideById(int rideId) {
    RideNode* current = head;
    while (current) {
        if (current->ride.getRideId() == rideId) {
            return &current->ride;
        }
        current = current->next;
    }
    return nullptr;
}
