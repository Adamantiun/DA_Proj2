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
};
#endif //PROJ1_SYSTEM_H

