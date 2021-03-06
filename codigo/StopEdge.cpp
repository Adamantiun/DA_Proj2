//
// Created by igcbs on 16/01/2022.
//

#include "StopEdge.h"
#include <iostream>

Stop::Stop() {
    this->code = "";
    this->name = "";
    this->predMax = 0;
    this->capacity = 0;

}

Stop::Stop(int index) {
    this->index=index;
    this->code = "";
    this->name = "";
    this->predMax = 0;
    this->capacity = 0;


}
Stop::Stop(const string &code, const int index) {
    this->code = code;
    this->index = index;
    this->predMax = 0;
    this->capacity = 0;

}

Stop::~Stop(){
    code.clear();
    name.clear();
}

vector<pair<int,int>> Stop::getEntrances(){
    return entrances;
}

const string &Stop::getCode() const {
    return code;
}

const int &Stop::getCapacity() const {
    return capacity;
}

const string &Stop::getName() const {
    return name;
}

int Stop::getPred() const {
    return pred;
}

void Stop::setCode(const string &code) {
    Stop::code = code;
}

void Stop::setName(const string &name) {
    Stop::name = name;
}

void Stop::setCapacity(int capacity) {
    Stop::capacity=capacity;
}

void Stop::setEntrances(vector<pair<int,int>> entrances){
    this->entrances = entrances;
}

int Stop::getLatestEntranceTime(){
    int ret = 0;
    for(auto e : entrances)
        ret = max(e.second, ret);
    return ret;
}

int Stop::getEntranceTime(int index){
    for(auto e : entrances)
        if(e.first == index)
            return e.second;
    return 0;
}

void Stop::addEntrance(pair<int, int> entrance){
    for(auto & e : entrances)
        if(e.first == entrance.first){
            if(e.second >= entrance.second)
                return;
            else {
                e = entrance;
                return;
            }
        }
    entrances.push_back(entrance);
}

istream & operator>>(istream &is, Stop &stop) {
    char temp[256];
    if(!is.getline(temp, 100, ',')){
        is.ignore();
        return is;
    }
    stop.setCode((string)temp);
    is.getline(temp, 100, ',');
    stop.setName((string)temp);
    return is;
}

void Stop::addEdge(Edge& edge) {
    adj.push_back(edge);
}
void Stop::addEdgeA(Edge edge) {
    edge.setOrigin(index);
    adj.push_back(edge);
}
void Stop::addEdge(int origin, int dest, int capacity, int duration){
    adj.push_back(Edge(origin, dest, capacity, duration));
}

void Stop::addEdge(int dest, int capacity, int duration){
    adj.push_back(Edge(index, dest, capacity, duration));
}

void Stop::setDistance(double distance) {
    this->distance=distance;
}

void Stop::setVisited(bool visited) {
    this->visited=visited;
}

void Stop::setPred(int pred){
    this->pred=pred;
}

double Stop::getDistance() const {
    return distance;
}

bool Stop::getVisited() const {
    return visited;
}

vector<Edge> * Stop::getAdj() {
    return &adj;
}

Edge& Stop::getEdge(int index) {
    for(int i=0; i<adj.size(); i++)
        if(adj[i].getDest() == index)
            return adj[i];
}

void Stop::setIndex(int index) {
    Stop::index = index;
}

int Stop::getIndex() const {
    return index;
}

void Stop::setPredMax(int max) {
    predMax = max;
}

int Stop::getPredMax() const{
    return predMax;
}

bool Stop::isInAdj(Stop &stop) {
    for(auto& e :adj){
        if(e.getDest()==stop.getIndex()) return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------

Edge::Edge() {
    this->origin=0;
    this->dest=0;
    this->capacity=0;
    this->duration=0;
}
Edge::Edge(int origin, int dest, int capacity, int duration) {
    this->origin=origin;
    this->dest=dest;
    this->capacity=capacity;
    this->duration=duration;
}

int Edge::getDest() {
    return dest;
}

int Edge::getDuration() {
    return duration;
}

int Edge::getOrigin() {
    return origin;
}

int Edge::getCapacity() {
    return capacity;
}

void Edge::setCapacity(int capacity) {
    this->capacity=capacity;
}

void Edge::setDuration(int duration) {
    this->duration=duration;
}

void Edge::setOrigin(int origin) {
    this->origin=origin;
}

void Edge::setDest(int  dest) {
    this->dest = dest;
}

int Edge::getSaturation() {
    return saturation;
}

void Edge::setSaturation(int saturation) {
    this->saturation = saturation;
}

