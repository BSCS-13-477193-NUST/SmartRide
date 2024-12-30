
#include "Structures/Ride.h"

#include <memory>
#include <queue>
#include <unordered_map>

#include "Entities/Person.h"
#define TIME 13
#define TRAFFIC 1
#define DEMAND 1

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

std::shared_ptr<Ride> RideHistory::getLastRide() {
    if (tail == nullptr) {
        return nullptr;
    }
    return tail->ride;
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
        std::cout << std::endl;
        current->ride->displayInfo();
        current = current->next;
    }
}

int RideWaitingQueue::getRideCount() const {
    int count = 0;
    RideNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
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

RideRepository::RideRepository(std::shared_ptr<MapGraph> mapGraph, std::shared_ptr<DriverRepository> driverRepository)
    : mapGraph(mapGraph), driverRepository(driverRepository) {
    waitingRides = std::make_shared<RideWaitingQueue>();
    rideHistory = std::unordered_map<int, std::shared_ptr<RideHistory>>();
    currentRide = std::unordered_map<int, std::shared_ptr<Ride>>();
    pricing = std::make_shared<DynamicRidePricing>();
}

RideRepository::~RideRepository() {}

std::shared_ptr<Ride> RideRepository::addRideToQueue(std::shared_ptr<Site> startLocation, int timestamp, std::vector<Ride::UserStops> usersStops) {
    int rideCount = waitingRides->getRideCount();
    std::shared_ptr<Ride> ride = std::make_shared<Ride>(rideCount + 1, startLocation, timestamp);
    ride->addUsersStops(usersStops);
    mergeUsersStops(ride, usersStops);
    waitingRides->addRide(ride);
    setRideFares(ride);
    return ride;
}

void RideRepository::popRide() {
    waitingRides->popRide();
}

void RideRepository::cancelRide(std::shared_ptr<Ride> ride) {
    waitingRides->removeRideById(ride->getRideId());
}

void RideRepository::completeRide(std::vector<Ride::UserStops> usersStops, std::shared_ptr<Ride> ride) {
    for (const auto& stop : usersStops) {
        if (rideHistory.find(stop.first->getId()) == rideHistory.end()) {
            rideHistory[stop.first->getId()] = std::make_shared<RideHistory>(stop.first);
        }
        rideHistory.at(stop.first->getId())->addRide(ride);
    }
    if (ride->IsAssigned()) {
        ride->getDriver()->setAvailability(true);
    }
    currentRide.erase(ride->getDriver()->getId());
}

std::shared_ptr<RideWaitingQueue> RideRepository::getWaitingRides() const {
    return waitingRides;
}

std::shared_ptr<Ride> RideRepository::topRide() {
    return waitingRides->topRide();
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

std::shared_ptr<Ride> RideRepository::getLastRide(std::shared_ptr<User> user) {
    if (rideHistory.find(user->getId()) == rideHistory.end()) {
        return nullptr;
    }
    return rideHistory.at(user->getId())->getLastRide();
}

std::shared_ptr<Driver> RideRepository::getDriverForRide(std::shared_ptr<Ride> ride) {
    using Node = std::pair<double, std::shared_ptr<Driver>>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    Coordinate startLocation = *ride->getStartLocation();
    std::cout << driverRepository->getDriverCount() << std::endl;
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

void RideRepository::mergeUsersStops(std::shared_ptr<Ride> ride, std::vector<std::pair<std::shared_ptr<User>, std::vector<std::shared_ptr<Site>>>> usersStops) {
    auto queue = mapGraph->mergeStops(ride->getStartLocation(), usersStops);
    while (!queue.empty()) {
        auto user = queue.front().first;
        auto stop = queue.front().second;
        ride->addFinalStop(user, stop);
        queue.pop();
    }
}

void RideRepository::displayCurrentRide(std::shared_ptr<Driver> driver) const {
    if (currentRide.find(driver->getId()) == currentRide.end()) {
        std::cout << "No current ride assigned." << std::endl;
        return;
    }
    currentRide.at(driver->getId())->displayInfo();
}

void RideRepository::displayRideHistory(std::shared_ptr<User> user) const {
    if (rideHistory.find(user->getId()) == rideHistory.end()) {
        std::cout << "No ride history found." << std::endl;
        return;
    }
    rideHistory.at(user->getId())->printAllRidesForward();
}

void RideRepository::displayWaitingRides() const {
    waitingRides->printAllRides();
}

void RideRepository::setRideFares(std::shared_ptr<Ride> ride) {
    auto current = ride->getStartLocation();
    for (const auto& stop : ride->getUsersStops()) {
        int userDistance = 0;
        current = ride->getStartLocation();
        for (const auto& site : stop.second) {
            auto path = mapGraph->shortestPath(current, site);
            userDistance += path.second;
            current = site;
        }
        ride->setFare(stop.first, pricing->calculatePrice(TIME, TRAFFIC, DEMAND, userDistance));
    }
}