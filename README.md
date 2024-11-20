# SmartRide - A Ride-Hailing Service

SmartRide is a simulated ride-hailing service that demonstrates various features of such a platform while leveraging efficient data structures and algorithms. This project is designed as part of a Data Structures and Algorithms (DSA) course, focusing on the implementation of data structures from scratch in C++.

---

## Project Overview

SmartRide enables users to book rides, drivers to accept requests, and the system to handle operations such as matching, route optimization, and dynamic pricing. It highlights the importance of choosing and implementing suitable data structures for specific tasks.

---

## Key Features

We have implemented the following features for SmartRide:

1. **User and Driver Management**

   - Stores user and driver profiles.
   - Allows registration, login, and ride requests for users.
   - Drivers can log in to accept ride requests.
   - **Data Structure:** Self-implemented `Hash Table` for quick lookup and updates.

2. **Ride Request Matching**

   - Matches users with the nearest available driver.
   - **Data Structure:** `Binary Heap` for efficient nearest-driver lookup.

3. **Real-Time Location Tracking**

   - Models the city map as a graph where intersections are nodes and roads are weighted edges.
   - Computes the shortest path between points using Dijkstra's Algorithm.
   - **Data Structure:** Adjacency List for graph representation.

4. **Dynamic Ride Pricing**

   - Adjusts pricing based on time, traffic, and demand.
   - **Data Structure:** `Balanced Binary Search Tree` for historical price retrieval.

5. **Ride Request Queue**

   - Manages pending ride requests when no drivers are available.
   - **Data Structure:** `Queue` (circular array implementation).

6. **Driver Rating System**

   - Allows users to rate drivers and prioritizes top-rated drivers.
   - **Data Structure:** `Max Heap` for efficient access to top-rated drivers.

7. **Additional Features**
   - [Insert your unique features here].
   - [Brief description of each].

---

## Project Structure
