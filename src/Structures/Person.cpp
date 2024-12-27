#include "Structures/Person.h"

#include "csv.hpp"
#include "csvWriter.h"

// Add a user to the repository
void PersonRepository::addUser(User* user) {
    users[user->getId()] = user;
}

// Add a driver to the repository
void PersonRepository::addDriver(Driver* driver) {
    drivers[driver->getId()] = driver;
}

// Retrieve a user by ID
User* PersonRepository::getUserById(int id) const {
    auto it = users.find(id);
    return it != users.end() ? it->second : nullptr;
}

// Retrieve a driver by ID
Driver* PersonRepository::getDriverById(int id) const {
    auto it = drivers.find(id);
    return it != drivers.end() ? it->second : nullptr;
}

// Destructor: Clean up dynamically allocated users and drivers
PersonRepository::~PersonRepository() {
    // Clean up dynamically allocated users and drivers
    for (auto& pair : users) {
        delete pair.second;
    }
    for (auto& pair : drivers) {
        delete pair.second;
    }
}

void PersonRepository::saveUsersToFile(const std::string& filename) const {
    std::ofstream file(filename);
    CSVWriter csv(",", 5);
    csv << "ID" << "Name" << "Email" << "Phone" << "Password";

    for (const auto& pair : users) {
        const User* user = pair.second;
        csv.newRow() << user->getId() << user->getName() << user->getEmail() << user->getPhone() << user->getPassword();
    }

    file << csv << std::endl;
    file.close();
}

void PersonRepository::loadUsersFromFile(const std::string& filename) {
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

            User* user = new User(id, name, email, phone, password);
            addUser(user);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
    }
}