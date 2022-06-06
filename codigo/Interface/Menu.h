// ****************************************************************************************************
// ****************************************** MENU_H__ ************************************************
// ****************************************************************************************************

/*! The superclass which all other Menu's implement */


#ifndef PROJ1_MENU_H
#define PROJ1_MENU_H
#include <string>
#include <vector>
#include "System.h"
#include "../Controller.h"
using namespace std;
class Menu{
protected:
    int option; //!< common use integer, starts as -1
    vector<string> mainOptions; //!< common use vector, frequently used as a parameter
    Controller* controller; //!< information handler for the whole system
public:
    Menu(Controller& control); //!< class creator
    string askCin(bool ignore_spaces = false); //!< replacement for the cin functionality, taking save and exit into account
    void setMainOps(std::vector<string> options); //!< mainOps Setter
    vector<string> getMainOps(); //!< mainOps Getter
    void setOption(int option); //!< option Setter
    int getOption(); //!< option Getter
    int printOptionsMenu(vector<string> options, string header="", string footer=""); //!< menu printer based on options from string vector
    string anyInputMenu(string message, string footer = "", bool ignoreSpaces = false); //!< menu printer that allows any input
    void singleInputScreen(string m1, string requestedInput="B", string m2=""); //!< menu used for single system messages
    void printLowerFrame(); //!< lower frame printer
    void printUpperFrame(); //!< upper frame printer
    bool checkIntInput(string input, int lowerBound = 0, int upperBound = 1000000 ); //!< verifies if a string is a valid number and between a certain range
    bool is_number(const string &s); //!< verifies is a string can be translated to an integer
    bool is_coord(const string &s);//!< verifies is a string can be translated to an double
    string intInputMenu(string message, string footer = "", int lowerBound = 0, int upperBound = 1000000, bool ignoreSpaces = false);//!< prints a menu and verifies if input string is a valid number and between a certain range
};
#endif //PROJ1_MENU_H

