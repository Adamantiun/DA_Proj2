//
// Created by 35196 on 24/01/2022.
//


#include "Graph.h"
#include "minHeap.h"

Graph::Graph() {
    this->n=0;
    stops={};
}

Graph::Graph(int num, bool dir) : n(num), hasDir(dir){}

void Graph::addStop(Stop &stop) {
    this->stops.push_back(stop);
}

vector<pair<int, std::string>> Graph::dijkstra_distance(Stop& a, Stop& b) {
    if (a==b) return {};
    resetNodes();
    a.setDistance(0);
    MinHeap<int,double> q(n,NULL);
    for (int i = 0; i<=n;i++){
        q.insert(i,stops[i].getDistance());
    }
    while (q.getSize()!=0){
        int u = q.removeMin();
        stops[u].setVisited(true);
        for (Edge& edge : stops[u].getAdj()){
            double tempDist = stops[u].getDistance() + edge.getWeight();
            if ((tempDist < getDest(edge).getDistance()) && q.hasKey(edge.getDest())){
                stops[getDest(edge).getIndex()].setDistance(tempDist);
                stops[getDest(edge).getIndex()].setPred(u);
                stops[getDest(edge).getIndex()].setPredLine(edge.getLineCode());
                q.decreaseKey(getDest(edge).getIndex(),tempDist);
            }
        }
    }
    return getPath(a, b);
}

vector<pair<int, string>> Graph::dijkstra_zones(int a, int b) {
    if (a==b) return {};
    resetNodes();
    stops[a].setDistance(0);
    MinHeap<int,double> q(n,0);
    for (int i = 0; i<n;i++){
        q.insert(i,stops[i].getDistance());
    }
    while (q.getSize()!=0){
        int u = q.removeMin();
        stops[u].setVisited(true);
        for (Edge& edge : stops[u].getAdj()){
            int v = edge.getDest();
            int tempDist = stops[u].getDistance();
            if(stops[u].getZone() != stops[v].getZone())
                tempDist++;
            if ((tempDist < getDest(edge).getDistance()) && q.hasKey(edge.getDest())){
                stops[getDest(edge).getIndex()].setDistance(tempDist);
                stops[getDest(edge).getIndex()].setPred(u);
                q.decreaseKey(getDest(edge).getIndex(),tempDist);
            }
        }
    }
    return getPath(stops[a], stops[b]);
}

vector<pair<int, string>> Graph::getPath(Stop& a, Stop& b){
    vector<pair<int, string>> res;
    pair<int, string> p = {b.getIndex(), b.getPredLine()};
    res.push_back(p);
    int i = b.getPred();
    p = {i, getStop(i).getPredLine()};
    while (i!=a.getIndex()){
        res.insert(res.begin(),p);
        i = getStop(i).getPred();
        p = {i, getStop(i).getPredLine()};
    }
    p = {a.getIndex(), a.getPredLine()};
    res.insert(res.begin(), p);
    if (b.getDistance()==INT_MAX) return {};
    return res;
}

void Graph::resetNodes(){
    for(int i = 0; i < n; i++) {
        stops[i].setDistance(1000);
        stops[i].setVisited(false);
        stops[i].setPred(i);
    }
}

Stop& Graph::getDest(Edge edge){
    return(stops.at(edge.getDest()));

}

int Graph::getIndexStop(string code) {
    for(int i=0;i<n;i++){
        if(stops[i].getCode()==code){
            return i;
        }
    }
    return -1;
}

Stop &Graph::getStop(int index) {
    for(int i=0;i<n;i++){
        if(stops.at(i).getIndex() == index)
            return stops.at(i);
    }
}
Stop& Graph::getStop(string code){
    for(int i=0;i<n;i++){
        if(stops.at(i).getCode() == code)
            return stops.at(i);
    }
    return stops.at(0);
}

vector<Stop>& Graph::getStops(){
    return stops;
}

void Graph::addEdge(int src, int dest, double weight = 1.0, string code=0){
    stops.at(src).addEdge(dest, weight, code);
}

vector<pair<int, std::string>> Graph::bfs(Stop& origin, Stop& dest) {
    resetNodes();
    queue<Stop> q; // queue of unvisited nodes
    q.push(origin);
    origin.setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        Stop u = q.front();
        q.pop();
        for (auto e : u.getAdj()) {
            int w = e.getDest();
            if (!stops[w].getVisited()) {
                q.push(stops[w]);
                stops[w].setVisited(true);
                stops[w].setPred(u.getIndex());
                stops[w].setPredLine(e.getLineCode());
            }
        }
    }
    return getPath(origin, dest);
}


