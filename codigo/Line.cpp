//
// Created by igcbs on 16/01/2022.
//

#include "Line.h"
#include <iostream>


Line::Line() {
    this->code = "";
    this->name = "";


}
Line::Line(const string &code, const string &name) {
    this->code = code;
    this->name = name;

}

Line::~Line(){
    code.clear();
    name.clear();
    l0.clear();
    l1.clear();
}

const string &Line::getCode() const {
    return code;
}

const string &Line::getName() const {
    return name;
}

void Line::setL0(const vector<int> l)  {
    l0=l;
}
void Line::setL1(const vector<int> l)  {
    l1=l;
}
void Line::setCode(const string &code) {
    this->code = code;
}

void Line::setName(const string &name) {
    this->name = name;
}


istream & operator>>(istream &is, Line &line) {
    char temp[256];
    if(!is.getline(temp, 100, ',')){
        is.ignore();
        return is;
    }
    line.setCode((string)temp);
    is.getline(temp, 100,'\n');
    line.setName((string)temp);
    return is;
}

 vector<int>& Line::getL0() {
    return l0;
}

 vector<int>& Line::getL1() {
    return l1;
}
