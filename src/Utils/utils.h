#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>

typedef std::vector<std::pair<unsigned long int, std::pair<double, double>>> Edges;
typedef std::vector<std::pair<unsigned long int, std::pair<double, double>>> Nodes;

/**
 * Reads edges from file anda returns information
 * @param path File to be read
 * @return Returns all the Edges from the graph
 */
Edges readEdges(std::string path);
/**
 * Reads nodes from file and returns information
 * @param path File to be read
 * @return Returns all the Nodes from the graph
 */
Nodes readNodes(std::string path);
/**
 * Builds the edge's file path
 * @param city The city to get edges
 * @return Path
 */
std::string getPathEdges(const std::string& city);
/**
 * Builds the nodes's file path
 * @param city The city to get nodes
 * @return Path
 */
std::string getPathNodes(const std::string& city);
/**
 * Calculates the distance between 2 points using latitudes and longitudes
 * @param lat1 First point latitude
 * @param lon1 First point longitude
 * @param lat2 Second point latitude
 * @param lon2 Second point longitude
 * @return Distance The distance between the 2 points
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

#endif //_UTILS_H_
