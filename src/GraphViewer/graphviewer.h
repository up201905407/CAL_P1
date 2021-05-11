#ifndef _GRAPHVIEWER_H_
#define _GRAPHVIEWER_H_

#include "../Graph/Graph.h"
#include "../Utils/utils.h"

template<class T>
class GraphViewer{
private:
    Graph<T>* graph;
public:
    explicit GraphViewer(Graph<T>* graph);
    bool fillGraph(const std::string &place);


};

template<class T>
GraphViewer<T>::GraphViewer(Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
bool GraphViewer<T>::fillGraph(const std::string &place) {
    Edges edges = readEdges(getPathEdges(place));
    Nodes nodes = readNodes(getPathNodes(place));
    for (auto node : nodes){
        if (!graph->addVertex(node.first, node.second.first, node.second.first))
            return false;
    }
    for (auto edge : edges){
        if (!graph->addEdge(edge.first, edge.second, 1))
            return false;
    }
    return true;
}

#endif //_GRAPHVIEWER_H_
