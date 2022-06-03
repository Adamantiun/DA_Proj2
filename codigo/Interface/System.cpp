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
        if(controller.getGraph().pathMaxCapacity(ori, dest) == 0){
            baseMenu.singleInputScreen("Sorry, but there's no path between those stops");
            continue;
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
        if (opt1 == 4) break;
    }
}

void System::changeMap() {
    Menu changeMapMenu = Menu(controller);

    string orderOption = changeMapMenu.intInputMenu("Please select the map!");
    while(!controller.readInput(stoi(orderOption)))
        orderOption = changeMapMenu.intInputMenu("Please select the map!", "This map does not exists!");
}

void System::nDivCase1(int ori, int dest, int groupSize) {
    Menu tempMenu = Menu(controller);
    if(groupSize > controller.getGraph().pathMaxCapacity(ori, dest)){
        tempMenu.singleInputScreen("Sorry, but you can't take that many people!");
        return;
    }
    string message = controller.getPrintableDikjCapacity(ori, dest, groupSize);
    tempMenu.singleInputScreen(message);
}

void System::nDivCase2(int ori, int dest) {
    Menu tempMenu = Menu(controller);
    int groupSize = controller.getGraph().pathMaxCapacity(ori, dest);
    if(tempMenu.printOptionsMenu({"Get path for that group size", "Go back"},
                              "You can take up to " + to_string(groupSize) + " people") == 1)
        return;
    string message = controller.getPrintableDikjCapacity(ori, dest, groupSize);
    tempMenu.singleInputScreen(message);
}

void System::nDivCase3(int ori, int dest) {
    Menu tempMenu = Menu(controller);
    float n = 0;
    vector<string> opts = controller.getEquiEfficientOpts(ori, dest, n);

    int op1 = tempMenu.printOptionsMenu(opts,
                              "Here are the most efficient paths, \nwith " + ftos(n, 2)  + " bus rides per person:");
    int groupSize = controller.getSizeAtIndex(op1);
    string message = controller.getPrintableDikjCapacity(ori, dest, groupSize);
    tempMenu.singleInputScreen(message);
}

void System::divCase1(int ori, int dest, int groupSize) {

}

void System::divCase2(int ori, int dest) {
    Menu tempMenu(controller);
    string message = controller.getPrintableMaxFlow(ori, dest);
    tempMenu.singleInputScreen(message);
}

string System::ftos(float n, int i) {
    string ret = "";
    string s = to_string(n);
    int j = 0;
    while(j<s.size() && s[j]!='.')
        ret.push_back(s[j++]);
    if(i == 0)
        return ret;
    ret.push_back(s[j++]);
    for(int k = 0; k < i; k++)
        ret.push_back(s[j++]);
    while (ret[--j] == '0') {
        ret.resize(ret.size() - 1);
    }
    if(ret[j] == '.')
        ret.resize(ret.size()-1);
    return ret;
}


