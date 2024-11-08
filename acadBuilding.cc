#include "acadBuilding.h"

AcadBuilding::AcadBuilding(std::string name, int purchaseCost, int improveCost, std::vector<int> tuition)
    : name{name}, purchaseCost{purchaseCost}, improveCost{improveCost}, tuition{tuition} {
}

std::string AcadBuilding::getName() const {
    return name;
}

void AcadBuilding::setOwner(std::string name) {
    owner = name;
}

std::string AcadBuilding::getOwner() const {
    return owner;
}

void AcadBuilding::setBlock(std::vector<std::shared_ptr<AcadBuilding>> block) {
    this->block = block;
}

int AcadBuilding::getImproveNum() const {
    return numImprove;
}

bool AcadBuilding::getMortgaged() const {
    return isMortgaged;
}

void AcadBuilding::setMortgaged(bool mortgate) {
    isMortgaged = mortgate;
}

int AcadBuilding::getPurchaseCost() const {
    return purchaseCost;
}

int AcadBuilding::getImproveCost() const {
    return improveCost;
}

std::vector<int> AcadBuilding::getTuition() const {
    return tuition;
}

void AcadBuilding::improve(int num) {
    numImprove += num;
    value = tuition[numImprove];
}

std::vector<std::shared_ptr<AcadBuilding>> AcadBuilding::getBlock() const {
    return block;
}

