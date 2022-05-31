//
// Created by 35196 on 24/01/2022.
//


#include "Graph.h"
#include "minHeap.h"
#include <algorithm>

Graph::Graph() {
    this->n=0;
    stops={};
}

Graph::Graph(int num, bool dir) : n(num), hasDir(dir){}

void Graph::addStop(Stop &stop) {
    this->stops.push_back(stop);
}


int Graph::pathMaxCapacity(int a, int b){
    return pathMaxCapacity(getStop(a), getStop(b));
}

int Graph::pathMaxCapacity(Stop& a, Stop& b){
    for(int i = 0; i < stops.size(); i++) {
        stops[i].setCapacity(0);
        stops[i].setVisited(false);
        stops[i].setPred(i);
    }
    getStop(a.getIndex()).setCapacity(1000);
    struct PriorityQueue s;
    for(int i = 0; i < stops.size(); i++) {
        s.push(stops[i].getIndex(),stops[i].getCapacity());
    }
    while (s.size()>0){
        int u = s.top();
        s.pop();
        getStop(u).setVisited(true);
        for (Edge& edge : getStop(u).getAdj()){
            if (min(getStop(u).getCapacity(),edge.getCapacity()) > getStop(edge.getDest()).getCapacity() ){
                getStop(edge.getDest()).setCapacity(min(getStop(u).getCapacity(),edge.getCapacity()));
                getStop(edge.getDest()).setPred(u);
                s.clean();
                for(int i = 0; i < stops.size() ; i++) {
                    if(!stops[i].getVisited()) {
                        s.push(stops[i].getIndex(), stops[i].getCapacity());
                    }
                }

            }
        }
    }
    return getStop(b.getIndex()).getCapacity();
}

vector<int> Graph::dijkstraCapacity(Stop& a, Stop& b, int groupSize) {
    if (a.getIndex()==b.getIndex()) return {};
    resetNodes();
    getStop(a.getIndex()).setDistance(0);
    MinHeap<int,double> q(n,NULL);
    for (int i = 0; i<=n;i++){
        q.insert(stops[i].getIndex(),stops[i].getDistance());
    }
    while (q.getSize()!=0){
        int u = q.removeMin();
        getStop(u).setVisited(true);
        for (Edge& edge : getStop(u).getAdj()){
            if(edge.getCapacity()<groupSize) continue;
            double tempDist = getStop(u).getDistance() + 1;
            if ((tempDist < getStop(edge.getDest()).getDistance()) && q.hasKey(edge.getDest())){
                getStop(getStop(edge.getDest()).getIndex()).setDistance(tempDist);
                getStop(getStop(edge.getDest()).getIndex()).setPred(u);
                getStop(getStop(edge.getDest()).getIndex()).setPredMax(edge.getCapacity());
                q.decreaseKey(getStop(edge.getDest()).getIndex(),tempDist);
            }
        }
    }
    return getPath(a, b);
}


vector<int> Graph::getPath(Stop& a, Stop& b){
    vector<int> res;
    int p = getStop(b.getIndex()).getIndex();
    res.push_back(p);
    int i = getStop(b.getIndex()).getPred();
    p = i;
    while (i!=a.getIndex()){
        res.insert(res.begin(),p);
        i = getStop(i).getPred();
        p = i;
    }
    p = a.getIndex();
    res.insert(res.begin(), p);
    if (b.getDistance()==INT_MAX) return {};
    return res;
}

void Graph::resetNodes(){
    for(int i = 0; i < n; i++) {
        stops[i].setDistance(1000);
        stops[i].setVisited(false);
        stops[i].setPred(stops[i].getIndex());
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

void Graph::addEdge(int origin, int dest, int capacity, int duration){
    stops.at(origin).addEdge(origin, dest, capacity, duration);
}

bool Graph::has(int x) {
    for(auto s : stops)
        if(s.getIndex() == x)
            return true;
    return false;
}

Edge Graph::getEdge(Stop a, Stop b) {
    for(auto e : getStop(a.getIndex()).getAdj()){
        if(e.getDest() == b.getIndex())
            return e;
    }
    return Edge(0, 0, 0, 0);
}
/*
vector<pair<int, std::string>> Graph::bfs(Stop& origin, Stop& dest, int max) {
    resetNodes();
    queue<Stop> q; // queue of unvisited nodes
    q.push(origin);
    origin.setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        Stop u = q.front();
        q.pop();
        for (auto e : u.getAdj()) {
            int w = e.getDest();
            if (!stops[w].getVisited() ) {
                q.push(stops[w]);
                stops[w].setVisited(true);
                stops[w].setPred(u.getIndex());
                stops[w].setPredLine(e.getLineCode());
            }
        }
    }
    return getPath(origin, dest);
}

*/
