#ifndef STRUCTURES_PERSON_H
#define STRUCTURES_PERSON_H

#include <memory>         // For shared_ptr
#include <queue>          // For priority_queue
#include <unordered_map>  // For unordered_map

#include "Entities/Person.h"  // Include Person header
#include "Structures/MapGraph.h"

// Forward declarations
class User;
class Driver;

// Repository class for storing Users and Drivers
class UserRepository {
   private:
    std::unordered_map<int, std::shared_ptr<User>> users;  // Stores User objects by their IDs

   public:
    UserRepository();

    // Retrieve a user by ID
    std::shared_ptr<User> getUserById(int id) const;

    // Add a user to the repository
    std::shared_ptr<User> addUser(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, Coordinate location);
    std::shared_ptr<User> removeUser(std::shared_ptr<User> user);

    void saveUsersToFile(const std::string& filename) const;
    void loadUsersFromFile(const std::string& filename);
    void appendUserToFile(const std::string& filename, std::shared_ptr<User> user) const;
    std::shared_ptr<User> getUserByEmail(const std::string& email) const;

    // Destructor: Clean up dynamically allocated users and drivers
    ~UserRepository();
};

struct DriverRating {
    std::shared_ptr<Driver> driver;
    std::vector<Rating> ratings;

    DriverRating(std::shared_ptr<Driver> driver);

    double getAverageRating() const;

    bool operator<(const DriverRating& other) const;
};

struct DriverRatingComparator {
    bool operator()(const std::shared_ptr<DriverRating> lhs, const std::shared_ptr<DriverRating> rhs) const;
};

class DriverRepository {
   private:
    std::unordered_map<int, std::shared_ptr<Driver>> drivers;
    std::unordered_map<int, std::shared_ptr<DriverRating>> driverRatings;

    std::priority_queue<std::shared_ptr<DriverRating>, std::vector<std::shared_ptr<DriverRating>>, DriverRatingComparator> topDrivers;

   public:
    DriverRepository();
    std::shared_ptr<Driver> getDriverById(int id) const;
    void addDriver(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& vehicleDetails, Coordinate location);

    int getDriverCount() const;
    double getAverageRating(std::shared_ptr<Driver>) const;
    std::shared_ptr<Driver> getDriverByRank(int rank) const;
    std::shared_ptr<Driver> getTopDriver() const;
    std::queue<std::shared_ptr<Driver>> getTopDrivers(int count) const;
    void addRating(const std::shared_ptr<Driver>, Rating rating);
    void printTopDrivers() const;
    void rateDriver(std::shared_ptr<Driver> driver, int rating);

    void saveDriversToFile(const std::string& filename) const;
    void loadDriversFromFile(const std::string& filename);
    void appendDriverToFile(const std::string& filename, std::shared_ptr<Driver> user) const;
    std::shared_ptr<Driver> getDriverByEmail(const std::string& email) const;
};

#endif