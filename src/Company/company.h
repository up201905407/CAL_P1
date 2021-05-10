#ifndef _COMPANY_H_
#define _COMPANY_H_

#include "../Vehicle/vehicle.h"

class Company{
private:
    std::vector<Vehicle*> fleet;
public:
    bool addVehicle(Vehicle* vehicle);
    Vehicle* findVehicle(unsigned int id);
    bool removeVehicle(unsigned int id);


};

#endif //_COMPANY_H_
