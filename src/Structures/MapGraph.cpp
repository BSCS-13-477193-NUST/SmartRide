#include "Structures.h"
#include "csv.hpp"

struct Node {
    Site* site;
    int distance;
    Node* parent;

    Node(Site* site, int distance, Node* parent) : site(site), distance(distance), parent(parent) {}
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }

    bool operator==(const Node& other) const {
        return site->getId() == other.site->getId();
    }
};

Site::Site(int id, int x, int y, const std::string& name) : Coordinate(x, y), id(id), name(name) {}

int Site::getId() const {
    return id;
}

std::string Site::getName() const {
    return name;
}

std::string Site::setName(const std::string& name) {
    this->name = name;
}

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

int Coordinate::getX() const {
    return x;
}

int Coordinate::getY() const {
    return y;
}

MapGraph::MapGraph() {
    // Load site names from CSV file
    loadSitesFromCSV("data/sites.csv");

    // Allocate memory for adjacency matrix
    adjacencyMatrix = new int*[this->getSitesNum()];
    for (int i = 0; i < this->getSitesNum(); i++) {
        adjacencyMatrix[i] = new int[this->getSitesNum()];
        for (int j = 0; j < this->getSitesNum(); j++) {
            adjacencyMatrix[i][j] = -1;
        }
    }

    // Load site distances from CSV file
    loadSiteDistancesFromCSV("data/distances.csv");
}

MapGraph::~MapGraph() {
    // Deallocate memory for adjacency matrix
    for (int i = 0; i < this->getSitesNum(); i++) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

void MapGraph::addroute(int startSiteID, int endSiteID, int distance) {
    // Check if the site IDs are valid
    if (startSiteID < 0 || startSiteID >= this->getSitesNum() || endSiteID < 0 || endSiteID >= this->getSitesNum()) {
        std::cerr << "Invalid site IDs." << std::endl;
        return;
    }

    // Add the route to the adjacency matrix
    adjacencyMatrix[startSiteID][endSiteID] = distance;
    adjacencyMatrix[endSiteID][startSiteID] = distance;
}

int MapGraph::getDistance(int startSiteID, int endSiteID) const {
    // Check if the site IDs are valid
    if (startSiteID < 0 || startSiteID >= this->getSitesNum() || endSiteID < 0 || endSiteID >= this->getSitesNum()) {
        std::cerr << "Invalid site IDs." << std::endl;
        return -1;
    }

    // Return the distance between the sites
    return adjacencyMatrix[startSiteID][endSiteID];
}

int MapGraph::getHeuristic(Site& start, Site& end) {
    return abs(start.getX() - end.getX()) + abs(start.getY() - end.getY());
}

int MapGraph::getSitesNum() const {
    return this->sites.size();
}

Site& MapGraph::getSiteByID(int siteID) {
    // Check if the site ID is valid
    if (siteID < 0 || siteID >= this->getSitesNum()) {
        std::cerr << "Invalid site ID." << std::endl;
        throw std::invalid_argument("Invalid site ID.");
    }

    for (Site& site : sites) {
        if (site.getId() == siteID) {
            return site;
        }
    }
}

Site& MapGraph::getSiteByName(const std::string& siteName) {
    for (Site& site : sites) {
        if (site.getName() == siteName) {
            return site;
        }
    }
    throw std::out_of_range("Site not found.");
}

std::vector<int> MapGraph::getNeighborSites(int siteID) {
    // Check if the site ID is valid
    if (siteID < 0 || siteID >= this->getSitesNum()) {
        std::cerr << "Invalid site ID." << std::endl;
        return std::vector<int>();
    }

    // Allocate memory for the array of neighbors
    std::vector<int> neighbors;

    // Fill the array with the IDs of the neighbors
    for (int i = 0; i < this->getSitesNum(); i++) {
        if (adjacencyMatrix[siteID][i] != -1) {
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

void MapGraph::loadSitesFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    csv::CSVReader reader(file);

    for (csv::CSVRow& row : reader) {
        try {
            std::string siteName = row["Site Name"].get<std::string>();
            int x = row["x"].get<int>();
            int y = row["y"].get<int>();

            if (siteName.empty()) {
                std::cerr << "Error: Site name is empty." << std::endl;
                continue;
            }

            Site site(sites.size(), x, y, siteName);
            sites.push_back(site);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
    }
}

void MapGraph::loadSiteDistancesFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    csv::CSVReader reader(file);

    for (csv::CSVRow& row : reader) {
        std::string startSiteName = row["Start"].get<std::string>();
        std::string endSiteName = row["End"].get<std::string>();
        int distance = row["Distance"].get<int>();

        try {
            Site& startSite = this->getSiteByName(startSiteName);
            Site& endSite = this->getSiteByName(endSiteName);

            int startSiteID = startSite.getId();
            int endSiteID = endSite.getId();

            if (distance < 0) {
                std::cerr << "Invalid distance value: " << distance << std::endl;
                continue;
            }

            this->addroute(startSiteID, endSiteID, distance);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Site not found: " << e.what() << std::endl;
            continue;
        }
    }
}
std::queue<int> MapGraph::shortestPath(int startSiteID, int endSiteID) {
    // Check if the site IDs are valid
    if (startSiteID < 0 || startSiteID >= this->getSitesNum() || endSiteID < 0 || endSiteID >= this->getSitesNum()) {
        std::cerr << "Invalid site IDs." << std::endl;
        return std::queue<int>();
    }

    // Initialize the queue for the shortest path
    std::queue<int> shortestPathQueue;

    // A* algorithm
    std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> toVisit;
    std::vector<bool> visited(this->getSitesNum(), false);

    toVisit.push(new Node(&this->getSiteByID(startSiteID), 0, nullptr));

    while (!toVisit.empty()) {
        Node* current = toVisit.top();
        toVisit.pop();

        if (current->site->getId() == endSiteID) {
            // Reconstruct the path
            std::queue<int> path;
            Node* node = current;
            while (node->parent != nullptr) {
                path.push(node->site->getId());
                node = node->parent;
            }
            while (!toVisit.empty()) {
                delete toVisit.top();
                toVisit.pop();
            }
            return path;
        }

        std::vector<int> neighbors = getNeighborSites(current->site->getId());
        for (int neighborID : neighbors) {
            Site& neighbor = getSiteByID(neighborID);
            Node* neighborNode = new Node(&neighbor, current->distance + getDistance(current->site->getId(), neighborID) + getHeuristic(neighbor, getSiteByID(endSiteID)), current);

            if (visited[current->site->getId()]) {
                continue;
            }

            toVisit.push(neighborNode);
        }

        visited[current->site->getId()] = true;
    }

    while (!toVisit.empty()) {
        delete toVisit.top();
        toVisit.pop();
    }

    return std::queue<int>();
}