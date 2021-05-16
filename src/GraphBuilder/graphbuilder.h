#ifndef _GRAPHVIEWER_H_
#define _GRAPHVIEWER_H_

#include "../Graph/Graph.h"
#include "../Utils/utils.h"

template<class T>
class GraphBuilder{
private:
    Graph<T>* graph;
public:
    explicit GraphBuilder(Graph<T>* graph);
    bool fillGraph(const std::string &place);
};


template<class T>
GraphBuilder<T>::GraphBuilder(Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
bool GraphBuilder<T>::fillGraph(const std::string &place) {
    Edges edges = readEdges(getPathEdges(place));
    Nodes nodes = readNodes(getPathNodes(place));
    for (auto node : nodes){
        if (!graph->addVertex(node.first, node.second.first, node.second.second))
            return false;
    }
    for (auto edge : edges){
        if (!graph->addEdge(edge.first, edge.second.first, edge.second.second, 1))
            return false;
    }
    return true;
}

#endif //_GRAPHVIEWER_H_
