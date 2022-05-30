//
// Created by igcbs on 16/01/2022.
//

#include "StopEdge.h"
#include <iostream>

Stop::Stop() {
    this->code = "";
    this->name = "";
    this->zone = "";
    this->latitude = 0;
    this->longitude = 0;
    this->predMax = 0;
    this->capacity = 0;

}

Stop::Stop(int index) {
    this->index=index;
    this->code = "";
    this->name = "";
    this->zone = "";
    this->latitude = 0;
    this->longitude = 0;
    this->predMax = 0;
    this->capacity = 0;


}
Stop::Stop(const string &code, const string &name, const string &zone, float latitude, float longitude) {
    this->code = code;
    this->name = name;
    this->zone = zone;
    this->latitude = latitude;
    this->longitude =longitude;
    this->predMax = 0;
    this->capacity = 0;

}

Stop::~Stop(){
    code.clear();
    name.clear();
    zone.clear();
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

const string &Stop::getZone() const {
    return zone;
}

float Stop::getLatitude() const {
    return latitude;
}

int Stop::getPred() const {
    return pred;
}

float Stop::getLongitude() const {
    return longitude;
}

void Stop::setCode(const string &code) {
    Stop::code = code;
}

void Stop::setName(const string &name) {
    Stop::name = name;
}

void Stop::setZone(const string &zone) {
    Stop::zone = zone;
}

void Stop::setLatitude(float latitude) {
    Stop::latitude = latitude;
}

void Stop::setLongitude(float longitude) {
    Stop::longitude = longitude;
}

void Stop::setCapacity(int capacity) {
    Stop::capacity=capacity;
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
    is.getline(temp, 100, ',');
    stop.setZone((string)temp);
    is.getline(temp, 100, ',');
    stop.setLatitude(stof(temp));
    is.getline(temp, 100);
    stop.setLongitude(stof(temp));
    return is;
}

Stop::Stop(int latitude, int longitude) {
    this->latitude = latitude;
    this->longitude =longitude;
}

void Stop::addEdge(Edge& edge) {
    adj.push_back(edge);
}

void Stop::addEdge(int origin, int dest, int capacity, int duration){
    adj.push_back(Edge(origin, dest, capacity, duration));
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

list<Edge> Stop::getAdj() {
    return adj;
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

void Edge::setDuration(int durantion) {
    this->duration=durantion;
}

void Edge::setOrigin(int origin) {
    this->origin=origin;
}

void Edge::setDest(int  dest) {
    this->dest = dest;
}

