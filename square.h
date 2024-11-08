#ifndef SQUARE_H
#define SQUARE_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <string>

using std::string;

class Square {
    string name;
    bool isAcad;
    int improvements;
    std::vector<char> players;

   public:
    // Constructor
    // Takes in the name of the building and true if the building is an academic building, and false otherwise.
    // Initialises a new Square with the input name and isAcad, with no players or improvements present.
    Square(string name, bool isAcad);

    // name accessor
    string getName();
    string getNameTop();
    // printNameTop() and printNameBottom() are funtions that assist with name formatting for display.
    // all names should fit in appropriately into two lines of 7 characters
    // printNameTop() prints the first line for the name section, with appropriate spacing
    void printNameTop();
    // printNameBottom() prints the second line for the name section, with appropriate spacing
    void printNameBottom();

    // players accessor
    std::vector<char> getPlayers();
    // printPlayers() prints players within the square
    void printPlayers();
    // player mutator functions
    void addPlayer(char player);
    void removePlayer(char player);

    // isAcad accessor
    bool getAcad();

    // improvements accessor
    int getImprovements();
    // improvements mutator, increases the improvements field by n (use negative n to decrease)
    void changeImprovements(int n);
    // printImprovements() prints the improvements of the square as they would appear on the board
    void printImprovements();
};

#endif
