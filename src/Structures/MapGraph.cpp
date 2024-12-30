#include "Structures/MapGraph.h"

#include "Entities/Person.h"
#include "Misc.h"
#include "csv.hpp"

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

int Coordinate::getX() const {
    return x;
}

int Coordinate::getY() const {
    return y;
}

typedef struct SiteNode {
    std::shared_ptr<Site> site;
    int distance;
    std::shared_ptr<SiteNode> parent;

    SiteNode(std::shared_ptr<Site> site, int distance, std::shared_ptr<SiteNode> parent) : site(site), distance(distance), parent(parent) {}

    bool operator>(const SiteNode& other) const {
        return distance > other.distance;
    }

    bool operator==(const SiteNode& other) const {
        return site->getId() == other.site->getId();
    }
} SiteNode;

Site::Site(int id, int x, int y, const std::string& name) : Coordinate(x, y), id(id), name(name) {}

int Site::getId() const {
    return id;
}

std::string Site::getName() const {
    return name;
}

void Site::setName(const std::string& name) {
    this->name = name;
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

void MapGraph::addroute(std::shared_ptr<Site> startSite, std::shared_ptr<Site> endSite, int distance) {
    adjacencyMatrix[startSite->getId()][endSite->getId()] = distance;
    adjacencyMatrix[endSite->getId()][startSite->getId()] = distance;
}

int MapGraph::getDistance(std::shared_ptr<Site> startSite, std::shared_ptr<Site> endSite) const {
    return adjacencyMatrix[startSite->getId()][endSite->getId()];
}

int MapGraph::getDistance(Coordinate a, Coordinate b) const {
    return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY());
}

std::vector<std::shared_ptr<Site>> MapGraph::getNeighborSites(std::shared_ptr<Site> site) {
    // Allocate memory for the array of neighbors
    std::vector<std::shared_ptr<Site>> neighbors;

    // Fill the array with the IDs of the neighbors
    for (int i = 0; i < this->getSitesNum(); i++) {
        if (adjacencyMatrix[site->getId()][i] != -1) {
            neighbors.push_back(getSiteByID(i));
        }
    }

    return neighbors;
}

int MapGraph::getHeuristic(std::shared_ptr<Site> start, std::shared_ptr<Site> end) {
    return abs(start->getX() - end->getX()) + abs(start->getY() - end->getY());
}

std::shared_ptr<Site> MapGraph::getSiteByID(int siteID) {
    for (auto site : sites) {
        if (site->getId() == siteID) {
            return site;
        }
    }
    std::cerr << "Error: Site " << siteID << " not found." << std::endl;
    throw std::out_of_range("Site not found");
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

            std::shared_ptr<Site> site = std::make_shared<Site>(sites.size(), x, y, siteName);
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

        std::shared_ptr<Site> startSite = getSiteByName(startSiteName);
        std::shared_ptr<Site> endSite = getSiteByName(endSiteName);

        this->addroute(startSite, endSite, distance);
    }
}
std::pair<std::stack<std::shared_ptr<Site>>, int> MapGraph::shortestPath(std::shared_ptr<Site> startSite, std::shared_ptr<Site> endSite) {
    // A* algorithm
    struct Compare {
        bool operator()(const std::shared_ptr<SiteNode>& lhs, const std::shared_ptr<SiteNode>& rhs) const {
            return lhs->distance > rhs->distance;
        }
    };
    std::priority_queue<std::shared_ptr<SiteNode>, std::vector<std::shared_ptr<SiteNode>>, Compare> toVisit;
    std::set<std::shared_ptr<SiteNode>> visited;

    toVisit.push(std::make_shared<SiteNode>(startSite, 0, nullptr));

    while (!toVisit.empty()) {
        std::shared_ptr<SiteNode> current = toVisit.top();
        toVisit.pop();

        if (current->site == endSite) {
            // Reconstruct the path
            // Initialize the queue for the shortest path
            std::stack<std::shared_ptr<Site>> path;
            int cost = 0;
            std::shared_ptr<SiteNode> node = current;
            while (node->parent != nullptr) {
                path.push(node->site);
                cost += getDistance(node->site, node->parent->site);
                node = node->parent;
            }
            return std::pair<std::stack<std::shared_ptr<Site>>, int>(path, cost);
        }

        std::vector<std::shared_ptr<Site>> neighbors = getNeighborSites(current->site);
        for (auto& neighbor : neighbors) {
            std::shared_ptr<SiteNode> neighborSiteNode = std::make_shared<SiteNode>(neighbor, current->distance + getDistance(current->site, neighbor) + getHeuristic(neighbor, endSite), current);

            if (visited.find(neighborSiteNode) != visited.end()) {
                continue;
            }

            toVisit.push(neighborSiteNode);
        }

        visited.insert(current);
    }

    return std::pair<std::stack<std::shared_ptr<Site>>, int>(std::stack<std::shared_ptr<Site>>(), -1);
}

std::shared_ptr<Site> MapGraph::getSiteByName(const std::string& siteName) {
    for (auto site : sites) {
        if (site->getName() == siteName) {
            return site;
        }
    }

    std::cerr << "Error: Site " << siteName << " not found." << std::endl;
    throw std::out_of_range("Site not found");
}

std::shared_ptr<Site> MapGraph::getClosestSite(Coordinate location) {
    std::shared_ptr<Site> closestSite = nullptr;
    int minDistance = INT_MAX;

    for (auto site : sites) {
        int distance = getDistance(location, Coordinate(site->getX(), site->getY()));
        if (distance < minDistance) {
            minDistance = distance;
            closestSite = site;
        }
    }

    return closestSite;
}

std::vector<std::shared_ptr<Site>> MapGraph::getSites() const {
    return sites;
}

std::queue<std::pair<std::shared_ptr<User>, std::shared_ptr<Site>>> MapGraph::mergeStops(std::shared_ptr<Site> start, std::vector<std::pair<std::shared_ptr<User>, std::vector<std::shared_ptr<Site>>>> usersStops) {
    using pair = std::pair<std::shared_ptr<User>, std::shared_ptr<Site>>;
    std::queue<pair> mergedQueue;

    if (usersStops.size() == 0 || usersStops.size() > 2) {
        std::cerr << "Error: Invalid number of users." << std::endl;
        return mergedQueue;
    }
    std::pair<std::shared_ptr<User>, std::vector<std::shared_ptr<Site>>> first = usersStops[0];
    std::pair<std::shared_ptr<User>, std::vector<std::shared_ptr<Site>>> second;
    if (usersStops.size() == 2) {
        second = usersStops[1];
    }

    while (!first.second.empty() || !second.second.empty()) {
        auto firstSite = first.second.empty() ? nullptr : first.second.front();
        auto secondSite = second.second.empty() ? nullptr : second.second.front();

        if (firstSite && secondSite) {
            int firstDistance = getDistance(start, firstSite);
            int secondDistance = getDistance(start, secondSite);
            if (firstDistance < secondDistance) {
                mergedQueue.push({first.first, firstSite});
                first.second.erase(first.second.begin());
            } else {
                mergedQueue.push({second.first, secondSite});
                second.second.erase(second.second.begin());
            }
        } else if (firstSite) {
            mergedQueue.push({first.first, firstSite});
            first.second.erase(first.second.begin());
        } else if (secondSite) {
            mergedQueue.push({second.first, secondSite});
            second.second.erase(second.second.begin());
        }
    }

    return mergedQueue;
}

int MapGraph::getSitesNum() const {
    return sites.size();
}
