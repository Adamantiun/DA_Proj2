// ****************************************************************************************************
// ****************************************** CONTROLLER_CPP__ ****************************************
// ****************************************************************************************************

#include "Controller.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <xmath.h>
#include <functional>
#include <chrono>


Controller::Controller() {
    readTrucks();
}

void Controller::readTrucks() {
    truckDB.clear();
    ifstream trucksFile;
    trucksFile.open("../input/trucks");
    if (trucksFile.fail()) {
        cout << "This file doesn't exist!\n";
    }
    else {
        string line;
        getline(trucksFile,line);
        while (!trucksFile.eof() && trucksFile.peek()!='\n') {
            Truck truck = Truck();
            getline(trucksFile,line, ' ');
            truck.setId(stoi(line));
            getline(trucksFile,line, ' ');
            truck.setVolMax(stoi(line));
            getline(trucksFile,line, ' ');
            truck.setWeightMax(stoi(line));
            getline(trucksFile,line);
            truck.setCost(stoi(line));
            truckDB.push_back(truck);
        }
        trucksFile.close();
    }
}

bool Controller::readOrders(int orderNo) {
    ifstream ordersFile;
    ordersFile.open("../input/orders" + to_string(orderNo));
    if (ordersFile.fail()) {
        return false;
    }
    string line;
    getline(ordersFile,line);
    while (!ordersFile.eof() && ordersFile.peek()!='\n') {
        Order order = Order();
        getline(ordersFile,line, ' ');
        order.setId(stoi(line));
        getline(ordersFile,line, ' ');
        order.setVol(stoi(line));
        getline(ordersFile,line, ' ');
        order.setWeight(stoi(line));
        getline(ordersFile,line, ' ');
        order.setReward(stoi(line));
        getline(ordersFile,line);
        order.setDuration(stoi(line));
        orderDB.push_back(order);
    }
    ordersFile.close();
    return true;
}

Controller::~Controller(){
    truckDB.clear();
    orderDB.clear();
}

vector<Order> Controller::getOrders() {
    return orderDB;
}

vector<Truck>& Controller::getTrucks() {
    return truckDB;
}

void Controller::clearOrders(){
    orderDB.clear();
}


void Controller::addTruck(int id,int volMax, int weightMax, int cost) {
    Truck truck = Truck(id, volMax,weightMax,cost);
    truckDB.push_back(truck);
}

void Controller::addOrder(int id, int vol, int weight, int reward, int duration) {
    Order order = Order(id, vol,weight,reward,duration);
    orderDB.push_back(order);
}

vector<Order> Controller::scenery3(int& getMeanTime){
    vector<Order> res;
    vector<Order> aux = orderDB;
    sort(aux.begin(),aux.end(), [](const Order &a, const Order &b) {
        return a.getDuration() < b.getDuration();});
    int total=0;
    int time=28800;
    getMeanTime = 0;
    int i;
    for(i=0; i<aux.size(); i++){
        if(total + aux[i].getDuration() >time){break;}
        total+=aux[i].getDuration();
        getMeanTime += total;
        res.push_back(aux[i]);
    }
    getMeanTime/=i;
    return res;
}



void Controller::SetOrderByWeight(vector<Order> &orderdb){
    auto cmp = [] (Order order1, Order order2){ return order1.getWeight()>order2.getWeight();};
    sort(orderdb.begin(), orderdb.end(),cmp);
    for(int i = 0; i<orderdb.size();i++){
        orderdb[i].setRankingWei(i);
    }
}
void Controller::SetOrderByVolume(vector<Order> &orderdbyVol){
    auto cmpVol = [] (Order order1, Order order2){return order1.getVol()>order2.getVol();};
    sort(orderdbyVol.begin(),orderdbyVol.end(),cmpVol);
    //estabeleco uma especie de ranking pelo volume
    for(int i = 0; i<orderdbyVol.size();i++){
        orderdbyVol[i].setRankingVol(i);
    }
}
void Controller::SetTruckRankingWeight(vector<Truck> &truckdb){
    auto cmpTruck = [] ( Truck truck1, Truck truck2 ) {return truck1.getWeightMax()>truck2.getWeightMax();};
    sort(truckdb.begin(), truckdb.end(),cmpTruck);
    //estabeleco uma especie de ranking pelo peso
    for(int i = 0; i<truckdb.size();i++){
        truckdb[i].setRankingWei(i);
    }
    }
