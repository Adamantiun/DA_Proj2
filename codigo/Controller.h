// ****************************************************************************************************
// ******************************************* CONTROLLER_H__ *****************************************
// ****************************************************************************************************

#ifndef PROJ1_CONTROLLER_H
#define PROJ1_CONTROLLER_H


#include "Graph.h"
#include "StopEdge.h"
#include "Line.h"
#include <vector>
#include <string>
#include <set>
class Controller{
private:
    vector<Stop> stopDB;
    vector<Line> linesDB;
    Graph graph;
    vector<int> latestIndexGroupSize;
    vector<Edge> usedEdges;
public:

    // Constructors
    /** @brief  Default constructor.*/
    Controller();
    /** @brief  Default destructor.*/
    ~Controller();

    // Gets
    /**
    * @brief Gets the item i of latestIndexGroupSize.
    */
    int getSizeAtIndex(int i);
    /**
    * @brief Gets the graph of the Controller object.
    * @return the graph attribute.
    */
    Graph getGraph();
    /**
    * @brief Gets the stopDB of the Controller object.
    * @return the stopDB attribute.
    */
    vector<Stop>& getStops();

    /**
    * @brief Gets the lineDB of the Controller object.
    * @return the orderDB attribute.
    */
    vector<Line> getLines();

    //Reads
    /**
    * @brief Reads input'n'_b
     * */
    bool readInput(int inNo);

    // Adds

    //Sceneries

    /**
    * @brief Runs dijkstra for capacity and returns a user friendly message
     * */
    string getPrintableDijkCapacity(int ori, int dest, int groupSize);
    /**
    * @brief Finds best paths and returns a user friendly message
     * */
    vector<string> getEquiEfficientOpts(int ori, int dest, float& retMaxCaptaPerConnect);
    /**
    * @brief Runs ford-fulkerson/edmonds-karp
     * @returns user friendly message
     * */
    string getPrintableMaxFlow(int ori, int dest);
    /**
    * @brief Recursive function that assists in creating user friendly print for flow
     * */
    string recursivePrintableFlow(int ori, int dest, int n=0);
    /**
    * @brief Runs ford-fulkerson/edmonds-karp with a limit
     * @returns user friendly message
     * */
    string getPrintableLimFlow(int ori, int dest, int groupSize);
    /**
    * @brief Adds to the limit of ford-fulkerson/edmonds-karp
     * @returns user friendly message
     * */
    string getPrintableLimFlow(int ori, int dest, int groupSize, int addToGroup);
};

#endif //PROJ1_CONTROLLER_H
