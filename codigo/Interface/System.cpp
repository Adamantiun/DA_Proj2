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
        controller.clearOrders();
        controller.readTrucks();
        string orderOption = baseMenu.intInputMenu("Hello! Please select an order to process!");
        vector<string> usedOrders;
        while(!controller.readOrders(stoi(orderOption)))
            orderOption = baseMenu.intInputMenu("Please select an order to process!", "This order does not exists!");
        usedOrders.push_back(orderOption);
        orderOption = baseMenu.anyInputMenu("If you would like, select another order to process!\nOr type 'C' to continue!");
        while(orderOption!="C" && orderOption!="c"){
            if(find(usedOrders.begin(), usedOrders.end(), orderOption)!=usedOrders.end()){
                orderOption = baseMenu.anyInputMenu("If you would like, select another order to process!\nOr type 'C' to continue!", "This order has already been requested!");
                continue;
            }
            if(!baseMenu.is_number(orderOption) || !controller.readOrders(stoi(orderOption)))
                orderOption = baseMenu.anyInputMenu("If you would like, select another order to process!\nOr type 'C' to continue!", "Invalid Input!");
            else{
                usedOrders.push_back(orderOption);
                orderOption = baseMenu.anyInputMenu("If you would like, select another order to process!\nOr type 'C' to continue!");
            }
        }
        int sceneryOption = baseMenu.printOptionsMenu(baseMenu.getMainOps(), "Please select a way to process your order");

        if(sceneryOption == 0){
            vector<Truck> trucksVec = controller.scenery1();
            baseMenu.singleInputScreen(getPrintableScenery1(trucksVec));
        }
        if(sceneryOption == 1){
            int totalProfit = 0;
            vector<Truck> trucksVec = controller.scenery2(totalProfit);
            baseMenu.singleInputScreen(getPrintableScenery2(trucksVec, totalProfit));
        }
        if(sceneryOption == 2){
            int meanTime = 0;
            vector<Order> ordersVec = controller.scenery3(meanTime);
            baseMenu.singleInputScreen(getPrintableScenery3(ordersVec, meanTime));
        }

        if (orderOption == "x") break;
    }
}

string System::getPrintableScenery3(const std::vector<Order>& orders, const int meanTime) {
    string ret = "Here are the Orders, by ID, arranged for delivery:\n";
    string line = "  ";
    for(auto o : orders){
        if(line.size()>=60){
            ret += line + "\n";
            line = "  ";
        }
        line += to_string(o.getId()) + ", ";
    }
    line.resize(line.size()-2);
    ret += line + "\nAverage delivery time estimated: " + to_string(meanTime);
    return ret;
}

string System::getPrintableScenery1(const vector<Truck> & trucks) {
    string ret = "Trucks and corresponding Orders to be delivered by ID:\n";
    for(auto t : trucks){
        ret += "-Truck " + to_string(t.getId()) + ":\n";
        string orders = "  ";
        for(auto o: t.getOrdersInside()){
            if(orders.size()>=60){
                ret += orders + "\n";
                orders = "  ";
            }
            orders += to_string(o.getId()) + ", ";
        }
        orders.resize(orders.size()-2);
        ret += orders + "\n";
    }
    ret.resize(ret.size()-1);
    return ret;
}

string System::getPrintableScenery2(const vector<Truck> & trucks, int profit) {
    string ret = getPrintableScenery1(trucks);
    ret += "\nTotal profit: " + to_string(profit);
    return ret;
}


