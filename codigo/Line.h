// ****************************************************************************************************
// *********************************************** LINE_H__ *****************************************
// ****************************************************************************************************

#ifndef UNTITLED_LINE_H
#define UNTITLED_LINE_H

#include "string"
#include "vector"
#include "StopEdge.h"

using namespace std;

class Line {
private:
    string code;
    string name;
    vector<int> l0 = vector<int>();
    vector<int> l1= vector<int>();


public:
    // Constructors
    /**
     * @brief  Default constructor.
     *
     */
    Line();
    /**
    * @brief Received the necessary attributes to create a Line object.
    * @param code
    * @param name
    */
    Line(const string &code, const string &name);

    //Deconstructors
    /** @brief  Default destructor.*/
    ~Line();

    //Gets
    /** @brief  Get code attribute.*/
    const string &getCode() const;

    /** @brief  Get name attribute.*/
    const string &getName() const;

    /** @brief  Get l0 attribute.*/
     vector<int>& getL0();

    /** @brief  Get l1 attribute.*/
     vector<int>& getL1();

     //Sets

    /** @brief  Set l0 attribute.*/
    void setL0(const vector<int> l0) ;

    /** @brief  Set l1 attribute.*/
    void setL1(const vector<int> l1);

    /** @brief  Set code attribute.*/
    void setCode(const string &code);

    /** @brief  Set name attribute.*/
    void setName(const string &name);

    //Reads
    /**
    * @brief Operator overload.
    */
    friend istream &operator>>(istream &is, Line &line);
};


#endif //UNTITLED_LINE_H
