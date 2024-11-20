#include "Entities/Ride.h"

// Define the Ride class

Ride::Ride(string r_id, string u_id, string d_id, string s_loc, string e_loc, time_t s_time)
{
    rideId = r_id;
    userId = u_id;
    driverId = d_id;
    startLocation = s_loc;
    endLocation = e_loc;
    startTime = s_time;
    endTime = 0; // Default to 0 until ride ends
    distance = 0.0;
    duration = 0;
    fareAmount = 0.0;
    paymentMethod = "Not Set";
    rideStatus = "Ongoing";
    passengerCount = 1;
    feedback = "";
}

// Setters and Getters
void Ride::setEndTime(time_t e_time) { endTime = e_time; }
void Ride::setDistance(double dist) { distance = dist; }
void Ride::setDuration(int dur) { duration = dur; }
void Ride::setFareAmount(double fare) { fareAmount = fare; }
void Ride::setPaymentMethod(string method) { paymentMethod = method; }
void Ride::setRideStatus(string status) { rideStatus = status; }
void Ride::setVehicleInfo(string info) { vehicleInfo = info; }
void Ride::addRouteDetail(string waypoint) { routeDetails.push_back(waypoint); }
void Ride::setFeedback(string fb) { feedback = fb; }
void Ride::setPassengerCount(int count) { passengerCount = count; }

// Print Ride Details
void Ride::printRideDetails()
{
    cout << "Ride ID: " << rideId << endl;
    cout << "User ID: " << userId << endl;
    cout << "Driver ID: " << driverId << endl;
    cout << "Start Location: " << startLocation << endl;
    cout << "End Location: " << endLocation << endl;
    cout << "Start Time: " << ctime(&startTime);
    if (endTime != 0)
    {
        cout << "End Time: " << ctime(&endTime);
    }
    else
    {
        cout << "End Time: Not Yet Completed" << endl;
    }
    cout << "Distance: " << distance << " km" << endl;
    cout << "Duration: " << duration << " minutes" << endl;
    cout << "Fare Amount: $" << fareAmount << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "Ride Status: " << rideStatus << endl;
    cout << "Vehicle Info: " << vehicleInfo << endl;
    cout << "Passenger Count: " << passengerCount << endl;
    cout << "Feedback: " << feedback << endl;

    // Print Route Details
    if (!routeDetails.empty())
    {
        cout << "Route Details: ";
        for (const string &waypoint : routeDetails)
        {
            cout << waypoint << " -> ";
        }
        cout << "End" << endl;
    }
}
