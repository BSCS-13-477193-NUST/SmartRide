#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
public:
    string ID;
    string name;
    char gender;
    string phone;

    Person() : ID(""), name(""), gender('M'), phone("") {}
    Person(string ID, string name, char gender, string phone) 
        : ID(ID), name(name), gender(gender), phone(phone) {}

    virtual string getName() = 0;
    virtual string getPhone() = 0;
    virtual void setName(string name) = 0;
    virtual void setPhone(string phone) = 0;

    string getID() { return ID; }
    char getGender() { return gender; }
    void setID(string ID) { this->ID = ID; }
    void setGender(char gender) { this->gender = gender; }
};

class Driver : public Person {
private:
    string carModel;
    string carPlate;

public:
    Driver() : Person(), carModel("Unknown"), carPlate("Unknown") {}

    Driver(string name, string email, string password, string carModel, string carPlate)
        : Person(email, name, 'M', password), carModel(carModel), carPlate(carPlate) {}

    string getCarModel() { return carModel; }
    string getCarPlate() { return carPlate; }
    void setCarModel(string carModel) { this->carModel = carModel; }
    void setCarPlate(string carPlate) { this->carPlate = carPlate; }

    string getName() override { return name; }
    string getPhone() override { return phone; }
    void setName(string name) override { this->name = name; }
    void setPhone(string phone) override { this->phone = phone; }
};

class Passenger : public Person {
private:
    string email;
    string password;

public:
    Passenger() : Person(), email(""), password("") {}

    Passenger(string name, string email, string password)
        : Person("", name, 'M', ""), email(email), password(password) {}

    string getName() override { return name; }
    string getPhone() override { return phone; }
    void setName(string name) override { this->name = name; }
    void setPhone(string phone) override { this->phone = phone; }

    void setEmail(string email) { this->email = email; }
    void setPassword(string password) { this->password = password; }
};

int main() {
    Driver driver1("Ali Hussain", "ali@saraiki.com", "password1", "Toyota Corolla", "ABC123");
    Driver driver2("Zain Butt", "zainbutt@gmail.com", "password2", "Honda Civic", "XYZ456");

    cout << "Driver Details (Initial):" << endl;
    cout << "Driver 1: " << driver1.getName() << ", " << driver1.getCarModel() << ", " << driver1.getCarPlate() << endl;
    cout << "Driver 2: " << driver2.getName() << ", " << driver2.getCarModel() << ", " << driver2.getCarPlate() << endl;

    Passenger passenger1("Battay", "battay@yahoo.com", "pass1");
    Passenger passenger2("Rakshas", "rakshas@prehistoricforums.com", "pass2");

    cout << "\nPassenger Details (Initial):" << endl;
    cout << "Passenger 1: " << passenger1.getName() << ", " << passenger1.getPhone() << endl;
    cout << "Passenger 2: " << passenger2.getName() << ", " << passenger2.getPhone() << endl;

    return 0;
}
