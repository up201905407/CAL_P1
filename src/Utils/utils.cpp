#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::pair<int, int>> readEdges(std::string path){
    std::vector<std::pair<int, int>> edges;
    std::pair<int, int> pair;
    std::ifstream edges_file(path);
    if (!edges_file.is_open()) {
        std::cerr << "Can't open edges file!" << std::endl;
        return edges; //excecao
    }

    std::string line;
    double source;
    double target;
    while(std::getline(edges_file, line)){
        std::istringstream iss(line);
        if (!(iss >> source >> target)) {
            std::cerr << "Error reading edges file!" << std::endl;
            return edges; //excecao
        } // error
        pair = {source, target};
        edges.push_back(pair);
    }
}
/*
std::vector<std::vector<int>> readNodes(std::string path){

}*/

