#ifndef MAP_GRAPH_H
#define MAP_GRAPH_H
#include <queue>
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
    std::string setName(const std::string& name);
};

class MapGraph {
   private:
    std::vector<Site> sites;                                     // Array to store the sites
    int** adjacencyMatrix;                                       // Adjacency matrix to store edge weights
    void loadSitesFromCSV(const std::string& filename);          // Load site names from a CSV file
    void loadSiteDistancesFromCSV(const std::string& filename);  // Load site distances from a CSV file
    std::vector<int> getNeighborSites(int siteID);               // Get the neighbor sites of a site
    int getHeuristic(Site& start, Site& end);

   public:
    // Constructor
    MapGraph();

    // Destructor
    ~MapGraph();

    // Add an route to the graph
    void addroute(int startSiteID, int endSiteID, int distance);

    // Get the distance between two sites
    int getDistance(int startSiteID, int endSiteID) const;

    // Get a reference to a site by its ID
    Site& getSiteByID(int siteID);

    Site& getSiteByName(const std::string& siteName);

    // Get the number of sites
    int getSitesNum() const;

    std::queue<int> shortestPath(int startSiteID, int endSiteID);
};

#endif