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

string Controller::getPrintableDijkCapacity(int ori, int dest, int groupSize) {
    string ret = "Here's your route:\n";
    vector<int> path = graph.dijkstraCapacity(graph.getStop(ori), graph.getStop(dest), groupSize);
    int i = 1;
    while (i < path.size()) {
        ret += "From " + to_string(path[i - 1]) + " to " + to_string(path[i]) + ", taking " +
               to_string(graph.getEdge(graph.getStop(path[i-1]), graph.getStop(path[i])).getDuration()) + "hours\n";
        i++;
    }
    ret.resize(ret.size()-1);
    return ret;
}

vector<string> Controller::getEquiEfficientOpts(int ori, int dest, float& retMaxCaptaPerConnect) {
    vector<string> ret;

    float maxCaptaPerConnect = 0;
    int n = 0;
    latestIndexGroupSize.clear();

    for(int i=1; i<=graph.pathMaxCapacity(ori, dest); i++){
        vector<int> path = graph.dijkstraCapacity(graph.getStop(ori), graph.getStop(dest), i);
        if(ceil((100.0*i)/((path.size()-1)))/100.0 > maxCaptaPerConnect){
            maxCaptaPerConnect = ceil((100.0*i)/((path.size()-1)))/100.0;
            latestIndexGroupSize.clear();
            n = 0;
            ret.clear();
            latestIndexGroupSize.push_back(i);
            ret.push_back("Taking " + to_string(i) + " people, you will ride " + to_string(path.size()-1)
                    +" buses, and take "+ to_string(graph.getPathTime(path)) + "hours");
            n++;
        }else if(ceil((100.0*i)/((path.size()-1)))/100.0 == maxCaptaPerConnect){
            latestIndexGroupSize.push_back(i);
            ret.push_back("Taking " + to_string(i) + " people, you will ride " + to_string(path.size()-1)
                          +" buses, and take "+ to_string(graph.getPathTime(path)) + "hours");
            n++;
        }
    }

    retMaxCaptaPerConnect = maxCaptaPerConnect;

    return ret;
}

int Controller::getSizeAtIndex(int i) {
    return latestIndexGroupSize[i];
}

string Controller::recursivePrintableFlow(int ori, int dest, int n){
    if(ori == dest)
        return "";
    string ret;
    Stop s = graph.getStop(ori);
    for(auto e : *s.getAdj()){
        if(e.getSaturation()!=0 && !(count(usedEdges.begin(), usedEdges.end(), e))){
            ret+= string(n, '.') + to_string(e.getSaturation()) + " people go from " + to_string(ori) + " to "
                    + to_string(e.getDest()) + " taking " + to_string(e.getDuration()) + "hours\n";
            if(graph.getStop(e.getDest()).getLatestEntranceTime() > graph.getStop(e.getDest()).getEntranceTime(s.getIndex())){
                ret.pop_back();
                int wait = graph.getStop(e.getDest()).getLatestEntranceTime() - graph.getStop(e.getDest()).getEntranceTime(s.getIndex());
                ret += " and wait there " + to_string(wait) + "hours\n";
            }
            ret+= recursivePrintableFlow(e.getDest(), dest, n + 1);
            usedEdges.push_back(e);
        }
    }
    return ret;
}

string Controller::getPrintableMaxFlow(int ori, int dest) {
    int maxFlow = graph.fordFulk(graph.getStop(ori), graph.getStop(dest));
    string ret = "You can take up to " + to_string(maxFlow) + " people from " + to_string(ori)
            + " to " + to_string(dest) + "!\nAnd here's the path:\n";
    usedEdges = {};
    ret += recursivePrintableFlow(ori, dest);
    ret+= "\nAnd the group will be fully together at:";
    for(auto s:graph.getStops())
        if(s.getCapacity() == maxFlow)
            ret+= "\nStop " + to_string(s.getIndex()) + " at hour " + to_string(s.getLatestEntranceTime());
    return ret;
}

string Controller::getPrintableLimFlow(int ori, int dest, int groupSize) {
    graph.clearEdges();
    graph.clearStopCaps();
    int flow = graph.fordFulkLim(graph.getStop(ori), graph.getStop(dest), groupSize);
    if (flow == 0)
        return "You can't take that many people though that path";
    string ret = "Here's the path taking " + to_string(groupSize) + " people from "
            + to_string(ori) + " to " + to_string(dest) + ":\n";
    usedEdges = {};
    ret+= recursivePrintableFlow(ori, dest);
    ret+= "\nAnd the group will be fully together at:";
    for(auto s:graph.getStops())
        if(s.getCapacity() == groupSize)
            ret+= "\nStop " + to_string(s.getIndex()) + " at hour " + to_string(s.getLatestEntranceTime());
    return ret;
}

string Controller::getPrintableLimFlow(int ori, int dest, int groupSize, int addToGroup) {
    int flow = graph.fordFulkLim(graph.getStop(ori), graph.getStop(dest), addToGroup);
    if (flow == 0)
        return "You can't take that many people though that path";
    string ret = "Here's the path taking " + to_string(groupSize+addToGroup) + " people from "
                 + to_string(ori) + " to " + to_string(dest) + ":\n";
    usedEdges = {};
    ret+= recursivePrintableFlow(ori, dest);
    ret+= "\nAnd the group will be fully together at:";
    for(auto s:graph.getStops())
        if(s.getCapacity() == groupSize+addToGroup)
            ret+= "\n -Stop " + to_string(s.getIndex()) + " at hour " + to_string(s.getLatestEntranceTime());
    return ret;
}





