#ifndef MAP_GRAPH_H
#define MAP_GRAPH_H
#include <queue>
#include <stack>
#include <string>

class Coordinate {
   private:
    int x;
    int y;

   public:
    Coordinate(int x, int y);
    int getX() const;
    int getY() const;
};

class Site : public Coordinate {
   private:
    int id;
    std::string name;

   public:
    Site(int id, int x, int y, const std::string& name);
    int getId() const;
    std::string getName() const;
    void setName(const std::string& name);
};

class MapGraph {
   private:
    std::vector<std::shared_ptr<Site>> sites;                                         // Array to store the sites
    int** adjacencyMatrix;                                                            // Adjacency matrix to store edge weights
    void loadSitesFromCSV(const std::string& filename);                               // Load site names from a CSV file
    void loadSiteDistancesFromCSV(const std::string& filename);                       // Load site distances from a CSV file
    std::vector<std::shared_ptr<Site>> getNeighborSites(std::shared_ptr<Site> site);  // Get the neighbor sites of a site
    int getHeuristic(std::shared_ptr<Site> start, std::shared_ptr<Site> end);

   public:
    // Constructor
    MapGraph();

    // Destructor
    ~MapGraph();

    // Add an route to the graph
    void addroute(std::shared_ptr<Site> startSite, std::shared_ptr<Site> endSite, int distance);

    // Get the distance between two sites
    int getDistance(std::shared_ptr<Site> startSite, std::shared_ptr<Site> endSite) const;
    int getDistance(Coordinate a, Coordinate b) const;

    // Get a reference to a site by its ID
    std::shared_ptr<Site> getSiteByID(int siteID);

    std::shared_ptr<Site> getSiteByName(const std::string& siteName);

    // Get the number of sites
    int getSitesNum() const;

    std::pair<std::stack<std::shared_ptr<Site>>, int> shortestPath(std::shared_ptr<Site> startSite, std::shared_ptr<Site> endSite);
};

#endif