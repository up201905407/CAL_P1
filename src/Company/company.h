#ifndef _COMPANY_H_
#define _COMPANY_H_

#include "../Vehicle/vehicle.h"


class Company{
private:
    unsigned long depotInfo;
    std::vector<Vehicle*> fleet;
    std::vector<Basket*> baskets;

public:
    explicit Company(unsigned long depotId);
    bool addVehicle(Vehicle* vehicle);
    bool addBasket(Basket* basket);
    std::vector<Vehicle*> getFleet();
    const std::vector<Basket*> &getBaskets() const;
    void setBaskets(const std::vector<Basket*> &baskets);
    Vehicle* findVehicle(unsigned int id);
    Basket* findBasket(unsigned long int numFat);
    Basket * findBasketByDest(unsigned long id);
    bool removeVehicle(unsigned int id);
    bool removeBasket(unsigned long int numFat);
    bool distributeBasketsByVehicles();
    unsigned long getDepotInfo() const;
    void setDepotInfo(unsigned long depotInfo);

};

#endif //_COMPANY_H_
