// ****************************************************************************************************
// ****************************************** CONTROLLER_CPP__ ****************************************
// ****************************************************************************************************

#include "Controller.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <xmath.h>
#include <functional>
#include <chrono>


Controller::Controller() {
}

bool Controller::readInput(int inNo) {
    ifstream inputFile;
    inputFile.open("../input/in" + to_string(inNo));
    if (inputFile.fail()) {
        return false;
    }
    else {
        string line;
        getline(inputFile, line);
        while (!inputFile.eof() && inputFile.peek() != '\n') {
            break;
        }
        inputFile.close();
    }
    return true;
}

Controller::~Controller(){
    linesDB.clear();
    stopDB.clear();
}

vector<Line> Controller::getLines() {
    return linesDB;
}

vector<Stop>& Controller::getStops() {
    return stopDB;
}





