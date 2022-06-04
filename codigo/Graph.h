// ****************************************************************************************************
// *********************************************** GRAPH_H__ *****************************************
// ****************************************************************************************************

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "StopEdge.h"
#include "maxHeap.h"


using namespace std;

class Graph {
    int n;
    bool hasDir;
    vector<Stop> stops;

public:
    // Constructors
    /**
     * @brief  Default constructor.
     *
     */
    Graph();
    /**
    * @brief Received the necessary attributes to create a Graph object.
    * @param nodes
    * @param dir in default is false
    */
    Graph(int nodes, bool dir = false);

    // Gets
    /** @brief  Get Stop wich is the destination of an edge.*/
    Stop& getDest(Edge edge);

    /** @brief  Get path between 2 Stops.*/
    vector<int> getPath(Stop& a, Stop& b);

    /** @brief  Get Stop with some index.*/
    Stop& getStop(int index);

    /** @brief  Get Stop with some code.*/
    Stop& getStop(string code);

    /** @brief  Get all the Stops.*/
    vector<Stop>& getStops();

    /** @brief  Get index of a Stop with some code.*/
    int getIndexStop(string code);

    Edge getEdge(Stop a, Stop b);

    //Adds
    /** @brief  Add a Stop.*/
    void addStop(Stop& stop);

    /** @brief  Add an Edge.*/
    void addEdge(int origin, int dest, int capacity, int duration);

    //Algorithms

    /** @brief  Dijkstra algorithm that returns the path the least distance.*/
    vector<int> dijkstraCapacity (Stop& a, Stop& b, int groupSize);

    /** @brief  Bfs algorithm that returns existance of path.*/
    int bfs(Stop& origin, Stop& dest);

    //Resents
    /** @brief  Reset every Stop.*/
    void resetNodes();

    int pathMaxCapacity(Stop& a, Stop& b);


    bool has(int x);

    int pathMaxCapacity(int a, int b);

    int getPathTime(vector<int> path);

    int fordFulk(Stop &ori, Stop &dest);

    void clearEdges();

    void clearStopCaps();

    int fordFulkLim(Stop &ori, Stop &dest, int lim);
};

#endif
