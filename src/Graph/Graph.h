
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    std::vector<std::vector<int>> D_Floyd_Warshall;
    std::vector<std::vector<int>> P_Floyd_Warshall;

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (Vertex<T>* vertex : vertexSet){
        vertex->dist = INF;
    }
    std::queue<Vertex<T>*> queueVertex;
    Vertex<T>* curr = findVertex(orig);
    if (curr == NULL || vertexSet.empty()) return;
    curr->dist = 0;
    queueVertex.push(curr);
    while(!queueVertex.empty()){
        curr = queueVertex.front();
        queueVertex.pop();
        for (Edge<T> edge : curr->adj){
            if (edge.dest->dist == INF){
                edge.dest->dist = curr->dist + 1;
                edge.dest->path = curr;
                queueVertex.push(edge.dest);
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (Vertex<T>* vertex : vertexSet){
        vertex->dist = INF;
        vertex->path = nullptr;
    }
    std::queue<Vertex<T>*> queueVertex;
    Vertex<T>* curr = findVertex(origin);
    if (curr == NULL || vertexSet.empty()) return;
    curr->dist = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(curr);
    while(!q.empty()){
        curr = q.extractMin();
        for (Edge<T> &edge : curr->adj){
            if (edge.dest->dist > curr->dist + edge.weight){
                bool wasAlreadyAdded = edge.dest->dist != INF;
                edge.dest->dist = curr->dist + edge.weight;
                edge.dest->path = curr;
                if (wasAlreadyAdded){
                    q.decreaseKey(edge.dest);
                } else {
                    q.insert(edge.dest);
                }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for (Vertex<T>* vertex : vertexSet){
        vertex->dist = INF;
        vertex->path = nullptr;
    }
    Vertex<T>* start = findVertex(orig);
    if (start == NULL || vertexSet.empty()) return;
    start->dist = 0;
    for (int i = 1; i <= vertexSet.size() -1 ; ++i){
        for (Vertex<T>* vertex : vertexSet){
            for (Edge<T> &edge : vertex->adj){
                if (edge.dest->dist > vertex->dist + edge.weight) {
                    edge.dest->dist = vertex->dist + edge.weight;
                    edge.dest->path = vertex;
                }
            }
        }
    }
    for (Vertex<T>* vertex : vertexSet){
        for (Edge<T> &edge : vertex->adj){
            if (vertex->dist + edge.weight < edge.dest->dist){
                throw std::logic_error("There are cycles of negative weight");
            }
        }
    }
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    Vertex<T>* start = findVertex(origin);
    Vertex<T>* end = findVertex(dest);
    std::vector<T> res;
    res.push_back(end->info);
    Vertex<T>* curr = end;
    while(curr != start){
        curr = curr->path;
        res.push_back(curr->info);
    }
    std::reverse(res.begin(), res.end());
    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    /*
    D_Floyd_Warshall = std::vector<std::vector<int>>(vertexSet.size(), std::vector<int>(vertexSet.size(), 0));
    P_Floyd_Warshall = std::vector<std::vector<int>>(vertexSet.size(), std::vector<int>(vertexSet.size(), 0));
    for (int i = 0; i < vertexSet.size(); i++) {
        for (int j = 0; j < vertexSet.size(); j++) {
            if (i == j) {
                D_Floyd_Warshall[i][j] = 0;
            }
            int weight = INF;
            for (Edge<T> &edge : vertexSet[i]->adj) {
                if (edge.dest == vertexSet[j]) {
                    weight = edge.weight;
                    break;
                }
            }
            D_Floyd_Warshall[i][j] = weight;
            if (weight != INF) {
                P_Floyd_Warshall[i][j] = j;
            }
        }
    }
    for(int k = 0; k < vertexSet.size(); k++) {
        for (int i = 0; i < vertexSet.size(); i++) {
            for (int j = 0; j < vertexSet.size(); j++) {
                if(D_Floyd_Warshall[i][k] + D_Floyd_Warshall[k][j] < D_Floyd_Warshall[i][j]){
                    D_Floyd_Warshall[i][j] = D_Floyd_Warshall[i][k] + D_Floyd_Warshall[k][j];
                    P_Floyd_Warshall[i][j] = P_Floyd_Warshall[i][k];
                }
            }
        }
    }*/
    D_Floyd_Warshall = std::vector<std::vector<int>>(vertexSet.size(), std::vector<int>(vertexSet.size(), 0));
    P_Floyd_Warshall = std::vector<std::vector<int>>(vertexSet.size(), std::vector<int>(vertexSet.size(), 0));
    for(size_t i = 0; i < vertexSet.size(); i++){
        for (size_t j = 0; j < vertexSet.size(); j++){
            if(i == j) D_Floyd_Warshall[i][j] = 0;
            int weight = INF;
            auto currentVertex = vertexSet[i];
            for(auto edge: currentVertex->adj){
                if(edge.dest == vertexSet[j]){
                    weight = edge.weight;
                    break;
                }
            }
            D_Floyd_Warshall[i][j] = weight;
            if(weight != INF) P_Floyd_Warshall[i][j] = j;
        }
    }
    for(size_t k = 0; k < vertexSet.size(); k++) {
        for (size_t i = 0; i < vertexSet.size(); i++) {
            for (size_t j = 0; j < vertexSet.size(); j++) {
                if(D_Floyd_Warshall[i][k] + D_Floyd_Warshall[k][j] < D_Floyd_Warshall[i][j]){
                    D_Floyd_Warshall[i][j] = D_Floyd_Warshall[i][k] + D_Floyd_Warshall[k][j];
                    P_Floyd_Warshall[i][j] = P_Floyd_Warshall[i][k];
                }
            }
        }
    }
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;

    auto currentVertex = findVertex(orig);
    auto destinationVertex = findVertex(dest);
    auto currentVertexIt = std::find(vertexSet.begin(), vertexSet.end(), currentVertex);
    auto destinationVertexIt = std::find(vertexSet.begin(), vertexSet.end(), destinationVertex);

    if(currentVertexIt == vertexSet.end() || destinationVertexIt == vertexSet.end()) return res;

    size_t currentIndex = std::distance(vertexSet.begin(), currentVertexIt);
    size_t destinationIndex = std::distance(vertexSet.begin(),destinationVertexIt);

    if(D_Floyd_Warshall[currentIndex][destinationIndex] == INF) return res;

    for(; currentIndex != destinationIndex; currentIndex = P_Floyd_Warshall[currentIndex][destinationIndex]){
        res.push_back(vertexSet.at(currentIndex)->info);
    }

    res.push_back(vertexSet.at(destinationIndex)->info);
    return res;
}


#endif //_GRAPH_H_
