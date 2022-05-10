// ****************************************************************************************************
// ****************************************** MENU_CPP__ **********************************************
// ****************************************************************************************************
#include "Menu.h"
#include <algorithm>
#include <iostream>
using namespace std;

int Menu::printOptionsMenu(vector<string> options, string header, string footer) {
    string option = "";
    vector<string> validOpts;
    for(int i; i<options.size(); i++)
        validOpts.push_back(to_string(i));
    while (find(validOpts.begin(), validOpts.end(), option)== validOpts.end()) {
        printUpperFrame();
        if(header!="")
            cout << header << endl;
        for(size_t i=0; i<options.size(); i++)
            cout << i << ") " << options[i]<<endl;
        printLowerFrame();

        if (find(validOpts.begin(), validOpts.end(), option)== validOpts.end() && option!="")
            cout << "Invalid Input!";
        cout << endl;
        if (footer=="")
            cout << "Pick a number: ";
        else
            cout << footer;
        option = askCin();
        System::clearScreen();
    }
    return stoi(option);
}

void Menu::printLowerFrame(){
    for (size_t i = 0; i < 62; i++)
        cout << (char)205;
    cout << endl;
}

void Menu::printUpperFrame() {
    for (size_t i = 0; i < 54; i++)
        cout << (char)205;
    cout << (char)185 <<"Q:Quit" << (char)204 << endl;
}

string Menu::anyInputMenu(string message, string footer, bool ignoreSpaces){
    printUpperFrame();
    cout << message << endl;
    printLowerFrame();
    if(footer!="")
        cout << footer;
    string ret = askCin(ignoreSpaces);
    System::clearScreen();
    return ret;
}

string Menu::intInputMenu(string message, string footer, int lowerBound, int upperBound, bool ignoreSpaces){
    string ret = "batata";
    while(!checkIntInput(ret, lowerBound, upperBound)){
        printUpperFrame();
        cout << message << endl;
        printLowerFrame();
        if(footer!="")
            cout << footer;
        if(ret!="batata")
            cout << "\nInput needs to be an integer!";
        ret = askCin(ignoreSpaces);
        System::clearScreen();
    }
    return ret;
}

void Menu::singleInputScreen(string m1, string requestedInput, string m2){
    string input = "";
    while(input != requestedInput) {
        printUpperFrame();
        cout << m1 << endl;
        printLowerFrame();
        if(input!="")
            cout << "Invalid Input!" << endl;
        if (m2!="")
            cout << m2 << endl;
        else
            cout << "Type " << requestedInput << " to go back: ";
        input = askCin();
        System::clearScreen();
    }
}

vector<string> Menu::getMainOps() {return mainOptions;};

int Menu::getOption(){return option;};

void Menu::setOption(int op){option = op;};

Menu::Menu(Controller& control) {
    mainOptions = {};
    option = -1;
    controller = &control;
}

string Menu::askCin(bool ignore_spaces){ // replacement of the cin func , accounting for system exits on any input
    string input;
    if (ignore_spaces)
        getline(cin, input); // ignores spaces when getting inputs
    else
        cin >> input;
    if (cin.fail())
        if (cin.eof())
            exit(0);
    if (input == "Q" || input == "q"){
        cout << "\n \nThank you for using our system!\n \n";
        exit(0);
    }
    cin.ignore(256, '\n');
    return input;
}

bool Menu::checkIntInput(string input, int lowerBound, int upperBound) {
    return (is_number(input) && stoi(input)>=lowerBound && stoi(input)<=upperBound);
}

bool Menu::is_coord(const string& s)
{
    string::const_iterator it = s.begin();
    if(*it == '-')
        it++;
    int ptCounter = 0;
    while (it != s.end() && (isdigit(*it) || *it == '.') && ptCounter < 2) {
        if(*it == '.')
            ptCounter++;
        ++it;
    }
    return !s.empty() && it == s.end();
}

bool Menu::is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void Menu::setMainOps(std::vector<string> options) {
    mainOptions = options;
}
