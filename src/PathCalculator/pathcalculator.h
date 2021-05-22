#ifndef _PATHCALCULATOR_H_
#define _PATHCALCULATOR_H_

#include "../Company/company.h"
#include "../Graph/Graph.h"

template<class T>
class PathCalculator{
private:
    Company *company;
    Graph<T> *graph;
    void setDistances(Vehicle* vehicle, double latitude, double longitude);
    Vertex<T>* getMinDistance(Vehicle* vehicle);
public:
    PathCalculator(Company *company, Graph<T> *graph);
    bool getPaths();
};

template<class T>
void PathCalculator<T>::setDistances(Vehicle* vehicle, double latitude, double longitude){
    for (Basket* basket : vehicle->getBaskets()){
        Vertex<T> *vertex = graph->findVertex(basket->getIdDest());
        if (vertex == NULL) return false;
        double dist = haversine(latitude, longitude, vertex->getLatitude(), vertex->getLongitude());
        basket.setDist(dist);
    }
}

template<class T>
Basket* PathCalculator<T>::getMinDistance(Vehicle* vehicle){
    Basket* min = vehicle->getBaskets()[0];
    for (Basket* basket : vehicle->getBaskets()){
        if (basket->getDist() < min->getDist()){
            min = basket;
        }
    }
    return min;
}

template<class T>
PathCalculator<T>::PathCalculator(Company *company, Graph<T> *graph){
    this->company = company;
    this->graph = graph;
}

template<class T>
bool PathCalculator<T>::getPaths() {
    std::pair<unsigned long int, unsigned long int> pair;
    for (Vehicle *vehicle : company->getFleet()){
        Vertex<T> *curr = graph->getDepot();
        while(!vehicle->getBaskets().empty()){
            setDistances(vehicle, curr->getLatitude(), curr->getLongitude());
            Basket* min = getMinDistance(vehicle);
            Vertex<T>* dest = graph->findVertex(min->getIdDest());
            if (dest == NULL) return false;
            if (!graph->aStarShortestPath(curr->getInfo(), dest->getInfo())) return false;
            pair = {curr->getInfo(), dest->getInfo()};
            vehicle->addPath(pair);
            vehicle->removeBasket(min->getNumFat());
            curr = dest;
        }
    }
    return true;
}

#endif //_PATHCALCULATOR_H_
