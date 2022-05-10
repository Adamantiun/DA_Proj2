//
// Created by 35196 on 26/03/2022.
//

#include "Truck.h"

Truck::Truck() {
    this->id=0;
    this->cost=0;
    this->volMax=0;
    this->weightMax=0;
}

Truck::Truck(const int &id, const int &volMax, const int &weightMax, const int &cost) {
    this->id=id;
    this->cost=cost;
    this->volMax=volMax;
    this->weightMax=weightMax;
}

Truck::~Truck() {}

const int &Truck::getId() const {
    return id;
}

const int &Truck::getCost() const {
    return cost;
}

const int &Truck::getVolMax() const {
    return volMax;
}

const int &Truck::getWeightMax() const {
    return weightMax;
}

void Truck::setId(const int &id) {
    this->id=id;
}

void Truck::setCost(const int &cost) {
    this->cost=cost;
}

void Truck::setVolMax(const int &volMax) {
    this->volMax=volMax;
}

void Truck::setWeightMax(const int &weightMax) {
    this->weightMax=weightMax;
}

int Truck::getRankingWei() const {
    return RankingWei;
}

void Truck::setRankingWei(int rankingWei) {
    RankingWei = rankingWei;
}

int Truck::getRankingVol() const {
    return RankingVol;
}

void Truck::setRankingVol(int rankingVol) {
    RankingVol = rankingVol;
}

void Truck::addOrder(Order &order) {
    ordersInside.push_back(order);
}

const vector<Order> &Truck::getOrdersInside() const {
    return ordersInside;
}

void Truck::setOrdersInside(const vector<Order> &ordersInside) {
    Truck::ordersInside = ordersInside;
}

void Truck::add(Order &order) {
 orderss.insert(order);
}

bool Truck::operator<(const Truck &o) {
    if(o.getId()< this->getId()) return false;
    return true;
}

bool Truck::operator==(const Truck &o) {
    if(o.getId() == this->getId()) return true;
        return false;}

void Truck::emptyTruck() {
    orderss.clear();
}

int Truck::getRankingCost() const {
    return RankingCost;
}

void Truck::setRankingCost(int rankingCost) {
    RankingCost = rankingCost;
}



