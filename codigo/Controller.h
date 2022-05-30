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

};

#endif //PROJ1_CONTROLLER_H
