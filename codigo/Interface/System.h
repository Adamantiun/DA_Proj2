// ****************************************************************************************************
// ****************************************** SYSTEM_H__ **********************************************
// ****************************************************************************************************

#ifndef PROJ1_SYSTEM_H
#define PROJ1_SYSTEM_H

#include <string>
#include "Menu.h"
#include "../Controller.h"
using namespace std;

class System{
private:
    Controller controller;
public:
    System();
    Controller& getController() {return controller;}
    static void clearScreen();
    string getPrintableScenery3(const std::vector<Order>&, const int meanTime);
    string getPrintableScenery1(const std::vector<Truck>&);
    string getPrintableScenery2(const vector<Truck> & trucks, int profit);
};
#endif //PROJ1_SYSTEM_H