void Controller::SetTruckRankingVol(vector<Truck> &truckdb){
    auto cmpTruckByVol = [] ( Truck truck1, Truck truck2 ) {return truck1.getVolMax()>truck2.getVolMax();};
    sort(truckdb.begin(),truckdb.end(),cmpTruckByVol);
    //estabeleco uma especie de ranking pelo volume
    for(int i = 0; i<truckdb.size();i++){
        truckdb[i].setRankingVol(i);
    }
}
void Controller::SetTruckRankingCost(vector<Truck> &truckdb){
    auto cmpTruckByCost = [] ( Truck truck1, Truck truck2 ) {return truck1.getCost()<truck2.getCost();};
    sort(truckdb.begin(),truckdb.end(),cmpTruckByCost);
    //estabeleco uma especie de ranking pelo volume
    for(int i = 0; i<truckdb.size();i++){
        truckdb[i].setRankingCost(i);
    }
}
vector<Truck> Controller::scenery1(){
    chrono::steady_clock sc;
    auto start = sc.now();
    //SORT ORDERS
    auto cmpRak = [this]  (Order order1, Order order2){return (order1.getRankingWei()+order1.getRankingVol())/2.0<(order2.getRankingWei()+order2.getRankingVol())/2.0 ;};
    vector<Order> orderdb = orderDB;
    SetOrderByWeight(orderdb);
    SetOrderByVolume(orderdb);
    sort(orderdb.begin(),orderdb.end(),cmpRak);
    //*SORT TRUCKS
    auto cmpTruckRak = [this]  (Truck truck1, Truck truck2){return (truck1.getRankingWei()+truck1.getRankingVol())/2.0<(truck2.getRankingWei()+truck2.getRankingVol())/2.0 ;};
    vector<Truck> truckByRanking = truckDB;
    SetTruckRankingWeight(truckByRanking);
    auto vec3 = truckByRanking;
    SetTruckRankingVol(truckByRanking);
    auto vec2 = truckByRanking;

    sort(truckByRanking.begin(),truckByRanking.end(),cmpTruckRak);
    int n = orderdb.size();
    int j = 0;
    set<int> ids;
    set<int> trucksIDS;
    vector<Truck> trucksUsed;
    for (int i = 0; i < n; i++) {
        if(orderdb[i].getWeight()>vec3[0].getWeightMax() || orderdb[i].getVol()> vec2[0].getVolMax()){
            continue;
        }
        if (orderdb[i].getWeight() > truckByRanking[j].getWeightMax() ||orderdb[i].getVol() > truckByRanking[j].getVolMax()  ) {
            j=(j!=(truckByRanking.size()-1)) ? ++j:(truckByRanking.size()-1);
            if(j != (truckByRanking.size() - 1) ){
                j++;
                i--;
            }
            else {
                j = (truckByRanking.size()-1);
            }
        }
        else {
            ids.insert(j);
            trucksIDS.insert(truckByRanking[j].getId());
            truckByRanking[j].setWeightMax(truckByRanking[j].getWeightMax() - orderdb[i].getWeight());
            truckByRanking[j].setVolMax(truckByRanking[j].getVolMax() - orderdb[i].getVol());
            truckByRanking[j].addOrder(orderdb[i]);
            j = 0;
        }
    }
    for(auto x:ids){
        trucksUsed.push_back(truckByRanking[x]);
    }
    return trucksUsed;
}


