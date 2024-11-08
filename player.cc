#include "player.h"
#include <iostream>

void Player::addAcad(std::shared_ptr<AcadBuilding> acad) { 
    ownedAcad.insert(std::make_pair(acad->getName(), acad)); 
}
bool Player::hasAcad(std::string acadName) { return ownedAcad.count(acadName) == 1; }
void Player::deleteAcad(std::string acadName) { 
    if(hasAcad(acadName)) {
        ownedAcad.erase(acadName);
    }
}

void Player::addRes(std::string res) { 
    ownedRes.insert(std::make_pair(res, false));
}
int Player::getResNum() const {
    return ownedRes.size();
}
void Player::deleteRes(std::string res) { 
    ownedRes.erase(res);
}


void Player::addGym(std::string gym) { 
    ownedGym.insert(std::make_pair(gym, false));
}
int Player::getGymNum() const {
    return ownedGym.size();
}
void Player::deleteGym(std::string gym) {
    ownedGym.erase(gym);
}
void Player::setResMortgage(std::string resName, bool isMortgaged) {
    ownedRes[resName] = isMortgaged;
}
void Player::setGymMortgated(std::string gymName, bool isMortgaged) {
    ownedGym[gymName] = isMortgaged;
}
void Player::setAcadMortgaged(std::string acadName, bool isMortgaged) {
    ownedAcad[acadName]->setMortgaged(isMortgaged);
}

bool Player::ownAllBlock(std::shared_ptr<AcadBuilding> acad) {
    auto blocks = acad->getBlock();
    for(auto block: blocks) {
        if(block->getOwner() != name) {
            return false;
        }
    }
    return true;
}

void Player::setPos(int pos) {
    currPos = newPos;
    newPos += pos;
    if (newPos > 39) {
        newPos -= 40;
        asset += 200;
        std::cout << "You collect the OSAP" << std::endl;
    }
    if (newPos < 0) {
        newPos += 40;
        asset += 200;
        std::cout << "You collect the OSAP" << std::endl;
    }
}

