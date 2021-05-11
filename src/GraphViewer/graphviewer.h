#ifndef _GRAPHVIEWER_H_
#define _GRAPHVIEWER_H_

#include "../Graph/Graph.h"

template<class T>
class GraphViewer{
private:
    Graph<T>* graph;
public:
    GraphViewer(Graph<T>* graph);


};

template<class T>
GraphViewer<T>::GraphViewer<class T>(Graph<T> *graph) {
    this->graph = graph;
}

#endif //_GRAPHVIEWER_H_
