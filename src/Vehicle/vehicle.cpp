#include "vehicle.h"
#include <algorithm>

#include <climits>


unsigned int Vehicle::id = 1;


Vehicle::Vehicle(){
    this->maxCap = LONG_MAX;
    this->currentLoad = 0;
    setId(id++);
}


Vehicle::Vehicle(unsigned long int maxCap){
    this->maxCap = maxCap;
    this->currentLoad = 0;
    setId(id++);
}


void Vehicle::setId(unsigned int uniqueId){
    this->uniqueId = uniqueId;
}


unsigned int Vehicle::getId(){
    return uniqueId;
}

void Vehicle::setMaxCap(unsigned long int maxCap){
    this->maxCap = maxCap;
}


unsigned long int Vehicle::getMaxCap(){
    return maxCap;
}


bool Vehicle::addBasket(Basket* basket){
    if (findBasket(basket->getNumFat()) != nullptr) return false;
    if (basket->getNumPack() > (maxCap - currentLoad)) return false;
    baskets.push_back(basket);
    currentLoad += basket->getNumPack();
    return true;
}


Basket* Vehicle::findBasket(unsigned long int numFat){
    auto basket_ptr = std::find_if(baskets.begin(), baskets.end(), [&numFat](Basket* basket){ return basket->getNumFat() == numFat;});
    if (basket_ptr == baskets.end()) return nullptr;
    else return (*basket_ptr);
}


std::vector<Basket*> Vehicle::getBaskets(){
    return baskets;
}

bool Vehicle::removeBasket(unsigned long int numFat){
    Basket* basket = findBasket(numFat);
    if (basket == nullptr){
        return false;
    }
    else{
        baskets.erase(std::find(baskets.begin(), baskets.end(), basket));
        return true;
    }
}


void Vehicle::clearBaskets(){
    baskets.clear();
    currentLoad = 0;
}


unsigned long Vehicle::getCurrentLoad() const {
    return currentLoad;
}


void Vehicle::setCurrentLoad(unsigned long currentLoad) {
    Vehicle::currentLoad = currentLoad;
}


const std::vector<unsigned long> &Vehicle::getPathList() const {
    return path_list;
}


void Vehicle::setPathList(const std::vector<unsigned long> &pathList) {
    path_list = pathList;
}


void Vehicle::addVertex(unsigned long path) {
    this->path_list.push_back(path);
}

void Vehicle::addPath(std::vector<unsigned long int> path){
    for (auto elem : path){
        this->path.push_back(elem);
    }
}

std::vector<unsigned long int> Vehicle::getPath(){
    return path;
}






