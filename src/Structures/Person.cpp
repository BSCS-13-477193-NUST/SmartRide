#include "Structures/Person.h"

#include "csv.hpp"
#include "csvWriter.h"

UserRepository::UserRepository() {
    users = std::unordered_map<int, std::shared_ptr<User>>();
}

UserRepository::~UserRepository() {
}

std::shared_ptr<User> UserRepository::getUserById(int id) const {
    return users.at(id);
}

std::shared_ptr<User> UserRepository::addUser(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, Coordinate location) {
    std::shared_ptr<User> user = std::make_shared<User>(users.size() + 1, name, email, phone, password, location.getX(), location.getY());
    users[user->getId()] = user;
    return user;
}

std::shared_ptr<User> UserRepository::removeUser(std::shared_ptr<User> user) {
    users.erase(user->getId());
    return user;
}

void UserRepository::saveUsersToFile(const std::string& filename) const {
    std::ofstream file(filename);
    CSVWriter csv(",", 5);
    csv << "ID" << "Name" << "Email" << "Phone" << "Password";

    for (const auto& pair : users) {
        const std::shared_ptr<User>& user = pair.second;
        csv.newRow() << user->getId() << user->getName() << user->getEmail() << user->getPhone() << user->getPassword();
    }

    file << csv << std::endl;
    file.close();
}

void UserRepository::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    csv::CSVReader reader(file);

    for (csv::CSVRow& row : reader) {
        try {
            int id = row["ID"].get<int>();
            std::string name = row["Name"].get<std::string>();
            std::string email = row["Email"].get<std::string>();
            std::string phone = row["Phone"].get<std::string>();
            std::string password = row["Password"].get<std::string>();
            addUser(name, email, phone, password, {0, 0});
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
    }
}

DriverRating::DriverRating(std::shared_ptr<Driver> driver) : driver(driver) {
    ratings = std::vector<Rating>();
}

double DriverRating::getAverageRating() const {
    if (ratings.empty()) {
        return 0;
    }

    double sum = 0;
    for (const Rating& rating : ratings) {
        sum += rating;
    }

    return sum / ratings.size();
}

bool DriverRating::operator<(const DriverRating& other) const {
    return getAverageRating() < other.getAverageRating();
}

bool DriverRatingComparator::operator()(const std::shared_ptr<DriverRating> lhs, const std::shared_ptr<DriverRating> rhs) const {
    return *lhs < *rhs;
}

DriverRepository::DriverRepository() {
    drivers = std::unordered_map<int, std::shared_ptr<Driver>>();
    driverRatings = std::unordered_map<int, std::shared_ptr<DriverRating>>();
    topDrivers = std::priority_queue<std::shared_ptr<DriverRating>, std::vector<std::shared_ptr<DriverRating>>, DriverRatingComparator>();
}

std::shared_ptr<Driver> DriverRepository::getDriverById(int id) const {
    return drivers.at(id);
}

void DriverRepository::addDriver(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& vehicleDetails, Coordinate location) {
    std::shared_ptr<Driver> driver = std::make_shared<Driver>(drivers.size() + 1, name, email, phone, password, vehicleDetails, location.getX(), location.getY());
    drivers[driver->getId()] = driver;
    driverRatings[driver->getId()] = std::make_shared<DriverRating>(driver);
}

int DriverRepository::getDriverCount() const {
    return drivers.size();
}

double DriverRepository::getAverageRating(std::shared_ptr<Driver> driver) const {
    return driverRatings.at(driver->getId())->getAverageRating();
}

std::shared_ptr<Driver> DriverRepository::getDriverByRank(int rank) const {
    std::priority_queue<std::shared_ptr<DriverRating>, std::vector<std::shared_ptr<DriverRating>>, DriverRatingComparator> temp = topDrivers;
    for (int i = 0; i < rank - 1; i++) {
        temp.pop();
    }
    return temp.top()->driver;
}

std::shared_ptr<Driver> DriverRepository::getTopDriver() const {
    return topDrivers.top()->driver;
}

void DriverRepository::addRating(const std::shared_ptr<Driver> driver, Rating rating) {
    driverRatings.at(driver->getId())->ratings.push_back(rating);
    topDrivers.push(driverRatings.at(driver->getId()));
}

void DriverRepository::printTopDrivers() const {
    std::priority_queue<std::shared_ptr<DriverRating>, std::vector<std::shared_ptr<DriverRating>>, DriverRatingComparator> temp = topDrivers;
    int rank = 1;
    while (!temp.empty()) {
        std::shared_ptr<DriverRating> driverRating = temp.top();
        std::cout << "Rank " << rank << ": " << driverRating->driver->getName() << " - " << driverRating->getAverageRating() << std::endl;
        temp.pop();
        rank++;
    }
}

std::queue<std::shared_ptr<Driver>> DriverRepository::getTopDrivers(int count) const {
    std::queue<std::shared_ptr<Driver>> topDriversOut;
    std::priority_queue<std::shared_ptr<DriverRating>, std::vector<std::shared_ptr<DriverRating>>, DriverRatingComparator> temp = topDrivers;
    for (int i = 0; i < count; i++) {
        topDriversOut.push(temp.top()->driver);
        temp.pop();
    }
    return topDriversOut;
}