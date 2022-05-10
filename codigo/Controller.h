// ****************************************************************************************************
// ******************************************* CONTROLLER_H__ *****************************************
// ****************************************************************************************************

#ifndef PROJ1_CONTROLLER_H
#define PROJ1_CONTROLLER_H


#include "Truck.h"
#include "Order.h"
#include <vector>
#include <string>
#include <set>
class Controller{
private:
    vector<Order> orderDB;
    vector<Truck> truckDB;

public:
    // Constructors
    /** @brief  Default constructor.*/
    Controller();
    /** @brief  Default destructor.*/
    ~Controller();

    // Gets


    /**
    * @brief Gets the truckDB of the Controller object.
    * @return the truckDB attribute.
    */
    vector<Truck>& getTrucks();

    /**
    * @brief Gets the orderDB of the Controller object.
    * @return the orderDB attribute.
    */
    vector<Order> getOrders();

    //Reads
    /**
    * @brief Reads orders1
     * */
    bool readOrders(int orderNo);

    /**
    * @brief Reads trucks
    * */
    void readTrucks();


    // Adds
    /** @brief  Adds a new Stop created with \p name, code, zone, latitude and longitude.*/
    void addTruck(int id, int volMax, int weightMax, int cost);

    void addOrder(int id, int vol, int weight, int reward, int duration);

    //Sceneries

    /** @brief  Processes scenery 1 and returns the trucks used.*/
    vector<Truck> scenery1();

    /** @brief  Processes scenery 2 and returns the trucks used,
     * also returns the profit through the parameter getProfit.*/
    vector<Truck> scenery2(int& getProfit);

    /** @brief  Processes scenery 3 and returns the orders to be shipped ordered,
     * also returns the average delivery time through the parameter getMeanTime*/
    vector <Order> scenery3(int& getMeanTime);


    /**
     * This function is responsible for calculate the maximum profit in a single truck, it use Buttom-Up approach
     * and Dynamic Programing
     * @param truck
     * @return the total profit in this operation
     */
    int processTruck(Truck &truck);

    /**
     * Loads the information obtained in the table in the database, filling the trucks with orders.
     * @param dp The table that contains all operations
     * @param truck the truck used for generate the table
     */
    void processSelectedOrders(vector<vector<vector<int>>> &dp, Truck &truck);

    void sortTruckDBforS2();

    static bool compareCostBenefit(const Truck &t1, const Truck &t2);

    void clearOrders();

    void clearTrucks();

    void SetOrderByWeight(vector<Order> &orderdb);

    void SetOrderByVolume(vector<Order> &orderdbyVol);

    void SetTruckRankingWeight(vector<Truck> &truckdb);

    void SetTruckRankingVol(vector<Truck> &truckdb);

    void SetTruckRankingCost(vector<Truck> &truckdb);
};

#endif //PROJ1_CONTROLLER_H
