#ifndef _GRID_
#define _GRID_

#include "player.h"
#include "display.h"
#include "acadBuilding.h"
#include "interpreter.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
 
class Grid {
    // vector of tuitions for all academic buildings
    std::vector<int> alTuition {2, 10, 30, 90, 160, 250};
    std::vector<int> mlTuition {4, 20, 60, 180, 320, 450};
    std::vector<int> echTuition {6, 30, 90, 270, 400, 550};
    std::vector<int> pasTuition {6, 30, 90, 270, 400, 550};
    std::vector<int> hhTuition {8, 40, 100, 300, 450, 600};
    std::vector<int> rchTuition {10, 50, 150, 450, 625, 750};
    std::vector<int> dweTuition {10, 50, 150, 450, 625, 750};
    std::vector<int> cphTuition {12, 60, 180, 500, 700, 900};
    std::vector<int> lhiTuition {14, 70, 200, 550, 750, 950};
    std::vector<int> bmhTuition {14, 70, 200, 550, 750, 950};
    std::vector<int> optTuition {16, 80, 220, 600, 800, 1000};
    std::vector<int> ev1Tuition {18, 90, 250, 700, 875, 1050};
    std::vector<int> ev2Tuition {18, 90, 250, 700, 875, 1050};
    std::vector<int> ev3Tuition {20, 100, 300, 750, 925, 1100};
    std::vector<int> physTuition {22, 110, 330, 800, 975, 1150};
    std::vector<int> b1Tuition {22, 110, 330, 800, 975, 1150};
    std::vector<int> b2Tuition {24, 120, 360, 850, 1025, 1200};
    std::vector<int> eitTuition {26, 130, 390, 900, 1100, 1275};
    std::vector<int> escTuition {26, 130, 390, 900, 1100, 1275};
    std::vector<int> c2Tuition {28, 150, 450, 1000, 1200, 1400};
    std::vector<int> mcTuition {35, 175, 500, 1100, 1300, 1500};
    std::vector<int> dcTuition {50, 200, 600, 1400, 1700, 2000};
    // shared_ptr for all academic buildings
    shared_ptr <AcadBuilding> al = std::make_shared<AcadBuilding>("AL", 40, 50, alTuition);       // initilize name
    shared_ptr <AcadBuilding> ml = std::make_shared<AcadBuilding>("ML", 60, 50, mlTuition);
    shared_ptr <AcadBuilding> ech = std::make_shared<AcadBuilding>("ECH", 100, 50, echTuition);
    shared_ptr <AcadBuilding> pas = std::make_shared<AcadBuilding>("PAS", 100, 50, pasTuition);
    shared_ptr <AcadBuilding> hh = std::make_shared<AcadBuilding>("HH", 120, 50, hhTuition);
    shared_ptr <AcadBuilding> rch = std::make_shared<AcadBuilding>("RCH", 140, 100, rchTuition);
    shared_ptr <AcadBuilding> dwe = std::make_shared<AcadBuilding>("DWE", 140, 100, dweTuition);
    shared_ptr <AcadBuilding> cph = std::make_shared<AcadBuilding>("CPH", 160, 100, cphTuition);
    shared_ptr <AcadBuilding> lhi = std::make_shared<AcadBuilding>("LHI", 180, 100, lhiTuition);
    shared_ptr <AcadBuilding> bmh = std::make_shared<AcadBuilding>("BMH", 180, 100, bmhTuition);
    shared_ptr <AcadBuilding> opt = std::make_shared<AcadBuilding>("OPT", 200, 100, optTuition);
    shared_ptr <AcadBuilding> ev1 = std::make_shared<AcadBuilding>("EV1", 220, 150, ev1Tuition);
    shared_ptr <AcadBuilding> ev2 = std::make_shared<AcadBuilding>("EV2", 220, 150, ev2Tuition);
    shared_ptr <AcadBuilding> ev3 = std::make_shared<AcadBuilding>("EV3", 240, 150, ev3Tuition);
    shared_ptr <AcadBuilding> phys = std::make_shared<AcadBuilding>("PHYS", 260, 150, physTuition);
    shared_ptr <AcadBuilding> b1 = std::make_shared<AcadBuilding>("B1", 260, 150, b1Tuition);
    shared_ptr <AcadBuilding> b2 = std::make_shared<AcadBuilding>("B2", 280, 150, b2Tuition);
    shared_ptr <AcadBuilding> eit = std::make_shared<AcadBuilding>("EIT", 300, 200, eitTuition);
    shared_ptr <AcadBuilding> esc = std::make_shared<AcadBuilding>("ESC", 300, 200, escTuition);
    shared_ptr <AcadBuilding> c2 = std::make_shared<AcadBuilding>("C2", 320, 200, c2Tuition);
    shared_ptr <AcadBuilding> mc = std::make_shared<AcadBuilding>("MC", 350, 200, mcTuition);
    shared_ptr <AcadBuilding> dc = std::make_shared<AcadBuilding>("DC", 400, 200, dcTuition);

