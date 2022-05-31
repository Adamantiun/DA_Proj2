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
}

bool Controller::readInput(int inNo) {
    ifstream inputFile;
    if(inNo>=10)
        inputFile.open("../input/in" + to_string(inNo) + "_b.txt" );
    else
        inputFile.open("../input/in0" + to_string(inNo) + "_b.txt" );
    if (inputFile.fail()) {
        return false;
    }
    string nStops;
    string nEdges;
    getline(inputFile,nStops, ' ');
    this->graph= Graph(stoi(nStops) );
    for(int i=1; i<= stoi(nStops);i++){
        Stop aux = Stop(i);
        graph.addStop(aux);
    }
    getline(inputFile,nEdges);
    string line;
    while (!inputFile.eof() && inputFile.peek()!='\n') {
        Edge edge = Edge();
        getline(inputFile,line, ' ');
        edge.setOrigin(stoi(line));
        getline(inputFile,line, ' ');
        edge.setDest(stoi(line));
        getline(inputFile,line, ' ');
        edge.setCapacity(stoi(line));
        getline(inputFile,line);
        edge.setDuration(stoi(line));
        graph.getStop(edge.getOrigin()).addEdge(edge);

    }
    inputFile.close();
    return true;
}


Controller::~Controller(){
    linesDB.clear();
    stopDB.clear();
}

vector<Line> Controller::getLines() {
    return linesDB;
}

vector<Stop>& Controller::getStops() {
    return stopDB;
}

Graph Controller::getGraph() {
    return graph;
}

string Controller::getPrintableDikjCapacity(int ori, int dest, int groupSize) {
    string ret = "Here's your route:\n";
    vector<int> path = graph.dijkstraCapacity(graph.getStop(ori), graph.getStop(dest), groupSize);
    int i = 1;
    while (i < path.size()) {
        ret += "From " + to_string(path[i - 1]) + " to " + to_string(path[i]) + ", taking " +
               to_string(graph.getEdge(graph.getStop(path[i-1]), graph.getStop(path[i])).getDuration()) + "min\n";
        i++;
    }
    ret.resize(ret.size()-1);
    return ret;
}





