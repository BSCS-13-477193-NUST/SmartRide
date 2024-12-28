
#include "Structures/Ride.h"

#include <queue>

#include "Entities/Person.h"

RideNode::RideNode(const std::shared_ptr<Ride> ride) : ride(ride), prev(nullptr), next(nullptr) {}

RideHistory::RideHistory(std::shared_ptr<User> user) : user(user), head(nullptr), tail(nullptr) {}

RideHistory::~RideHistory() {
    RideNode* current = head;
    while (current != nullptr) {
        RideNode* next = current->next;
        delete current;
        current = next;
    }
}

void RideHistory::addRide(const std::shared_ptr<Ride> ride) {
    RideNode* newNode = new RideNode(ride);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void RideHistory::printAllRidesForward() const {
    RideNode* current = head;
    while (current != nullptr) {
        current->ride->displayInfo();
        current = current->next;
    }
}

void RideHistory::printAllRidesBackward() const {
    RideNode* current = tail;
    while (current != nullptr) {
        current->ride->displayInfo();
        current = current->prev;
    }
}

std::shared_ptr<Ride> RideHistory::findRideById(int rideId) {
    RideNode* current = head;
    while (current != nullptr) {
        if (current->ride->getRideId() == rideId) {
            return current->ride;
        }
        current = current->next;
    }
    return nullptr;
}

RideWaitingQueue::RideWaitingQueue() : head(nullptr), tail(nullptr) {}

RideWaitingQueue::~RideWaitingQueue() {
    RideNode* current = head;
    while (current != nullptr) {
        RideNode* next = current->next;
        delete current;
        current = next;
    }
}

void RideWaitingQueue::addRide(const std::shared_ptr<Ride> ride) {
    RideNode* newNode = new RideNode(ride);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

std::shared_ptr<Ride> RideWaitingQueue::topRide() {
    if (head == nullptr) {
        return nullptr;
    }
    return head->ride;
}

void RideWaitingQueue::popRide() {
    if (head == nullptr) {
        return;
    }
    RideNode* next = head->next;
    delete head;
    head = next;
    if (head == nullptr) {
        tail = nullptr;
    }
}

void RideWaitingQueue::printAllRides() const {
    RideNode* current = head;
    while (current != nullptr) {
        current->ride->displayInfo();
        current = current->next;
    }
}

std::shared_ptr<Ride> RideWaitingQueue::findRideById(int rideId) {
    RideNode* current = head;
    while (current != nullptr) {
        if (current->ride->getRideId() == rideId) {
            return current->ride;
        }
        current = current->next;
    }
    return nullptr;
}

std::shared_ptr<Ride> RideWaitingQueue::removeRideById(int rideId) {
    RideNode* current = head;
    while (current != nullptr) {
        if (current->ride->getRideId() == rideId) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            std::shared_ptr<Ride> ride = current->ride;
            delete current;
            return ride;
        }
        current = current->next;
    }
    return nullptr;
}

RideRepository::RideRepository(std::shared_ptr<MapGraph> mapGraph, std::shared_ptr<DriverRepository> driverRepository) {
    waitingRides = RideWaitingQueue();
    rideHistory = std::unordered_map<int, std::shared_ptr<RideHistory>>();
    currentRide = std::unordered_map<int, std::shared_ptr<Ride>>();
    mapGraph = mapGraph;
    driverRepository = driverRepository;
}

RideRepository::~RideRepository() {}

void RideRepository::addRideToQueue(std::shared_ptr<Site> startLocation, std::time_t timestamp, double fare) {
    std::shared_ptr<Ride> ride = std::make_shared<Ride>(currentRide.size() + 1, startLocation, timestamp, fare);
    waitingRides.addRide(ride);
}

void RideRepository::popRide() {
    waitingRides.popRide();
}

void RideRepository::cancelRide(std::shared_ptr<Ride> ride) {
    waitingRides.removeRideById(ride->getRideId());
}

void RideRepository::completeRide(std::shared_ptr<User> user, std::shared_ptr<Ride> ride) {
    rideHistory.at(user->getId())->addRide(ride);
    currentRide.erase(ride->getDriver()->getId());
}

std::shared_ptr<Ride> RideRepository::topRide() {
    return waitingRides.topRide();
}

std::shared_ptr<RideHistory> RideRepository::getRideHistory(std::shared_ptr<User> user) {
    if (rideHistory.find(user->getId()) == rideHistory.end()) {
        rideHistory[user->getId()] = std::make_shared<RideHistory>(user);
    }
    return rideHistory.at(user->getId());
}

std::shared_ptr<Ride> RideRepository::getCurrentRide(std::shared_ptr<Driver> driver) const {
    if (currentRide.find(driver->getId()) == currentRide.end()) {
        return nullptr;
    }
    return currentRide.at(driver->getId());
}

void RideRepository::setCurrentRide(std::shared_ptr<Driver> driver, std::shared_ptr<Ride> ride) {
    currentRide[driver->getId()] = ride;
}

std::shared_ptr<Driver> RideRepository::getDriverForRide(std::shared_ptr<Ride> ride) {
    using Node = std::pair<double, std::shared_ptr<Driver>>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    Coordinate startLocation = *ride->getStartLocation();
    auto drivers = driverRepository->getTopDrivers(driverRepository->getDriverCount());

    while (!drivers.empty()) {
        auto driver = drivers.front();
        drivers.pop();
        auto driverLocation = driver->getLocation();
        double distance = mapGraph->getDistance(startLocation, driverLocation);
        pq.push({distance, driver});
    }
    while (!pq.empty()) {
        auto driver = pq.top().second;
        pq.pop();
        if (driver->getAvailability()) {
            return driver;
        }
    }
    return nullptr;
}