#include "utils.h"
#include <fstream>
#include <iostream>
#include <cmath>

Edges readEdges(std::string path){
    Edges edges;
    std::pair<double, double> pair1;
    std::pair<unsigned long int, std::pair<double, double>> pair2;
    std::ifstream edges_file(path);
    if (!edges_file.is_open()) {
        std::cerr << "Can't open edges file!" << std::endl;
        return edges; //excecao
    }
    int numEdges;
    std::string line;
    long int source;
    long int target;
    char trash;
    edges_file >> numEdges;
    for(int i = 0; i < numEdges; ++i){
        edges_file >> trash >> source >> trash >> target >> trash;
        pair1 = {source, target};
        pair2 = {i, pair1};
        edges.push_back(pair2);
    }
    return edges;
}
Nodes readNodes(std::string path){
    Nodes nodes;
    std::pair<double, double> pair1;
    std::pair<unsigned long int, std::pair<double, double>> pair2;
    std::ifstream nodes_file(path);
    if (!nodes_file.is_open()) {
        std::cerr << "Can't open nodes file!" << std::endl;
        return nodes; //excecao
    }

    int numNodes;
    std::string line;
    long int id;
    double lat;
    double lon;
    char trash;
    nodes_file >> numNodes;
    for(int i = 0; i < numNodes; ++i){
        nodes_file >> trash >> id >> trash >> lat >> trash >> lon >> trash;
        pair1 = {lat, lon};
        pair2 = {id, pair1};
        nodes.push_back(pair2);
    }
    return nodes;
}

std::string getPathEdges(const std::string& city){
    std::string cityUpper = city;
    cityUpper[0] = std::toupper(cityUpper[0]);
    std::string path = "../Map/PortugalMaps/PortugalMaps/" + cityUpper + "/edges_" + city + ".txt";
    return path;
}

std::string getPathNodes(const std::string& city){
    std::string cityUpper = city;
    cityUpper[0] = std::toupper(cityUpper[0]);
    std::string path = "../Map/PortugalMaps/PortugalMaps/" + cityUpper + "/nodes_lat_lon_" + city + ".txt";
    return path;
}

double haversine(double lat1, double lon1, double lat2, double lon2){
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

