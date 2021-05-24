#ifndef _COMPANY_H_
#define _COMPANY_H_

#include "../Vehicle/vehicle.h"


class Company{
private:
    unsigned long depotInfo;
    std::vector<Vehicle*> fleet;
    std::vector<Basket*> baskets;

public:
    /**
     * Company's constructor
     * @param depotId Localization of company
    */
    explicit Company(unsigned long depotId);
    /**
     * Adds new vehicle to the company's fleet
     * @param vehicle Vehicle to be added
     * @return This function will return true if the vehicle was sucessfully added, it will return false, otherwise
     */
    bool addVehicle(Vehicle* vehicle);
    /**
     * Adds a basket to the list of baskets that the vehicle will carry
     * @param basket The basket to be added
     * @return This function will return true if the basket was sucessfully added to the list, it will return false, otherwise
     */
    bool addBasket(Basket* basket);
    /**
     * Returns the list of vehicles
     * @return Vector with the list of vehicles
     */
    std::vector<Vehicle*> getFleet();
    /**
     * Getter function for baskets' vector
     * @return This function will return the vector of baskets
     */
    const std::vector<Basket*> &getBaskets() const;
    /**
     * Updates the list of baskets
     * @param baskets new vector with the list of baskets
     */
    void setBaskets(const std::vector<Basket*> &baskets);
    /**
     * Finds vehicle by id
     * @param id identification of vehicle
     * @return This function returns the vehicle specified by id
     */
    Vehicle* findVehicle(unsigned int id);
    /**
     * Finds basket by bill number
     * @param numFat Bill number
     * @return This function returns the basket specified by numFat
     */
    Basket* findBasket(unsigned long int numFat);
    /**
     * Finds basket by destination's Id
     * @param id Destination Id of basket
     * @return This function returns the basket specified by id
     */
    Basket * findBasketByDest(unsigned long id);
    /**
     * Deletes the vehicle specified by id
     * @param id Id of vehicle
     * @return This function will return true if the vehicle was sucessfully removed, it will return false, otherwise
     */
    bool removeVehicle(unsigned int id);
    /**
     * Deletes the basket specified by numFat
     * @param numFat Bill number
     * @return This function will return true if the basket was sucessfully removed, it will return false, otherwise
     */
    bool removeBasket(unsigned long int numFat);
    /**
     * Returns the Id of the localization of the company
     * @return Id of localization of the company
     */
    unsigned long getDepotInfo() const;
    /**
     * Updates the  of the company
     * @param depotInfo Localization of company
     */
    void setDepotInfo(unsigned long depotInfo);
};

#endif //_COMPANY_H_
