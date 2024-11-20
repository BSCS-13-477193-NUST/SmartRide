#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    int age;
    string name;
    string email;
    bool gender;
    string phoneNumber;
    string location;

    Person(int age, string name, string email, bool gender, string phoneNumber, string location)
        : age(age), name(name), email(email), gender(gender), phoneNumber(phoneNumber), location(location) {}

    void setAge(int newAge) { age = newAge; }
    void setName(string newName) { name = newName; }
    void setGender(bool newGender) { gender = newGender; }
    void setPhoneNumber(string newPhoneNumber) { phoneNumber = newPhoneNumber; }
    void setLocation(string newLocation) { location = newLocation; }

    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Email: " << email << endl;
        cout << "Gender: " << (gender ? "Male" : "Female") << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Location: " << location << endl;
    }
};

class Passenger : public Person {
public:
    string rideStatus;

    Passenger(int age, string name, string email, bool gender, string phoneNumber, string location)
        : Person(age, name, email, gender, phoneNumber, location), rideStatus("None") {}

    bool requestRide() {
        if (rideStatus == "None") {
            rideStatus = "Requested";
            return true;
        }
        return false;
    }

    void setRideStatus(string newRideStatus) { rideStatus = newRideStatus; }

    void display() const override {
        Person::display();
        cout << "Ride Status: " << rideStatus << endl;
    }
};

class Driver : public Person {
public:
    string licenseNumber;
    int yearsOfExperience;
    double averageRating;
    int numberOfRidesCompleted;
    vector<double> ratings;
    bool availability;

    Driver(int age, string name, string email, bool gender, string phoneNumber, string location, string licenseNumber, int yearsOfExperience)
        : Person(age, name, email, gender, phoneNumber, location), licenseNumber(licenseNumber), yearsOfExperience(yearsOfExperience),
          averageRating(0.0), numberOfRidesCompleted(0), availability(true) {}

    void setLicenseNumber(string newLicenseNumber) { licenseNumber = newLicenseNumber; }
    void setYearsOfExperience(int newYearsOfExperience) { yearsOfExperience = newYearsOfExperience; }
    void setAvailability(bool newAvailability) { availability = newAvailability; }

    void acceptRide(const Passenger& Passenger) {
        if (availability && Passenger.rideStatus == "Requested") {
            availability = false;
            cout << "Driver " << name << " accepted the ride for " << Passenger.name << "." << endl;
        } else {
            cout << "Driver unavailable or invalid ride request!" << endl;
        }
    }

    void takeRating(double newRating) {
        if (newRating < 0 || newRating > 5) {
            cout << "Invalid rating! Ratings must be between 0 and 5." << endl;
            return;
        }
        ratings.push_back(newRating);
        numberOfRidesCompleted++;
        averageRating = 0;
        for (double rating : ratings) {
            averageRating += rating;
        }
        averageRating /= ratings.size();
    }

    void display() const override {
        Person::display();
        cout << "License Number: " << licenseNumber << endl;
        cout << "Years of Experience: " << yearsOfExperience << endl;
        cout << "Number of Rides Completed: " << numberOfRidesCompleted << endl;
        cout << "Average Rating: " << averageRating << endl;
        cout << "Availability: " << (availability ? "Available" : "Unavailable") << endl;
    }
};

int main() {
    Driver driver1(35, "Ali Hussain", "ali@saraiki.com", true, "123-456-7890", "Sindh", "D123456", 10);
    Driver driver2(29, "Zain Butt", "zainbutt@gmail.com", false, "987-654-1230", "Lor", "D654321", 5);

    cout << "Driver Details (Initial):" << endl;
    driver1.display();
    cout << endl;
    driver2.display();
    cout << "--------------------------" << endl;

    cout << "\nAdding Ratings to Drivers:" << endl;
    driver1.takeRating(4.5);
    driver1.takeRating(5.0);
    driver1.takeRating(4.8);

    driver2.takeRating(4.0);
    driver2.takeRating(3.5);
    driver2.takeRating(4.2);

    cout << "\nUpdated Driver Details:" << endl;
    driver1.display();
    cout << endl;
    driver2.display();
    cout << "--------------------------" << endl;

    Passenger Passenger1(25, "Battay", "battay@yahoo.com", false, "987-654-3210", "Pindi");
    Passenger Passenger2(30, "Rakshas", "rakshas@prehistoricforums.com", true, "654-123-9870", "Ali ke sath");

    cout << "Passenger Details (Initial):" << endl;
    Passenger1.display();
    cout << endl;
    Passenger2.display();
    cout << "--------------------------" << endl;

    cout << "\nPassengers Requesting Rides:" << endl;
    if (Passenger1.requestRide())
        cout << Passenger1.name << " successfully requested a ride." << endl;
    else
        cout << Passenger1.name << " failed to request a ride." << endl;

    if (Passenger2.requestRide())
        cout << Passenger2.name << " successfully requested a ride." << endl;
    else
        cout << Passenger2.name << " failed to request a ride." << endl;

    cout << "\nUpdated Passenger Details:" << endl;
    Passenger1.display();
    cout << endl;
    Passenger2.display();
    cout << "--------------------------" << endl;

    cout << "\nDriver Accepting Ride:" << endl;
    driver1.acceptRide(Passenger1);
    driver2.acceptRide(Passenger2);

    cout << "\nUpdated Driver Availability:" << endl;
    driver1.display();
    cout << endl;
    driver2.display();
    cout << "--------------------------" << endl;

    return 0;
}
