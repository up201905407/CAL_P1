#include <iostream>
#include "src/Vehicle/vehicle.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Basket basket("Luis",1, 1, 1);
    Basket basket2("Luis",1, 1, 2);
    Basket basket3("Luis",1, 1, 2);
    Vehicle vehicle;
    std::cout << vehicle.addBasket(&basket) << std::endl;
    std::cout << vehicle.addBasket(&basket) << std::endl;
    std::cout << vehicle.addBasket(&basket2) << std::endl;
    std::cout << vehicle.addBasket(&basket3) << std::endl;
    return 0;
}
