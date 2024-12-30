#include <memory>

#include "Entities.h"
#include "Structures.h"

class SmartRide {
   private:
    std::unique_ptr<DynamicRidePricing> pricing;
    std::shared_ptr<MapGraph> mapGraph;
    std::shared_ptr<DriverRepository> driverRepository;
    std::shared_ptr<UserRepository> userRepository;
    std::shared_ptr<RideRepository> rideRepository;

   public:
    SmartRide();
    ~SmartRide();

    void start();
    std::shared_ptr<User> loginUser();
    std::shared_ptr<Driver> loginDriver();
    std::shared_ptr<User> registerUser();
    std::shared_ptr<Driver> registerDriver();
    void logout();

    void userInterface(std::shared_ptr<User> user);
    void driverInterface(std::shared_ptr<Driver> driver);

    void requestRide(std::shared_ptr<User> user);
    void viewRideHistory(std::shared_ptr<User> user);
    void ratelastDriver(std::shared_ptr<User> user);

    void pickRide(std::shared_ptr<Driver> driver);
    void acceptRideRequest(std::shared_ptr<Driver> driver, std::shared_ptr<Ride> ride);
    void endRideDriver(std::shared_ptr<Driver> driver);
    void viewRideRequests(std::shared_ptr<Driver> driver);
    void showMyRating(std::shared_ptr<Driver> driver);
};