    // string buildingName, shared_ptr<AcadBuilding>
    std::map<std::string, std::shared_ptr<AcadBuilding>> acadBuilding = {
        {"AL", al},
        {"ML", ml},
        {"ECH", ech},
        {"PAS", pas},
        {"HH", hh},
        {"RCH", rch},
        {"DWE", dwe},
        {"CPH", cph},
        {"LHI", lhi},
        {"BMH", bmh},
        {"OPT", opt},
        {"EV1", ev1},
        {"EV2", ev2},
        {"EV3", ev3},
        {"PHYS", phys},
        {"B1", b1},
        {"B2", b2},
        {"EIT", eit},
        {"ESC", esc},
        {"C2", c2},
        {"MC", mc},
        {"DC", dc}
    };
    //map of player name and player shared_ptr
    std::map<std::string, std::shared_ptr<Player>> players;
    // group AcadBuildings by block
    std::vector<std::shared_ptr<AcadBuilding>> arts1 {al, ml};
    std::vector<std::shared_ptr<AcadBuilding>> arts2 {ech, pas, hh};
    std::vector<std::shared_ptr<AcadBuilding>> eng {rch, dwe, cph};
    std::vector<std::shared_ptr<AcadBuilding>> health {lhi, bmh, opt};
    std::vector<std::shared_ptr<AcadBuilding>> env {ev1, ev2, ev3};
    std::vector<std::shared_ptr<AcadBuilding>> sci1 {phys, b1, b2};
    std::vector<std::shared_ptr<AcadBuilding>> sci2 {eit, esc, c2};
    std::vector<std::shared_ptr<AcadBuilding>> math {mc, dc};

    // Total number of cups
    int totalCup = 0;
    

    // private helppers
    std::shared_ptr<Player> getResOwner(std::string resName);
    std::shared_ptr<Player> getGymOwner(std::string gymName);
    public:
    Grid() {
        al->setBlock(arts1);
        ml->setBlock(arts1);
        ech->setBlock(arts2);
        pas->setBlock(arts2);
        hh->setBlock(arts2);
        rch->setBlock(eng);
        dwe->setBlock(eng);
        cph->setBlock(eng);
        lhi->setBlock(health);
        bmh->setBlock(health);
        opt->setBlock(health);
        ev1->setBlock(env);
        ev2->setBlock(env);
        ev3->setBlock(env);
        phys->setBlock(sci1);
        b1->setBlock(sci1);
        b2->setBlock(sci1);
        eit->setBlock(sci2);
        esc->setBlock(sci2);
        c2->setBlock(sci2);
        mc->setBlock(math);
        dc->setBlock(math);
    }
    void addPlayer(std::shared_ptr<Player>);
    void deletePlayer(std::shared_ptr<Player>);
    std::map<std::string, std::shared_ptr<Player>> getPlayers() { return players; }
    std::map<std::string, std::shared_ptr<AcadBuilding>> getAcadBuildings() { return acadBuilding; }
    void academic(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void residence(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void gym(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void osap(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    // Tims Line Square, nothing happens while landing on this square
    // if player is in jail, return -1 if he is in thrid turn and fails to roll double
    int timsLine(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    // the player is sent to tims
    void goToTims(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void gooseNesting(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    // interact with user to decide if the player pays 300 or 10% of their total worth
    void tuition(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void coop(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void SLC(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void needlesHall(std::shared_ptr<Player>, std::shared_ptr<Display> d);
    void changeAsset(std::shared_ptr<Player> p, int offset);   
    void bankrupt(std::shared_ptr<Player> p, std::shared_ptr<Player> owner, int amount, std::shared_ptr<Display> d);
    // auction on building without player p
    void auction(std::shared_ptr<Player> p, std::shared_ptr<AcadBuilding> acad, std::string name, std::string type);
    void doNothing(std::shared_ptr<Player>, std::shared_ptr<Display> d) {} // for players step in the Tims Line square

};

#endif
