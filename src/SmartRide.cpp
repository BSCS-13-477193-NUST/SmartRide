#include "SmartRide.hpp"

#include "Entities.h"

#define TIME 13
#define TRAFFIC 1
#define DEMAND 1

SmartRide::SmartRide() {
    pricing = std::make_unique<DynamicRidePricing>();
    mapGraph = std::make_shared<MapGraph>();
    driverRepository = std::make_shared<DriverRepository>();
    userRepository = std::make_shared<UserRepository>();
    rideRepository = std::make_shared<RideRepository>(mapGraph, driverRepository);
    start();
}

SmartRide::~SmartRide() {}

void SmartRide::start() {
    std::cout << "🚗 Welcome to SmartRide! 🚗" << std::endl;
    while (true) {
        std::cout << "=============================" << std::endl;
        std::cout << "1️⃣  Login as user" << std::endl;
        std::cout << "2️⃣  Login as driver" << std::endl;
        std::cout << "3️⃣  Register as user" << std::endl;
        std::cout << "4️⃣  Register as driver" << std::endl;
        std::cout << "5️⃣  Exit" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "Please enter your choice: ";
        int choice;
        std::cin >> choice;
        std::shared_ptr<User> user;
        std::shared_ptr<Driver> driver;
        switch (choice) {
            case 1:
                user = loginUser();
                if (user) {
                    userInterface(user);
                } else {
                    std::cout << "❌ Invalid email or password. Please try again." << std::endl;
                }
                break;
            case 2:
                driver = loginDriver();
                if (driver) {
                    driverInterface(driver);
                } else {
                    std::cout << "❌ Invalid email or password. Please try again." << std::endl;
                }
                break;
            case 3:
                user = registerUser();
                if (user) {
                    userInterface(user);
                } else {
                    std::cout << "❌ User with this email already exists. Please try again." << std::endl;
                }
                break;
            case 4:
                driver = registerDriver();
                if (driver) {
                    driverInterface(driver);
                } else {
                    std::cout << "❌ Driver with this email already exists. Please try again." << std::endl;
                }
                break;
            case 5:
                std::cout << "👋 Goodbye!" << std::endl;
                return;
            default:
                std::cout << "❌ Invalid choice. Please try again." << std::endl;
        }
    }
}

std::shared_ptr<User> SmartRide::loginUser() {
    std::string email, password;
    std::cout << "📧 Enter email: ";
    std::cin >> email;
    std::cout << "🔑 Enter password: ";
    std::cin >> password;
    auto user = userRepository->getUserByEmail(email);
    if (user && user->getPassword() == password) {
        return user;
    }
    return nullptr;
}

std::shared_ptr<Driver> SmartRide::loginDriver() {
    std::string email, password;
    std::cout << "📧 Enter email: ";
    std::cin >> email;
    std::cout << "🔑 Enter password: ";
    std::cin >> password;
    auto driver = driverRepository->getDriverByEmail(email);
    if (driver && driver->getPassword() == password) {
        return driver;
    }
    return nullptr;
}

std::shared_ptr<User> SmartRide::registerUser() {
    std::string name, email, phone, password;
    int x, y;
    std::cout << "👤 Enter name: ";
    std::cin >> name;
    std::cout << "📧 Enter email: ";
    std::cin >> email;
    std::cout << "📞 Enter phone: ";
    std::cin >> phone;
    std::cout << "🔑 Enter password: ";
    std::cin >> password;
    std::cout << "📍 Enter X coordinate: ";
    std::cin >> x;
    std::cout << "📍 Enter Y coordinate: ";
    std::cin >> y;
    auto user = userRepository->addUser(name, email, phone, password, {x, y});
    userRepository->appendUserToFile("data/users.csv", user);
    return user;
}

std::shared_ptr<Driver> SmartRide::registerDriver() {
    std::string name, email, phone, password, vehicleDetails;
    int x, y;
    std::cout << "👤 Enter name: ";
    std::cin >> name;
    std::cout << "📧 Enter email: ";
    std::cin >> email;
    std::cout << "📞 Enter phone: ";
    std::cin >> phone;
    std::cout << "🔑 Enter password: ";
    std::cin >> password;
    std::cout << "🚗 Enter vehicle details: ";
    std::cin >> vehicleDetails;
    std::cout << "📍 Enter X coordinate: ";
    std::cin >> x;
    std::cout << "📍 Enter Y coordinate: ";
    std::cin >> y;
    driverRepository->addDriver(name, email, phone, password, vehicleDetails, {x, y});
    auto driver = driverRepository->getDriverByEmail(email);
    driverRepository->appendDriverToFile("data/drivers.csv", driver);
    return driver;
}

void SmartRide::logout() {
    std::cout << "✅ Logged out successfully." << std::endl;
}

