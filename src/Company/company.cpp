#include "company.h"
#include <algorithm>

Company::Company(double latitude, double longitude){
    this->latitude = latitude;
    this->longitude = longitude;
}

double Company::getLatitude(){
    return latitude;
}

double Company::getLongitude(){
    return longitude;
}

bool Company::addVehicle(Vehicle* vehicle){
    if (findVehicle(vehicle->getId()) != nullptr) return false;
    fleet.push_back(vehicle);
    return true;
}

bool Company::addBasket(Basket* basket){
    if (findBasket(basket->getNumFat()) != nullptr) return false;
    baskets.push_back(basket);
    return true;
}

std::vector<Vehicle*> Company::getFleet(){
    return fleet;
}

Vehicle* Company::findVehicle(unsigned int id){
    auto vehicle_ptr = std::find_if(fleet.begin(), fleet.end(), [&id](Vehicle* vehicle){ return vehicle->getId() == id;});
    if (vehicle_ptr == fleet.end()) return nullptr;
    else return (*vehicle_ptr);
}

Basket* Company::findBasket(unsigned long int numFat){
    auto basket_ptr = std::find_if(baskets.begin(), baskets.end(), [&numFat](Basket* basket){ return basket->getNumFat() == numFat;});
    if (basket_ptr == baskets.end()) return nullptr;
    else return (*basket_ptr);
}

bool Company::removeVehicle(unsigned int id){
    Vehicle* vehicle = findVehicle(id);
    if (vehicle == nullptr){
        return false;
    }
    else{
        fleet.erase(std::find(fleet.begin(), fleet.end(), vehicle));
        return true;
    }
}

bool Company::removeBasket(unsigned long int numFat){
    Basket* basket = findBasket(numFat);
    if (basket == nullptr){
        return false;
    }
    else{
        baskets.erase(std::find(baskets.begin(), baskets.end(), basket));
        return true;
    }
}

bool Company::distributeBasketsByVehicles() {
    std::vector<Basket*> basketsBackup;
    std::sort(fleet.begin(), fleet.end(), [](Vehicle *v1, Vehicle *v2){return v1->getMaxCap() > v2->getMaxCap();});
    std::sort(baskets.begin(), baskets.end(), [](Basket *b1, Basket *b2){return b1->getNumPack() > b2->getNumPack();});
    for (Basket* basket : baskets){
        basketsBackup.push_back(basket);
    }
    for (Vehicle * vehicle : fleet){
        for (Basket* basket : baskets){
            if (vehicle->addBasket(basket))
                removeBasket(basket->getNumFat());
        }
    }
    if (baskets.empty()){
        return true;
    }
    else {
        baskets.clear();
        for (Basket *basket : basketsBackup) {
            baskets.push_back(basket);
        }
        return false;
    }
}
