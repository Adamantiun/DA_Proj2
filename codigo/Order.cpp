//
// Created by 35196 on 26/03/2022.
//

#include "Order.h"

Order::Order(){
    this->id=0;
    this->weight=0;
    this->duration=0;
    this->reward=0;
    this->vol=0;
}

Order::~Order(){
}

Order::Order(const int &id, const int &vol, const int &weight, const int &reward, const int &duration){
    this->id=id;
    this->weight=vol;
    this->duration=weight;
    this->reward=reward;
    this->vol=duration;
}

const int &Order::getId() const {
    return id;
}

const int &Order::getWeight() const {
    return weight;
}

const int &Order::getDuration() const {
    return duration;
}

const int &Order::getReward() const {
    return reward;
}

const int &Order::getVol() const {
    return vol;
}

void Order::setId(const int &id) {
    this->id=id;
}

void Order::setWeight(const int &weight) {
    this->weight=weight;
}

void Order::setDuration(const int &duration) {
    this->duration=duration;
}

void Order::setReward(const int &reward) {
    this->reward=reward;
}

void Order::setVol(const int &vol) {
    this->vol=vol;
}
bool Order::operator<(const Order &o) const {
    if(o.duration< this->duration) return false;
    return true;
}

int Order::getRankingVol() const {
    return rankingVol;
}

void Order::setRankingVol(int rankingVol) {
    Order::rankingVol = rankingVol;
}

int Order::getRankingWei() const {
    return rankingWei;
}

void Order::setRankingWei(int rankingWei) {
    Order::rankingWei = rankingWei;
}

bool Order::operator==(const Order &o) const {
    if(o.id==this->id) return true;
     return false;
}
