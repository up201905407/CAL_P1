#include "vehicle.h"
#include <algorithm>

#include <climits>

unsigned int Vehicle::id = 1;

Vehicle::Vehicle(){
    this->maxCap = LONG_MAX;
    setId(id++);
}

Vehicle::Vehicle(unsigned long int maxCap){
    this->maxCap = maxCap;
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

long int Vehicle::getMaxCap(){
    return maxCap;
}

bool Vehicle::addBasket(Basket* basket){
    if (findBasket(basket->getNumFat()) != nullptr) return false;
    baskets.push_back(basket);
    return true;
}

Basket* Vehicle::findBasket(unsigned long int numFat){
    auto basket_ptr = std::find_if(baskets.begin(), baskets.end(), [&numFat](Basket* basket){ return basket->getNumFat() == numFat;});
    if (basket_ptr == baskets.end()) return nullptr;
    else return (*basket_ptr);
}

void Vehicle::clearBaskets(){
    baskets.clear();
}

