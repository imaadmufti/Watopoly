#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

class Grid;
class Player;
class AcadBuilding;
class Display;
using std::shared_ptr;

class interpreter {
    typedef void (Grid::*FuncPtr)(std::shared_ptr<Player>, std::shared_ptr<Display> display);
    std::map<std::string, FuncPtr> funcMap;
    bool isEligible(std::string player, std::shared_ptr<AcadBuilding> building);                              //isEigible will determine if a player is eligible for the improvement on this building
    bool accept();                                                                                            // accept will interact wite the user to see if the user accept the trade
    void saveNotAcad(std::shared_ptr<Grid> grid, std::shared_ptr<std::ofstream> file, std::string property);  // this function is the helper function for save to deal with not acad properties
   public:
    void createSquares(std::shared_ptr<Display> display);  // create squares will custom a board by pushing squares into display
    bool isInt(std::string str);
    void use(Grid& grid, std::shared_ptr<Display> display, std::string name, std::shared_ptr<Player> player);
    interpreter();
    void startGame(std::shared_ptr<Grid> grid, std::shared_ptr<Display> display);                                               // startGame initialize the grid by interacting with the users
    bool endGame(std::shared_ptr<Grid> grid);                                                                                   // endGame returns true if there is only one player left in the game
    int roll();                                                                                                                 // roll returns a random number from 1 to 6
    void buyImprove(std::shared_ptr<Player> player, std::shared_ptr<AcadBuilding> building, std::shared_ptr<Display> display);  //buyImprove will build the improvement of the building if the player is suitable for it
    void sellImprove(std::shared_ptr<Player> player, std::shared_ptr<AcadBuilding> building, std::shared_ptr<Display> display);
    void mortgage(std::shared_ptr<Player> player, std::string property);                                                                 //mortage will mark the building as mortaged and the player will not earn assets from it anymore
    void umortgage(std::shared_ptr<Player> player, std::string property);                                                                //umortage will umortage the building that the player previously mortaged
    void buyFrom(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::string property, int price);                     // buyFrom will let player1 give a trade for buying the property from player2 with the amount of money
    void sellTo(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::string property, int price);                      // sellTo will let player1 give a trade for selling the property to player2 with the amount of money
    void tradeProperty(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::string property1, std::string property2);  // tradeProperty will let player1 give a trade for giving the property1 to player2 with the property2 as return
    void all(std::shared_ptr<Grid> grid);                                                                                                //all prints out the assets and owned properties for every player
    void assets(std::shared_ptr<Player> player);                                                                                         //assets prints out the assets and owned properties for the specified player
    void save(std::shared_ptr<Grid> grid, std::shared_ptr<std::ofstream> file, std::shared_ptr<Display> display);                                                          //save the game with given file
    void loadGame(std::shared_ptr<Grid> grid, std::shared_ptr<std::ifstream> file, std::shared_ptr<Display> display);                    //load the game from given file
};

#endif
