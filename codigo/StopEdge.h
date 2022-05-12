// ****************************************************************************************************
// ******************************************* STOPEDGE_H__ *******************************************
// ****************************************************************************************************

#ifndef STOPEDGE_H
#define STOPEDGE_H

#include <string>
#include <list>

using namespace std;

class Edge;

class Stop {
private:
    int index;
    string code;
    string name;
    string zone;
    float latitude;
    float longitude;
    list<Edge> adj;
    double distance;
    bool visited;
    int pred;
    string predLine;

public:
    // Constructors
    /**
     * @brief  Default constructor.
     *
     */
    Stop();

    /**
    * @brief Received the necessary attributes to create a Stop object.
    * @param code
    * @param name
    * @param zone
    * @param latitude
    * @param longitude
    */
    Stop(const string &code, const string &name, const string &zone, float latitude, float longitude);

    /**
    * @brief Received the necessary attributes to create a Stop object.
    * @param x
    * @param y
    */
    Stop(int x, int y);

    //Deconstructors
    /** @brief  Default destructor.*/
    ~Stop();

    //Gets
    /** @brief  Get code attribute.*/
    const string &getCode() const;

    /** @brief  Get name attribute.*/
    const string &getName() const;

    /** @brief  Get zone attribute.*/
    const string &getZone() const;

    /** @brief  Get latitude attribute.*/
    float getLatitude() const;

    /** @brief  Get longitude attribute.*/
    float getLongitude() const;

    /** @brief  Get pred attribute.*/
    int getPred( ) const;

    /** @brief  Get distance attribute.*/
    double getDistance()const;

    /** @brief  Get visited attribute.*/
    bool getVisited() const;

    /** @brief  Get adj attribute.*/
    list<Edge> getAdj();

    /** @brief  Get predLine attribute.*/
    string getPredLine() const;

    /** @brief  Get index attribute.*/
    int getIndex() const;

    //Sets
    /** @brief  Set index attribute.*/
    void setIndex(int index);

    /** @brief  Set code attribute.*/
    void setCode(const string &code);

    /** @brief  Set distance attribute.*/
    void setDistance(double distance);

    /** @brief  Set visited attribute.*/
    void setVisited(bool visited);

    /** @brief  Set pred attribute.*/
    void setPred(int pred);

    /** @brief  Set name attribute.*/
    void setName(const string &name);

    /** @brief  Set zone attribute.*/
    void setZone(const string &zone);

    /** @brief  Set latitude attribute.*/
    void setLatitude(float latitude);

    /** @brief  Set longitude attribute.*/
    void setLongitude(float longitude);

    /** @brief  Set predLine attribute.*/
    void setPredLine(string line);

    //Adds
    /** @brief  Add an edge.*/
    void addEdge(Edge& edge);

    /** @brief  Add an edge.*/
    void addEdge(int dest, double weight, string code);

    //Seachs
    /** @brief  Find for a Stop in the list adj .*/
    bool isInAdj(Stop &stop);

    //Operators
    /**
    * @brief Operator overload.
    */
    friend bool operator==(const Stop& s1, const Stop& s2){
        return (s1.code==s2.code);
    }
    /**
    * @brief Operator overload.
    */
    friend istream &operator>>(istream &is, Stop &stop);


};


using namespace std;
class Edge{
private:
    int dest;
    double weight;
    string lineCode;
public:
    // Constructors
    /**
    * @brief Received the necessary attributes to create a Stop object.
    * @param dest
    * @param weight
    * @param lineCode
    */
    Edge(int dest, double weight, string lineCode);

    //Gets
    /** @brief  Get dest attribute.*/
    int getDest();

    /** @brief  Get weight attribute.*/
    double getWeight() const;

    /** @brief  Get lineCode attribute.*/
    string getLineCode();

    //Sets
    /** @brief  Set dest attribute.*/
    void setDest(int dest);

    /** @brief  Set weight attribute.*/
    void setWeight(double weight);

    /** @brief  Set lineCode attribute.*/
    void setLineCode(string lineCode);

    //Operators
    /**
    * @brief Operator overload.
    */
    friend bool operator==(const Edge& e1, const Edge& e2){
        return(e1.weight==e2.weight && e1.lineCode==e2.lineCode && e1.dest==e2.dest);
    }

};

#endif //STOPEDGE_H
