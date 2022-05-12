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

    Menu baseMenu = Menu(controller);
    baseMenu.setMainOps({"Staff Optimizing", "Profit Optimizing", "Express Deliveries"});

    while(true) {
        string orderOption = baseMenu.intInputMenu("Hello! Please select an input to process!");
        vector<string> usedInputs;
        while(!controller.readInput(stoi(orderOption)))
            orderOption = baseMenu.intInputMenu("Please select an input to process!", "This input does not exists!");
        usedInputs.push_back(orderOption);
        orderOption = baseMenu.anyInputMenu("If you would like, select another input to process!\nOr type 'C' to continue!");
        while(orderOption!="C" && orderOption!="c"){
            if(find(usedInputs.begin(), usedInputs.end(), orderOption) != usedInputs.end()){
                orderOption = baseMenu.anyInputMenu("If you would like, select another input to process!\nOr type 'C' to continue!", "This input has already been requested!");
                continue;
            }
            if(!baseMenu.is_number(orderOption) || !controller.readInput(stoi(orderOption)))
                orderOption = baseMenu.anyInputMenu("If you would like, select another input to process!\nOr type 'C' to continue!", "Invalid Input!");
            else{
                usedInputs.push_back(orderOption);
                orderOption = baseMenu.anyInputMenu("If you would like, select another input to process!\nOr type 'C' to continue!");
            }
        }

        if (orderOption == "x") break;
    }
}


