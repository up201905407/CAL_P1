#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>

typedef std::vector<std::pair<long int, long int>> Edges;
typedef std::vector<std::pair<long int, std::pair<double, double>>> Nodes;

Edges readEdges(std::string path);
Nodes readNodes(std::string path);
std::string getPathEdges(const std::string& city);
std::string getPathNodes(const std::string& place);

#endif //_UTILS_H_
