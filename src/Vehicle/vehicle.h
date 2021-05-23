#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "../Basket/basket.h"
#include <vector>


class Vehicle{
private:
    static unsigned int id; /**<Id Counter*/
    unsigned int uniqueId;
    unsigned long int maxCap;
    unsigned long int currentLoad;
    /**<The current load that the vehicle carries*/
    std::vector<Basket*> baskets; /**<List of baskets inside the vehicle*/
    std::vector<std::pair<unsigned long int , unsigned long int>> path;
    std::vector<unsigned long int> path_list = {};


public:
    /**
     * Vehicle's default constructor that will set the maxCap to infinity (i.e., LONG_MAX)
     */
    Vehicle();
    /**
     * Vehicle's constructor
     * @param maxCap The maximum capacity that a vehicle can carry (1 unity corresponds to 1 package from the basket)
     */
    Vehicle(unsigned long int maxCap);
    /**
     * Sets the vehicle unique id
     * @param uniqueId The unique id of the vehicle
     */
    void setId(unsigned int uniqueId);
    /**
     * Returns the unique id of the vehicle
     * @return
     */
    unsigned int getId();
    /**
     * Sets the current maximum capacity of the vehicle
     * @param maxCap
     */
    void setMaxCap(unsigned long int maxCap);
    /**
     * Returns the current maximum capacity of the vehicle
     * @return
     */
    unsigned long int getMaxCap();
    /**
     * Adds a basket to the list of baskets that the vehicle will carry
     * @param basket The basket to be added
     * @return This function will return true if the basket was sucessfully added to the list, it will return false, otherwise
     */
    bool addBasket(Basket* basket);
    /**
     * Searches the current list of vehicle baskets if the basket exists
     * @param numFat Bill number, since it is unique, which will be used in the search for the basket
     * @return This function will return true if the basket was sucessfully found, it will return false, otherwise
     */
    Basket* findBasket(unsigned long int numFat);

    std::vector<Basket*> getBaskets();

    void addPath(std::pair<unsigned long int, unsigned long int> path);

    bool removeBasket(unsigned long int numFat);

    /**
     * Will remove every basket from the list
     */
    void clearBaskets();

    unsigned long getCurrentLoad() const;

    void setCurrentLoad(unsigned long currentLoad);

    const std::vector<unsigned long> &getPathList() const;

    void setPathList(const std::vector<unsigned long> &pathList);

    void addPath( unsigned long path);

    bool isInPath(unsigned long path);

};

#endif //_VEHICLE_H_