int Controller::processTruck(Truck &truck){
    if (truck.getVolMax() <= 0 || truck.getWeightMax()<=0) {
        return 0;
    }
    int n = orderDB.size();
    vector<vector<vector<int>>>dp(n, vector<vector<int>>(truck.getWeightMax() + 1,vector<int>(truck.getVolMax()+1)));
    for (int i = 0; i < n; i++) {
        dp[i][0][0] = 0;
    }
    for (int c = 0; c <= truck.getWeightMax(); c++) {
        for(int j= 0; j<= truck.getVolMax();j++){
            if (orderDB[0].getWeight() <= c && orderDB[0].getVol() <= j) {
                dp[0][c][j] = orderDB[0].getReward();
            }
        }
    }
    for (int i = 1; i < n; i++) {
        for (int c = 1; c <= truck.getWeightMax() ; c++) {
            for(int j = 1; j <= truck.getVolMax(); j++){
                int profit1 = 0, profit2 = 0;
                if (orderDB[i].getWeight() <= c && orderDB[i].getVol()<=j) {
                    profit1 = orderDB[i].getReward() + dp[i - 1][c - orderDB[i].getWeight()][j - orderDB[i].getVol()];
                }
                profit2 = dp[i - 1][c][j];
                dp[i][c][j] = max(profit1, profit2);
            }
        }
    }
    int totalProfit = dp[orderDB.size() - 1][truck.getWeightMax()][truck.getVolMax()];
    processSelectedOrders(dp, truck);
    return totalProfit;
}
void Controller::processSelectedOrders(vector<vector<vector<int>>> &dp, Truck &truck) {
    ///This function processes the orders to be added to the truck and taken for the orders DB
    int totalProfit = dp[orderDB.size() - 1][truck.getWeightMax()][truck.getVolMax()];

    for (int i = orderDB.size() - 1; i > 0; i--) {
        if (totalProfit != dp[i - 1][ truck.getWeightMax()][truck.getVolMax()]) {
            truck.addOrder(orderDB[i]);
            truck.setWeightMax(truck.getWeightMax()- orderDB[i].getWeight());
            truck.setVolMax(truck.getVolMax()- orderDB[i].getVol());
            totalProfit -= orderDB[i].getReward();
            orderDB.erase(orderDB.begin()+i);
            i++;
        }
    }



    if (totalProfit != 0) {
        truckDB[0].addOrder(orderDB[0]);
        orderDB.erase(orderDB.begin());
    }
}

void Controller :: sortTruckDBforS2(){
    sort(truckDB.begin(), truckDB.end(), compareCostBenefit);
}

bool Controller::compareCostBenefit(const Truck &t1, const Truck &t2) {
    return (t1.getWeightMax()*t1.getVolMax()/t1.getCost()) < (t2.getWeightMax()*t2.getVolMax()/t2.getCost());
}

vector<Truck> Controller::scenery2(int& getProfit){
    chrono::steady_clock sc;
    auto start = sc.now();
    sortTruckDBforS2(); //sort based on volume*weight/cost
    int total = 0; //profit counter
    vector<Truck> usedTrucks; //used trucks, returned for interface processing
    int i = 0; //current truck index

    while(!orderDB.empty() && i<truckDB.size()) {
        int reward = processTruck(truckDB[i]);

        if (reward == 0) { //no reward: skip truck
            i++;
            continue;
        }
        int cost = truckDB[i].getCost();
        int profit = reward - cost;
        if (profit <= 0) { //negative profit: return all orders and go to next truck
            for( auto order : truckDB[i].getOrdersInside() )
                orderDB.push_back(order);
                truckDB[i].emptyTruck();
                continue;
        }
        total += profit;
        usedTrucks.push_back(truckDB[i]);
        i++;
    }
    getProfit = total; // setting given int as Total profit to be shown to user


    auto end = sc.now();
    auto time_span = static_cast<chrono::duration<double>>(end - start);
    cout<<"Operation took: "<<time_span.count()<<" seconds !!!\n";
    return usedTrucks;
}

void Controller::clearTrucks() {
    for(auto &t: truckDB)
        t.emptyTruck();
}





