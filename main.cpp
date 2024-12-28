#include <iostream>

#include "Entities.h"
#include "Structures.h"

int main() {
    // Create a new map graph
    MapGraph mapGraph;

    // Find the shortest path between two sites
    auto shortestPath = mapGraph.shortestPath(mapGraph.getSiteByID(15), mapGraph.getSiteByID(8));

    // Display the shortest path
    while (!shortestPath.first.empty()) {
        auto site = shortestPath.first.top();
        std::cout << site->getName() << std::endl;
        shortestPath.first.pop();
    }
    std::cout << "Total distance: " << shortestPath.second << std::endl;
}