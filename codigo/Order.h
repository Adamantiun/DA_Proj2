//
// Created by 35196 on 26/03/2022.
//

#ifndef TRABALHODA1_ORDER_H
#define TRABALHODA1_ORDER_H

using namespace std;

class Order {
private:
    int id;
    int vol;
    int weight;
    int reward;
    int duration;
    int rankingVol;
    int rankingWei;
public:
    int getRankingVol() const;

    void setRankingVol(int rankingVol);

    int getRankingWei() const;

    void setRankingWei(int rankingWei);

public:
    //Constructors
    /** @brief  Default constructor.*/
    Order();

    /** @brief Received the necessary attributes to create a Order object.*/
    Order(const int &id, const int &vol, const int &weight, const int &reward, const int &duration);

    //Deconstructors
    /** @brief  Default destructor.*/
    ~Order();

    //Gets
    /** @brief  Get id attribute.*/
    const int &getId() const;

    /** @brief  Get volume attribute.*/
    const int &getVol() const;

    /** @brief  Get weight attribute.*/
    const int &getWeight() const;

    /** @brief  Get reward attribute.*/
    const int &getReward() const;

    /** @brief  Get duration attribute.*/
    const int &getDuration() const;


    //Sets
    /** @brief  Set id attribute.*/
    void setId (const int &id);

    /** @brief  Set volume attribute.*/
    void setVol(const int &vol);

    /** @brief  Set name attribute.*/
    void setWeight(const int &weight);

    /** @brief  Set code attribute.*/
    void setReward(const int &reward);

    /** @brief  Set code attribute.*/
    void setDuration(const int &duration);

    bool operator<(const Order& o) const;
    bool operator==(const Order& o) const;

};
#endif //TRABALHODA1_ORDER_H
