#ifndef RIDE_H
#define RIDE_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime> // For time management

using namespace std;

// Define the Ride class
class Ride {
private:
    // Core attributes
    string rideId;
    string userId;
    string driverId;
    string startLocation;
    string endLocation;
    time_t startTime;
    time_t endTime;

    // Additional attributes
    double distance;               // in kilometers
    int duration;                  // in minutes
    double fareAmount;            // total fare
    string paymentMethod;         // e.g., "Credit Card", "Cash"
    string rideStatus;            // "Ongoing", "Completed", "Cancelled"
    string vehicleInfo;           // e.g., "Toyota Corolla, ABC-123"
    vector<string> routeDetails;  // Optional: Store intermediate waypoints
    int passengerCount;
    string feedback;               // User feedback or rating

public:
    // Constructor
    Ride(string r_id, string u_id, string d_id, string s_loc, string e_loc, time_t s_time);
    // Setters and Getters
    void setEndTime(time_t e_time);
    void setDistance(double dist);
    void setDuration(int dur);
    void setFareAmount(double fare);
    void setPaymentMethod(string method);
    void setRideStatus(string status);
    void setVehicleInfo(string info);
    void addRouteDetail(string waypoint);
    void setFeedback(string fb);
    void setPassengerCount(int count);

    // Print Ride Details
    void printRideDetails();
};

#endif