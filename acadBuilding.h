#ifndef _ACADBUILDING_
#define _ACADBUILDING_

#include <string>
#include <memory>
#include <vector>

class AcadBuilding {
    std::string name;
    int numImprove = 0;
    // the amount of tuition corresponding to the level of improvements
    std::string owner;
    int purchaseCost;
    int improveCost;
    int value;      // the cost for other players while landing on this building
    bool isMortgaged = false;
    std::vector<int> tuition;
    std::vector<std::shared_ptr<AcadBuilding>> block;

    public: 
    AcadBuilding(std::string name, int purchaseCost, int improveCost, std::vector<int> tuition);
    std::string getName() const;
    void setOwner(std::string name);
    std::string getOwner() const;
    void setBlock(std::vector<std::shared_ptr<AcadBuilding>> block);
    int getImproveNum() const;
    bool getMortgaged() const;
    void setMortgaged(bool mortgate);
    int getPurchaseCost() const;
    int getImproveCost() const;
    std::vector<int> getTuition() const;
    
    // change numImprove and building value based on the number of enhancements
    void improve(int num);

    std::vector<std::shared_ptr<AcadBuilding>> getBlock() const;
};


#endif
