#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#include "square.h"

using std::cout;
using std::endl;
using std::string;

class Display {
    std::vector<std::shared_ptr<Square>> squares;

   public:
    // getPosition returns the position of the building
    int getPosition(string building);

    int getSquareNum(int position);

    void addSquare(std::shared_ptr<Square> square);

    // updatePlayer updates the position of a player
    // (removes a player from the oldPos square and adds the same player to the newPos square)
    // (let x be a valid square)
    // (using x as oldPos and -1 as the newPos removes the player from the game)
    // (using -1 as oldPos and x as newPos adds a player into the game)
    void updatePlayer(char player, int oldPos, int newPos);

    // updateImp changes the improvement of a building by impNum
    void updateImp(string building, int impNum);

    // getName returns the name of the building at the squareNum position
    string getName(int position);

    // rearrange() rearranges the positions of the squares, changing up the formation of the board
    void rearrange();

    // notify() prints out the entire board with present player positions and improvements
    // (notifies the user)
    void notify();
};

#endif
