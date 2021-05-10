#include "company.h"
#include <algorithm>

bool Company::addVehicle(Vehicle* vehicle){
    if (findVehicle(vehicle->getId()) != nullptr) return false;
    fleet.push_back(vehicle);
    return true;
}

Vehicle* Company::findVehicle(unsigned int id){
    auto vehicle_ptr = std::find_if(fleet.begin(), fleet.end(), [&id](Vehicle* vehicle){ return vehicle->getId() == id;});
    if (vehicle_ptr == fleet.end()) return nullptr;
    else return (*vehicle_ptr);
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

