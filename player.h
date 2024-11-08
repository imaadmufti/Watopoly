#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include "acadBuilding.h"

class Player {
    std::string name;
    bool isBankrupt = false;
    // map containing acadBuilding name and ptr
    std::map<std::string, std::shared_ptr<AcadBuilding>> ownedAcad;
    // string resName, bool isMortgaged
    std::map<std::string, bool> ownedRes;
    // string gymName, bool isMortgaged
    std::map<std::string, bool> ownedGym;
    int currPos;
    int newPos;
    int asset;
    int rimCup;
    bool goToTims;
    int turnsInTims;
    public:
    Player(std::string name, bool isInTims, int currPos, int newPos, int asset, int rimCup, int turnsInTims) :
        name{ name }, goToTims{ isInTims }, newPos{ currPos }, currPos{ newPos }, asset{ asset }, rimCup{ rimCup }, turnsInTims{ turnsInTims }  {}

    // get player name
    std::string getName() const { return name; }
    // get player total asset
    int getAsset() const { return asset; }
    // change player asset by adding either positive or negative offset
    void changeAsset(int offset) { asset += offset; }

    // add new AcadBuilding shared_ptr to the map of academic buildings
    void addAcad(std::shared_ptr<AcadBuilding> acad);
    // determine if an academic building is owned by player
    bool hasAcad(std::string acadName);
    // remove an academic building from ownedAcad
    void deleteAcad(std::string acadName);
    // get map of owned academic building
    std::map<std::string, std::shared_ptr<AcadBuilding>> getOwnedAcad() const { return ownedAcad; }
    
    // insert new residence into ownedRes
    void addRes(std::string res);
    // return the number of residences owned by player
    int getResNum() const;
    // delete res from ownedRes
    void deleteRes(std::string res);
    // get map of ownedRes
    std::map<std::string, bool> getOwnedRes() const { return ownedRes; }

    // change boolean corresponding to the gym name given to true
    void addGym(std::string gym);
    //return the number of gyms owned by player
    int getGymNum() const;
    // delete gym from ownedGym
    void deleteGym(std::string gym);
    // get map of ownedGym
    std::map<std::string, bool> getOwnedGym() const { return ownedGym; }

    int getCurrPos() const { return currPos; }
    int getNewPos() const { return newPos; }
    void setPos(int pos);

    // modify the modified status of buildings
    void setResMortgage(std::string resName, bool isMortgaged);
    void setGymMortgated(std::string gymName, bool isMortgaged);
    void setAcadMortgaged(std::string acadName, bool isMortgaged);

    // get the number of rim cups (outa jail card) owned by player
    int getCup() const { return rimCup; }
    void setCup(int cup) { rimCup = cup; }
    bool getGoTims() const { return goToTims; }
    void setGoTims(bool jail) { goToTims = jail; } 
    int getTurnsInTims() const { return turnsInTims; }
    void setTurnsInTims(int turns) { turnsInTims = turns; }

    // check if the player owns all the buildings in the same block (eg. math, env)
    bool ownAllBlock(std::shared_ptr<AcadBuilding> acad);

    bool getBankrupt() { return isBankrupt; }
    void setBankrupt(bool bankrupt) { isBankrupt = bankrupt; }


    

};


#endif
