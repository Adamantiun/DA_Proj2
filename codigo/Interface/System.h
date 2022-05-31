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

    void changeMap();

    void nDivCase1(int ori, int dest, int groupSize);

    void nDivCase2(int ori, int dest);

    void nDivCase3(int ori, int dest);

    void divCase1(int ori, int dest, int groupSize);

    void divCase2(int ori, int dest);

    string ftos(float n, int i);
};
#endif //PROJ1_SYSTEM_H

