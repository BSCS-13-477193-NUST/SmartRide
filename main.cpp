#include <iostream>

#include "Entities.h"
#include "Structures.h"

int main() {
    // Create a new map graph
    MapGraph mapGraph;

    // Find the shortest path between two sites
    std::queue<int> shortestPath = mapGraph.shortestPath(0, 6);

    // Display the shortest path
    while (!shortestPath.empty()) {
        int site = shortestPath.front();
        std::cout << site + 1 << std::endl;
        shortestPath.pop();
}