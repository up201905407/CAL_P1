
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <set>
#include <climits>
#include "MutablePriorityQueue.h"
#include "../Utils/utils.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    double latitude;                 //latitude of the vertex
    double longitude;                 //longitude of the vertex
    std::vector<Edge<T>> adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    Edge<T> *edge_path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    int index = INT_MAX;   //auxiliary field - Tarjans strongly Connected
    bool isOnStack = false;  //auxiliary field - Tarjans strongly Connected
    int lowlink = INT_MAX;  //auxiliary field - Tarjans strongly Connected
    void addEdge(T in, Vertex<T> *dest, double w);

public:
    Vertex(T in, double lat, double lon);
    T getInfo() const;
    double getLatitude() const;
    double getLongitude() const;
    double getDist() const;
    Vertex *getPath() const;
    std::vector<Edge<T>> getAdj() const;
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in, double lat, double lon): info(in), latitude(lat), longitude(lon) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(T in, Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(in, d, w));
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
double Vertex<T>::getLatitude() const {
    return latitude;
}

template <class T>
double Vertex<T>::getLongitude() const {
    return longitude;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

template<class T>
std::vector<Edge<T>> Vertex<T>::getAdj() const {
    return adj;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    T info;
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(T in, Vertex<T> *d, double w);
    T getInfo() const;
    Vertex<T>* getDest();
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(T in, Vertex<T> *d, double w): info(in), dest(d), weight(w) {}

template<class T>
T Edge<T>::getInfo() const{
    return info;
}

template<class T>
Vertex<T>* Edge<T>::getDest(){
    return dest;
}

/*************************** Graph  **************************/

template <class T>
class Graph {
    Vertex<T> *depot;
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    std::vector<std::vector<int>> D_Floyd_Warshall;
    std::vector<std::vector<int>> P_Floyd_Warshall;

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in, const double &lat, const double &lon);
    bool addEdge(const T &info, const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;
    void dfsVisit(Vertex<T> *v, std::vector<T> & res) const;
    std::vector<T> dfs(T item) const;
    bool dijkstraShortestPath(const T &origin, const T& destiny);
    bool aStarShortestPath(const T &origin, const T& destiny);
    std::vector<T> getPath(const T &origin, const T &dest) const;
    std::set<std::set<T>> getTarjanStronglyConnectedVertex();
    void strongConnect(Vertex<T> *v ,std::stack<Vertex<T>*> &stack, int &index, std::set<std::set<T>> &results);
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
 *  Adds a vertex with a given content or info (in) to a Graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in, const double &lat, const double &lon) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in, lat, lon));
    return true;
}

/*
 * Adds an edge to a Graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &in, const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(in, v2,w);
    return true;
}

/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a Graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::dfs(T value) const {
    // TODO (7 lines)
    std::vector<T> res;

    for ( auto item : vertexSet) {
        item->visited = false;
    }

    if(!findVertex(value)->visited)
        dfsVisit(findVertex(value),res);


    return res;

}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> & res) const {
    v->visited=true;
    res.push_back(v->info);

    for(auto edge: v->adj)
        if(!edge.dest->visited)
            dfsVisit(edge.dest,res);

    return;
}

template<class T>
bool Graph<T>::dijkstraShortestPath(const T &origin, const T& destiny) {
    for (Vertex<T>* vertex : vertexSet){
        vertex->dist = INF;
        vertex->path = nullptr;
    }
    std::queue<Vertex<T>*> queueVertex;
    Vertex<T>* curr = findVertex(origin);
    Vertex<T>* dest = findVertex(destiny);
    if (curr == NULL || dest == NULL || vertexSet.empty()) return false;
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
    return dest->dist != INF;
}

template<class T>
bool Graph<T>::aStarShortestPath(const T &origin, const T &destiny) {
    for (Vertex<T>* vertex : vertexSet){
        vertex->dist = INF;
        vertex->path = nullptr;
    }
    std::queue<Vertex<T>*> queueVertex;
    Vertex<T>* curr = findVertex(origin);
    Vertex<T>* dest = findVertex(destiny);
    if (curr == NULL || dest == NULL || vertexSet.empty()) return false;
    curr->dist = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(curr);
    while(!q.empty()){
        curr = q.extractMin();
        for (Edge<T> &edge : curr->adj){
            if (edge.dest->dist > curr->dist + edge.weight){
                bool wasAlreadyAdded = edge.dest->dist != INF;
                edge.dest->dist = curr->dist + edge.weight + haversine(curr->getLatitude(), curr->getLongitude(), dest->getLatitude(), dest->getLongitude());
                edge.dest->path = curr;
                edge.dest->edge_path = &edge;
                if (wasAlreadyAdded){
                    q.decreaseKey(edge.dest);
                } else {
                    q.insert(edge.dest);
                }
            }
        }
    }
    return dest->dist != INF;
}

template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    Vertex<T>* start = findVertex(origin);
    Vertex<T>* end = findVertex(dest);
    std::vector<T> edgesPath;
    edgesPath.push_back(end->edge_path->getInfo());
    Vertex<T>* curr = end;
    while(true){
        curr = curr->path;
        if (curr != start)
            edgesPath.push_back(curr->edge_path->getInfo());
        else
            break;
    }
    std::reverse(edgesPath.begin(), edgesPath.end());
    return edgesPath;
}

/*********************Strong Connected Vertexes****************************/

template<class T>
std::set<std::set<T>> Graph<T>::getTarjanStronglyConnectedVertex(){
    for(Vertex<T>* v : this->vertexSet){
        v->index = INT_MAX;
        v->isOnStack = false;
        v->lowlink = INT_MAX;
    }

    int index = 0;
    std::set<std::set<T>> results;
    std::stack<Vertex<T>*> stack;

    for(auto v : this->vertexSet){
        if(v->index==INT_MAX)
            strongConnect(v,stack,index,results);

    }
    return results;
}

template<class T>
void Graph<T>::strongConnect(Vertex<T>* v,std::stack<Vertex<T>*> &stack, int &index,std::set<std::set<T>> &results) {
    Vertex<T>* w;
    v->index = index;
    v->lowlink = index;
    index += 1;
    stack.push(v);
    v->isOnStack = true;

    for (Edge<T> e : v->adj){
        if (e.dest->index == INT_MAX) {
            strongConnect(e.dest, stack, index, results);
            v->lowlink = std::min(v->lowlink, e.dest->lowlink);
        } else if (e.dest->isOnStack) {
            v->lowlink = std::min(v->lowlink, e.dest->index);
        }
    }

    if(v->lowlink == v->index){
        std::set<T> str_component;
        do{
            w = stack.top();
            stack.pop();
            w->isOnStack = false;
            str_component.insert(w->info);
        }while(v!= w);
        if(str_component.size()>1) {
            results.insert(str_component);
        }
    }
}

#endif //_GRAPH_H_
