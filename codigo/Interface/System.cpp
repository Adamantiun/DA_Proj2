// ****************************************************************************************************
// ****************************************** SYSTEM_CPP__ ********************************************
// ****************************************************************************************************

#include "System.h"
#include <string>
#include <iostream>
#include <regex>

using namespace std;

void System::clearScreen() {
    cout << string(50, '\n');
};


System::System() {

    controller = Controller();
    controller.readInput(1);
    Menu baseMenu = Menu(controller);
    baseMenu.setMainOps({"Staff Optimizing", "Profit Optimizing", "Express Deliveries"});

    while(true) {
        int opt1 = baseMenu.printOptionsMenu({"Get route","Change map"}, "Welcome! What would you like to do?");
        if(opt1 == 1){
            changeMap();
            continue;
        }
        int ori = stoi(baseMenu.intInputMenu("Where are you coming from?"));
        while(!controller.getGraph().has(ori)){
            ori = stoi(baseMenu.intInputMenu("Where are you coming from?", "This stop does not exist!"));
        }
        int dest = stoi(baseMenu.intInputMenu("Where would you like to go?"));
        while(!controller.getGraph().has(dest)){
            dest = stoi(baseMenu.intInputMenu("Where would you like to go?", "This stop does not exist!"));
        }
        int opt2 = baseMenu.printOptionsMenu({"Yes", "No", "Go back"},"Are you willing to split your group?");
        if(opt2 == 2)
            continue;
        int opt3;
        if(opt2 == 1){
            opt3 = baseMenu.printOptionsMenu({"I have a set number of people to take",
                                       "How many people can I take?", "What is the most efficient path?", "Go back"});
            if(opt3 == 3)
                continue;
            if(opt3 == 0){
                int np = stoi(baseMenu.intInputMenu("How manny people are you taking?"));
                nDivCase1(ori, dest, np);
                continue;
            }
            if(opt3 == 1)
                nDivCase2(ori, dest);
            else
                nDivCase3(ori, dest);
            continue;
        }
        if(opt2 == 0){
            opt3 = baseMenu.printOptionsMenu({"I have a set number of people to take",
                                              "How many people can I take? On which path?", "Go back"});
            if(opt3 == 2)
                continue;
            if(opt3 == 0){
                int np = stoi(baseMenu.intInputMenu("How manny people are you taking?"));
                divCase1(ori, dest, np);
                continue;
            }
            divCase2(ori, dest);
            continue;
        }
        if (opt1 == 69) break;
    }
}

void System::changeMap() {
    Menu changeMapMenu = Menu(controller);

    string orderOption = changeMapMenu.intInputMenu("Please select the map!");
    while(!controller.readInput(stoi(orderOption)))
        orderOption = changeMapMenu.intInputMenu("Please select the map!", "This map does not exists!");
}

void System::nDivCase1(int ori, int dest, int groupSize) {

}

void System::nDivCase2(int ori, int dest) {

}

void System::nDivCase3(int ori, int dest) {

}

void System::divCase1(int ori, int dest, int groupSize) {

}

void System::divCase2(int ori, int dest) {

}


