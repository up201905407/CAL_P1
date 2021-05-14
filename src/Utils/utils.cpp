#include "utils.h"
#include <fstream>
#include <iostream>

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
    std::string path = "../Mapas-20210511/PortugalMaps/PortugalMaps/" + cityUpper + "/edges_" + city + ".txt";
    return path;
}

std::string getPathNodes(const std::string& place){
    std::string placeUpper = place;
    placeUpper[0] = std::toupper(placeUpper[0]);
    std::string path = "../Mapas-20210511/PortugalMaps/PortugalMaps/" + placeUpper + "/nodes_lat_lon_" + place + ".txt";
    return path;
}