void SmartRide::userInterface(std::shared_ptr<User> user) {
    while (true) {
        std::cout << std::endl;
        std::cout << "👤 Welcome, " << user->getName() << "!" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "1️⃣  Request a ride" << std::endl;
        std::cout << "2️⃣  View ride history" << std::endl;
        std::cout << "3️⃣  Rate last driver" << std::endl;
        std::cout << "4️⃣  Logout" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "Please enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                requestRide(user);
                break;
            case 2:
                viewRideHistory(user);
                break;
            case 3:
                ratelastDriver(user);
                break;
            case 4:
                logout();
                return;
            default:
                std::cout << "❌ Invalid choice. Please try again." << std::endl;
        }
    }
}

void SmartRide::driverInterface(std::shared_ptr<Driver> driver) {
    while (true) {
        std::cout << std::endl;
        std::cout << "🚗 Welcome, " << driver->getName() << "!" << std::endl;
        std::cout
            << "=============================" << std::endl;
        std::cout << "1️⃣  Pick a ride" << std::endl;
        std::cout << "2️⃣  End ride" << std::endl;
        std::cout << "3️⃣  View Ride Requests" << std::endl;
        std::cout << "4️⃣  Show my rating" << std::endl;
        std::cout << "5️⃣  Logout" << std::endl;
        std::cout << "Please enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                pickRide(driver);
                break;
            case 2:
                endRideDriver(driver);
                break;
            case 3:
                viewRideRequests(driver);
                break;
            case 4:
                showMyRating(driver);
                break;
            case 5:
                return;
            default:
                std::cout << "❌ Invalid choice. Please try again." << std::endl;
        }
    }
}

void SmartRide::requestRide(std::shared_ptr<User> user) {
    std::cout << std::endl;
    std::cout << "🚗 Request a ride" << std::endl;
    // Ask for current location
    std::cout << "📍 Select your current location:" << std::endl;
    auto locations = mapGraph->getSites();
    for (const auto& location : locations) {
        std::cout << location->getId() << ". " << location->getName() << std::endl;
    }
    int locationId;
    std::cout << "📍 Enter location ID: ";
    std::cin >> locationId;
    auto currentLocation = mapGraph->getSiteByID(locationId);
    if (!currentLocation) {
        std::cout << "❌ Invalid location. Please try again." << std::endl;
        return;
    }

    // Ask for stops in between
    for (const auto& location : locations) {
        std::cout << location->getId() << ". " << location->getName() << std::endl;
    }

    std::vector<Ride::UserStops> usersStops;  // Mapping of user ID to stops
    std::vector<std::shared_ptr<Site>> userStops;
    while (true) {
        std::cout << "📍 Enter stop location ID (-1 to finish): ";
        int stopId;
        std::cin >> stopId;
        if (stopId == -1) {
            break;
        }
        auto stop = mapGraph->getSiteByID(stopId);
        if (!stop) {
            std::cout << "❌ Invalid location. Please try again." << std::endl;
            continue;
        }
        userStops.push_back(stop);
    }

    // Ask for destination
    std::cout << "📍 Select your destination:" << std::endl;
    for (const auto& location : locations) {
        std::cout << location->getId() << ". " << location->getName() << std::endl;
    }
    int destinationId;
    std::cout << "📍 Enter destination ID: ";
    std::cin >> destinationId;
    auto destination = mapGraph->getSiteByID(destinationId);
    if (!destination) {
        std::cout << "❌ Invalid location. Please try again." << std::endl;
        return;
    }
    userStops.push_back(destination);
    usersStops.push_back({user, userStops});

    // Ask for car pooling
    std::cout << "🚗 Do you want to carpool? (y/n)" << std::endl
              << "Note: Carpooling is only available for rides with 2 users." << std::endl;
    char choice;
    std::cin >> choice;
    if (choice == 'y') {
        std::cout << "👤 Enter the email of the user you want to carpool with: ";
        std::string email;
        std::cin >> email;
        auto user2 = userRepository->getUserByEmail(email);
        if (!user2) {
            std::cout << "❌ User not found. Please try again." << std::endl;
            return;
        }
        std::vector<std::shared_ptr<Site>> userStops2;
        for (const auto& location : locations) {
            std::cout << location->getId() << ". " << location->getName() << std::endl;
        }
        while (true) {
            std::cout << "📍 Enter stop location ID (-1 to finish): ";
            int stopId;
            std::cin >> stopId;
            if (stopId == -1) {
                break;
            }
            auto stop = mapGraph->getSiteByID(stopId);
            if (!stop) {
                std::cout << "❌ Invalid location. Please try again." << std::endl;
                continue;
            }
            userStops2.push_back(stop);
        }
        userStops2.push_back(destination);
        usersStops.push_back({user2, userStops2});
    }

    // add ride to queue
    auto ride = rideRepository->addRideToQueue(currentLocation, TIME, usersStops);
    ride->displayInfo();
    std::cout << "✅ Ride request added to queue." << std::endl;
}

