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

    Graph getGraph();
    // Constructors
    /** @brief  Default constructor.*/
    Controller();
    /** @brief  Default destructor.*/
    ~Controller();

    // Gets


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
    * @brief Reads orders1
     * */
    bool readInput(int inNo);

    // Adds

    //Sceneries

    string getPrintableDikjCapacity(int ori, int dest, int groupSize);

    vector<string> getEquiEfficientOpts(int ori, int dest, float& retMaxCaptaPerConnect);

    int getSizeAtIndex(int i);

    string getPrintableMaxFlow(int ori, int dest);

    string recursivePrintableFlow(int ori, int dest, int n=0);

    string getPrintableLimFlow(int ori, int dest, int groupSize);

    string getPrintableLimFlow(int ori, int dest, int groupSize, int addToGroup);
};

#endif //PROJ1_CONTROLLER_H
