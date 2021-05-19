#include "company.h"
#include <algorithm>

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

