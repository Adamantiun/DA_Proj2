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
    vector<pair<int, std::string>> getPath(Stop& a, Stop& b);

    /** @brief  Get Stop with some index.*/
    Stop& getStop(int index);

    /** @brief  Get Stop with some code.*/
    Stop& getStop(string code);

    /** @brief  Get all the Stops.*/
    vector<Stop>& getStops();

    /** @brief  Get index of a Stop with some code.*/
    int getIndexStop(string code);

    //Adds
    /** @brief  Add a Stop.*/
    void addStop(Stop& stop);

    /** @brief  Add an Edge.*/
    void addEdge(int src, int dest, double weight, string code);

    //Algorithms

    /** @brief  Dijkstra algorithm that returns the path the least distance.*/
    vector<pair<int, std::string>> dijkstra_distance (Stop& a, Stop& b);

    /** @brief  Dijkstra algorithm that returns the path the least number of zones.*/
    vector<pair<int, string>> dijkstra_zones(int a, int b);

    /** @brief  Bfs algorithm that returns the path the least number of Stops.*/
    vector<pair<int, std::string>> bfs(Stop& origin, Stop& dest);

    //Resents
    /** @brief  Reset every Stop.*/
    void resetNodes();







};

#endif
