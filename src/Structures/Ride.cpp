

#include "Structures.h"
// RideHistory class implementation
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