void SmartRide::viewRideHistory(std::shared_ptr<User> user) {
    std::cout << std::endl;
    std::cout << "🚗 Ride History" << std::endl;
    auto rideHistory = rideRepository->getRideHistory(user);
    rideHistory->printAllRidesForward();
}

void SmartRide::ratelastDriver(std::shared_ptr<User> user) {
    std::cout << std::endl;
    auto ride = rideRepository->getLastRide(user);
    if (!ride) {
        std::cout << "❌ No rides to rate." << std::endl;
        return;
    }
    std::cout << "🚗 Rate your last driver (1-5): ";
    int rating;
    std::cin >> rating;
    if (rating < 1 || rating > 5) {
        std::cout << "❌ Invalid rating. Please try again." << std::endl;
        return;
    }
    driverRepository->rateDriver(ride->getDriver(), rating);
    std::cout << "✅ Driver rated successfully." << std::endl;
}

void SmartRide::pickRide(std::shared_ptr<Driver> driver) {
    std::cout << std::endl;
    if (!driver->getAvailability()) {
        std::cout << "❌ You are already on a ride." << std::endl;
        return;
    }
    RideWaitingQueue waitingRides;
    auto _waitingRide = rideRepository->getWaitingRides();
    auto temp = _waitingRide->topRide();
    while (temp) {
        auto _driver = rideRepository->getDriverForRide(temp);
        if (_driver && _driver->getId() == driver->getId()) {
            std::cout << "🚗 Ride request available. Do you want to accept it? (y/n)" << std::endl;
            char choice;
            std::cin >> choice;
            _waitingRide->popRide();
            if (choice == 'y') {
                acceptRideRequest(driver, temp);
                std::cout << "✅ Ride request accepted." << std::endl;

                while (_waitingRide->topRide()) {
                    waitingRides.addRide(_waitingRide->topRide());
                    _waitingRide->popRide();
                }
                while (waitingRides.topRide()) {
                    _waitingRide->addRide(waitingRides.topRide());
                    waitingRides.popRide();
                }
                return;
            } else {
                waitingRides.addRide(temp);
                temp = _waitingRide->topRide();
            }
        } else {
            waitingRides.addRide(temp);
            _waitingRide->popRide();
            temp = _waitingRide->topRide();
        }
    }
    while (_waitingRide->topRide()) {
        waitingRides.addRide(_waitingRide->topRide());
        _waitingRide->popRide();
    }
    while (waitingRides.topRide()) {
        _waitingRide->addRide(waitingRides.topRide());
        waitingRides.popRide();
    }
    std::cout << "❌ No ride requests available." << std::endl;
}

void SmartRide::acceptRideRequest(std::shared_ptr<Driver> driver, std::shared_ptr<Ride> ride) {
    std::cout << std::endl;
    ride->setDriver(driver);
    rideRepository->setCurrentRide(driver, ride);
    driver->setAvailability(false);
    std::cout << "🚗 Pick up ";
    for (const auto& stop : ride->getUsersStops()) {
        std::cout << stop.first->getName() << " ";
    }
    std::cout << "at " << ride->getStartLocation()->getName() << " at " << TIME << std::endl;

    auto current = ride->getStartLocation();
    int distance = 0;
    for (const auto& stop : ride->getFinalStops()) {
        auto path = mapGraph->shortestPath(current, stop.second);
        distance += path.second;
        while (!path.first.empty()) {
            std::cout << "➡️  Go to " << path.first.top()->getName() << std::endl;
            path.first.pop();
        }
        std::cout << "🚗 Drop off " << stop.first->getName() << " at " << current->getName() << std::endl;

        current = stop.second;
    }
    for (const auto& stop : ride->getUsersStops()) {
        std::cout << "💰 Fare for " << stop.first->getName() << ": " << ride->getFare(stop.first) << std::endl;
    }
}

void SmartRide::endRideDriver(std::shared_ptr<Driver> driver) {
    std::cout << std::endl;
    auto ride = rideRepository->getCurrentRide(driver);
    if (!ride) {
        std::cout << "❌ No ride to end." << std::endl;
        return;
    }
    std::cout << "🚗 Ending ride..." << std::endl;
    rideRepository->completeRide(ride->getUsersStops(), ride);
    std::cout << "✅ Ride ended." << std::endl;
}

void SmartRide::viewRideRequests(std::shared_ptr<Driver> driver) {
    std::cout << std::endl;
    std::cout << "🚗 Ride Requests" << std::endl;
    auto waitingRides = rideRepository->getWaitingRides();
    waitingRides->printAllRides();
}

void SmartRide::showMyRating(std::shared_ptr<Driver> driver) {
    std::cout << "🚗 Your rating: " << driverRepository->getAverageRating(driver) << std::endl;
}