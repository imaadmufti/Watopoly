#include "grid.h"

#include <random>

void Grid::addPlayer(std::shared_ptr<Player> p) {
    players[p->getName()] = p;
}
void Grid::deletePlayer(std::shared_ptr<Player> p) {
    players.erase(p->getName());
}

bool checkAfford(std::shared_ptr<Player> p, int payment) {
    if (payment <= p->getAsset())
        return true;
    else {
        return false;
    }
}

void Grid::academic(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::shared_ptr<AcadBuilding> acad = acadBuilding[d->getName(p->getNewPos())];
    if (acad->getOwner() == "") {
        std::cout << "Are you willing to purchase " << acad->getName() << "? (y/n)" << std::endl;
        std::string input;
        getline(std::cin, input);
        if (input == "y" || input == "Y") {
            if (p->getAsset() <= acad->getPurchaseCost()) {
                std::cout << "You do not have enough money to purchase. The building will be auctioned." << std::endl;
                auction(p, acad, "", "acad");
            } else {
                p->changeAsset(-acad->getPurchaseCost());
                acad->setOwner(p->getName());
                p->addAcad(acad);
            }
        } else {
            auction(p, acad, "", "acad");
        }
    } else {
        if (acad->getMortgaged()) {
            std::cout << "This building is mortgaged, so you don't need to pay" << std::endl;
            return;
        }
        int amount = acad->getTuition()[acad->getImproveNum()];
        if (players[acad->getOwner()]->ownAllBlock(acad) && acad->getImproveNum() == 0) {
            amount *= 2;
        }
        if (acad->getOwner() != p->getName()) {
            bool afford = checkAfford(p, amount);
            if (afford) {
                p->changeAsset(-amount);
                players[acad->getOwner()]->changeAsset(amount);
                std::cout << "You pay " << amount << "tuition to player " << acad->getOwner() << std::endl;
            } else {
                bankrupt(p, players[acad->getOwner()], amount, d);  //
            }
        }
    }
}

std::shared_ptr<Player> Grid::getResOwner(std::string resName) {
    for (auto ply : players) {
        if (ply.second->getOwnedRes().count(resName) == 1) {
            return ply.second;
        }
    }
    return nullptr;
}
void Grid::residence(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::shared_ptr<Player> owner = getResOwner(d->getName(p->getNewPos()));
    if (!owner) {
        std::cout << "Are you willing to purchase " << d->getName(p->getNewPos()) << "? (y/n)" << std::endl;
        std::string input;
        getline(std::cin, input);
        if (input == "y" || input == "Y") {
            p->changeAsset(-200);
            p->addRes(d->getName(p->getNewPos()));
        } else {
            auction(p, nullptr, d->getName(p->getNewPos()), "res");
        }
    } else {
        if (owner->getOwnedRes()[d->getName(p->getNewPos())]) {
            std::cout << "This building is mortgaged, so you don't need to pay" << std::endl;
            return;
        }
        int amount = 0;
        if (owner != p) {
            if (owner->getResNum() == 1) {
                cout << "The owner own 1 res, so you pay 25" << endl;
                amount = 25;
            } else if (owner->getResNum() == 2) {
                cout << "The owner own 2 res, so you pay 50" << endl;
                amount = 50;
            } else if (owner->getResNum() == 3) {
                cout << "The owner own 3 res, so you pay 100" << endl;
                amount = 100;
            } else if (owner->getResNum() == 4) {
                cout << "The owner own 4 res, so you pay 200" << endl;
                amount = 200;
            }
        }
        bool afford = checkAfford(p, amount);
        if (afford) {
            p->changeAsset(-amount);
            owner->changeAsset(amount);
        } else {
            bankrupt(p, owner, amount, d);
        }
    }
}
std::shared_ptr<Player> Grid::getGymOwner(std::string gymName) {
    for (auto ply : players) {
        if (ply.second->getOwnedGym().count(gymName) == 1) {
            return ply.second;
        }
    }
    return nullptr;
}
void Grid::gym(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::shared_ptr<Player> owner = getGymOwner(d->getName(p->getNewPos()));
    if (!owner) {
        std::cout << "Are you willing to purchase " << d->getName(p->getNewPos()) << "? (y/n)" << std::endl;
        std::string input;
        getline(std::cin, input);
        if (input == "y" || input == "Y") {
            p->changeAsset(-150);
            p->addGym(d->getName(p->getNewPos()));
        } else {
            auction(p, nullptr, d->getName(p->getNewPos()), "gym");
        }
    } else {
        if (owner->getOwnedGym()[d->getName(p->getNewPos())]) {
            std::cout << "This building is mortgaged, so you don't need to pay" << std::endl;
            return;
        }
        int amount = 0;
        if (owner != p) {
            interpreter i;
            int die1 = i.roll();
            int die2 = i.roll();
            if (owner->getGymNum() == 1) {
                cout << "The owner own 1 gym, so you pay ( " << die1 << " + " << die2 << " ) * 4" << endl;
                amount = (die1 + die2) * 4;
            } else if (owner->getGymNum() == 2) {
                cout << "The owner own 2 gym, so you pay ( " << die1 << " + " << die2 << " ) * 10" << endl;
                amount = (die1 + die2) * 10;
            }
        }
        bool afford = checkAfford(p, amount);
        if (afford) {
            p->changeAsset(-amount);
            owner->changeAsset(amount);
        } else {
            bankrupt(p, owner, amount, d);
        }
    }
}
void Grid::osap(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    if (!p->getGoTims()) {
        changeAsset(p, 200);
    }
}
int Grid::timsLine(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::cout << "Player " << p->getName() << ", please choose from the following to get out of Tims" << std::endl;
    std::cout << "1. Roll a double" << std::endl;
    std::cout << "2. Pay $50" << std::endl;
    std::cout << "3. Use a Roll up and Rims Cup" << std::endl;
    std::cout << "Choose from 1, 2, 3 " << std::endl;
    interpreter i;
    string choose;
    int die1;
    int die2;
    bool afford;
    while (true) {
        getline(std::cin, choose);
        if (stoi(choose) >= 1 && stoi(choose) <= 3) {
            break;
        } else {
            std::cerr << "Wrong number. Enter again" << std::endl;
        }
    }
    switch (stoi(choose)) {
        case 1:
            die1 = i.roll();
            die2 = i.roll();
            if (die1 == die2) {
                std::cout << "Congraduations! You rolled " << die1 + die2 << " and can leave" << std::endl;
                p->setGoTims(false);
                p->setTurnsInTims(0);
                return 0;
            } else {
                if (3 == p->getTurnsInTims()) {
                    std::cout << "You You rolled " << die1<< " and " << die2 << ", and this is the third round in Tims. So choose 2 or 3 to get out" << std::endl;
                    while (true) {
                        getline(std::cin, choose);
                        if (stoi(choose) == 2 || stoi(choose) == 3) {
                            break;
                        } else {
                            std::cerr << "Wrong number. Enter again" << std::endl;
                        }
                    }
                    if (stoi(choose) == 2) {
                        afford = checkAfford(p, 50);
                        if (afford) {
                            std::cout << "You paid successfully" << std::endl;
                            p->changeAsset(-50);
                            p->setGoTims(false);
                            p->setTurnsInTims(0);
                            return die1 + die2;
                        } else {
                            bankrupt(p, nullptr, 50, d);
                            p->setGoTims(false);
                            return 0;
                        }
                    } else {
                        if (p->getCup() == 0) {
                            std::cout << "You dont have cup. Please pay" << std::endl;
                            afford = checkAfford(p, 50);
                            if (afford) {
                                std::cout << "You paid successfully" << std::endl;
                                p->changeAsset(-50);
                                p->setGoTims(false);
                                p->setTurnsInTims(0);
                                return die1 + die2;
                            } else {
                                bankrupt(p, nullptr, 50, d);
                                p->setGoTims(false);
                                return 0;
                            }
                        } else {
                            std::cout << "You used cup to get out" << std::endl;
                            p->setCup(p->getCup() - 1);
                            p->setGoTims(false);
                            p->setTurnsInTims(0);
                            return die1 + die2;
                        }
                    }
                } else {
                    std::cout << "You You rolled " << die1 + die2 << ". Stay in Tims" << std::endl;
                    p->setTurnsInTims(p->getTurnsInTims() + 1);
                    return 0;
                }
            }
        case 2:
            afford = checkAfford(p, 50);
            if (afford) {
                std::cout << "You paid successfully" << std::endl;
                p->changeAsset(-50);
                p->setGoTims(false);
                p->setTurnsInTims(0);
                return 0;
            } else {
                bankrupt(p, nullptr, 50, d);
                p->setGoTims(false);
                return 0;
            }
        case 3:
            if (p->getCup() == 0) {
                std::cout << "You dont have cup. End turn" << std::endl;
                p->setTurnsInTims(p->getTurnsInTims() + 1);
                return 0;
            } else {
                std::cout << "You used cup to get out" << std::endl;
                p->setCup(p->getCup() - 1);
                p->setGoTims(false);
                p->setTurnsInTims(0);
                totalCup -= 1;
                return 0;
            }
    }
}

void Grid::goToTims(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    p->setGoTims(true);
    p->setTurnsInTims(1);
    p->setPos(d->getPosition("DC Tims Line") - p->getNewPos());
    d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());  // position for tims counting clockwise. OSAP is position 0
    d->notify();
}
void Grid::gooseNesting(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::cout << "You are attacted by a bunch of geese. Nothing else happened." << std::endl;
}
void Grid::tuition(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::cout << "Choose between paying $300 or 10% of your total asset. (Type 1 or 2 to choose)" << std::endl;
    string input;
    getline(std::cin, input);
    if (input == "2") {
        int amount = p->getAsset() / 10;
        for (auto i : p->getOwnedAcad()) {
            amount += i.second->getPurchaseCost();
            if (i.second->getImproveNum() != 0) {
                amount += i.second->getImproveNum() * i.second->getImproveCost();
            }
        }
        for (auto i : p->getOwnedGym()) {
            amount += 150;
        }
        for (auto i : p->getOwnedRes()) {
            amount += 200;
        }
        bool afford = checkAfford(p, amount);
        if (afford) {
            p->changeAsset(-amount);
        } else {
            bankrupt(p, nullptr, amount, d);
        }
    } else {
        int amount = 300;
        bool afford = checkAfford(p, amount);
        if (afford) {
            p->changeAsset(-amount);
        } else {
            bankrupt(p, nullptr, amount, d);
        }
    }
}
void Grid::coop(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    int amount = 150;
    bool afford = checkAfford(p, amount);
    cout << "You need to pay 150 to COOP" <<  endl;
    if (afford) {
        p->changeAsset(-amount);
    } else {
        bankrupt(p, nullptr, amount, d);
    }
}
void Grid::SLC(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dis({0.125, 0.167, 0.167, 0.125, 0.167, 0.167, 0.0416, 0.0416});
    std::discrete_distribution<> cup({0.99, 0.01});
    int rcup = cup(gen);
    if (rcup == 1 && totalCup < 4) {
        std::cout << "You have won a Roll Up the Rim Cup!\n";
        p->setCup(p->getCup() + 1);
        totalCup += 1;
    }
    interpreter i;
    Grid& grid = *this;
    int roll = dis(gen);
    switch (roll) {
        case 0:
            std::cout << "Back 3\n";
            p->setPos(-3);
            d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());
            d->notify();
            i.use(grid, d, d->getName(p->getNewPos()), p);
            break;
        case 1:
            std::cout << "Back 2\n";
            p->setPos(-2);
            d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());
            d->notify();
            i.use(grid, d, d->getName(p->getNewPos()), p);
            break;
        case 2:
            std::cout << "Back 1\n";
            p->setPos(-1);
            d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());
            d->notify();
            i.use(grid, d, d->getName(p->getNewPos()), p);
            break;
        case 3:
            std::cout << "Forward 1\n";
            p->setPos(1);
            d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());
            d->notify();
            i.use(grid, d, d->getName(p->getNewPos()), p);
            break;
        case 4:
            std::cout << "Forward 2\n";
            p->setPos(2);
            d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());
            d->notify();
            i.use(grid, d, d->getName(p->getNewPos()), p);
            break;
        case 5:
            std::cout << "Forward 3\n";
            p->setPos(3);
            d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());
            d->notify();
            i.use(grid, d, d->getName(p->getNewPos()), p);
            break;
        case 6:
            std::cout << "Go to DC timsLine\n";
            goToTims(p, d);
            break;
        case 7:
            std::cout << "Collect OSAP in advance\n";
            p->setPos(-(p->getNewPos() - 0));
            d->updatePlayer(p->getName()[0], p->getCurrPos(), p->getNewPos());
            d->notify();
            osap(p, d);
            p->changeAsset(200);
            break;
    }
}
void Grid::needlesHall(std::shared_ptr<Player> p, std::shared_ptr<Display> d) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dis({0.05556, 0.11111, 0.16667, 0.33333, 0.16667, 0.11111, 0.05556});
    std::discrete_distribution<> cup({0.99, 0.01});
    int rcup = cup(gen);
    if (rcup == 1 && totalCup < 4) {
        std::cout << "You have won a Roll Up the Rim Cup!\n";
        p->setCup(p->getCup() + 1);
        totalCup += 1;
    }
    int roll = dis(gen);
    int amount;
    bool afford;
    switch (roll) {
        case 0:
            std::cout << "Lose $200\n";
            amount = 200;
            afford = checkAfford(p, amount);
            if (afford) {
                p->changeAsset(-amount);
            } else {
                bankrupt(p, nullptr, amount, d);
            }
            break;
        case 1:
            std::cout << "Lose $100\n";
            amount = 100;
            afford = checkAfford(p, amount);
            if (afford) {
                p->changeAsset(-amount);
            } else {
                bankrupt(p, nullptr, amount, d);
            }
            break;
        case 2:
            std::cout << "Lose $50\n";
            amount = 50;
            afford = checkAfford(p, amount);
            if (afford) {
                p->changeAsset(-amount);
            } else {
                bankrupt(p, nullptr, amount, d);
            }
            break;
        case 3:
            std::cout << "Gain $25\n";
            p->changeAsset(25);
            break;
        case 4:
            std::cout << "Gain $50\n";
            p->changeAsset(50);
            break;
        case 5:
            std::cout << "Gain $100\n";
            p->changeAsset(100);
            break;
        case 6:
            std::cout << "Gain $200\n";
            p->changeAsset(200);
            break;
    }
}
void Grid::changeAsset(std::shared_ptr<Player> p, int offset) {
    p->changeAsset(offset);
}
void Grid::bankrupt(std::shared_ptr<Player> p, std::shared_ptr<Player> owner, int amount, std::shared_ptr<Display> d) {
    string mortgage;
    interpreter inter;
    bool afford = true;
    while (p->getAsset() < amount) {
        std::cout << "Please sell improvements, mortgate properties to raise money. You can also decleare bankruptcy if you are not able to raise money\n";
        std::cout << "Type \'bankrupt\' to declare bankruptcy. Follow program commands to raise money.\n";
        std::cout << "Type improve <property> to sell improvements; Type mortgage <property> to mortgage <property>\n";
        std::cout << "Your current assets are: " << std::endl;
        inter.assets(p);
        std::cout << "You need to raise money to " << amount << std::endl;
        std::string word;
        std::cin >> word;
        if (word == "bankrupt") {
            p->setBankrupt(true);
            if (owner) {
                owner->changeAsset(p->getAsset());
                owner->setCup(p->getCup());
                for (auto a : p->getOwnedAcad()) {
                    a.second->setOwner(owner->getName());
                    owner->addAcad(a.second);
                    if (a.second->getMortgaged()) {
                        std::cout << "Pay 10% to the bank since " << a.second->getName() << " is mortgaged" << std::endl;
                        afford = checkAfford(owner, 0.1 * a.second->getPurchaseCost());
                        if (afford) {
                            owner->changeAsset(-0.1 * a.second->getPurchaseCost());
                        } else {
                            bankrupt(owner, nullptr, -0.1 * a.second->getPurchaseCost(), d);
                            return;
                        }
                        std::cout << "Choose to pay 50% to unmortgage now, or pay 10% to leave it mortgaged. Enter 50 or 10" << std::endl;
                       std::cin>> mortgage;
                        if (mortgage == "50") {
                            afford = checkAfford(owner, 0.5 * a.second->getPurchaseCost());
                            if (afford) {
                                owner->changeAsset(-0.5 * a.second->getPurchaseCost());
                                a.second->setMortgaged(false);
                            } else {
                                bankrupt(owner, nullptr, -0.5 * a.second->getPurchaseCost(), d);
                                return;
                            }
                        } else {
                            afford = checkAfford(owner, 0.1 * a.second->getPurchaseCost());
                            if (afford) {
                                owner->changeAsset(-0.1 * a.second->getPurchaseCost());
                            } else {
                                bankrupt(owner, nullptr, -0.1 * a.second->getPurchaseCost(), d);
                                return;
                            }
                        }
                    }
                }
                for (auto r : p->getOwnedRes()) {
                    owner->addRes(r.first);
                    if (r.second) {
                        std::cout << "Pay 10% to the bank since " << r.first << " is mortgaged" << std::endl;
                        afford = checkAfford(owner, 0.1 * 200);
                        if (afford) {
                            owner->changeAsset(-0.1 * 200);
                        } else {
                            bankrupt(owner, nullptr, -0.1 * 200, d);
                            return;
                        }
                        std::cout << "Choose to pay 50% to unmortgage now, or pay 10% to leave it mortgaged. Enter 50 or 10" << std::endl;
                        std::cin >> mortgage;
                        if (mortgage == "50") {
                            afford = checkAfford(owner, 0.5 * 200);
                            if (afford) {
                                r.second = false;
                                owner->changeAsset(-0.5 * 200);
                            } else {
                                bankrupt(owner, nullptr, -0.5 * 200, d);
                                return;
                            }
                        } else {
                            afford = checkAfford(owner, 0.1 * 200);
                            if (afford) {
                                owner->changeAsset(-0.1 * 200);
                            } else {
                                bankrupt(owner, nullptr, -0.1 * 200, d);
                                return;
                            }
                        }
                    }
                    owner->setResMortgage(r.first, r.second);
                }
                for (auto g : p->getOwnedGym()) {
                    owner->addGym(g.first);
                    if (g.second) {
                        std::cout << "Pay 10% to the bank since " << g.first << " is mortgaged" << std::endl;
                        afford = checkAfford(owner, 0.1 * 150);
                        if (afford) {
                            owner->changeAsset(-0.1 * 150);
                        } else {
                            bankrupt(owner, nullptr, -0.1 * 150, d);
                            return;
                        }
                        std::cout << "Choose to pay 50% to unmortgage now, or pay 10% to leave it mortgaged. Enter 50 or 10" << std::endl;
                        std::cin >> mortgage;
                        if (mortgage == "50") {
                            afford = checkAfford(owner, 0.5 * 150);
                            if (afford) {
                                g.second = false;
                                owner->changeAsset(-0.5 * 150);
                            } else {
                                bankrupt(owner, nullptr, -0.5 * 150, d);
                                return;
                            }
                        } else {
                            afford = checkAfford(owner, 0.1 * 150);
                            if (afford) {
                                owner->changeAsset(-0.1 * 150);
                            } else {
                                bankrupt(owner, nullptr, -0.1 * 150, d);
                                return;
                            }
                        }
                    }
                    owner->setResMortgage(g.first, g.second);
                }
            } else {  // properties goes back to the bank, rimCups are destroyed
                for (auto a : p->getOwnedAcad()) {
                    a.second->setOwner("");
                    p->setAcadMortgaged(a.first, false);
                    auction(p, a.second, a.second->getName(), "acad");
                    p->deleteAcad(a.first);
                }
                for (auto r : p->getOwnedRes()) {
                    p->setResMortgage(r.first, false);
                    auction(p, nullptr, r.first, "res");
                    p->deleteRes(r.first);
                }
                for (auto g : p->getOwnedGym()) {
                    p->setGymMortgated(g.first, false);
                    auction(p, nullptr, g.first, "gym");
                    p->deleteGym(g.first);
                }
                p->setCup(0);
            }
            return;
        } else if (word == "improve") {  // player can only sell
            string property;
            std::cin>> property;
            inter.sellImprove(p, p->getOwnedAcad()[property], d);
        } else if (word == "mortgage") {
            string mortgage;
            string property;
            std::cin >> property;
            inter.mortgage(p, property);
        }
    }
    p->changeAsset(-amount);
    owner->changeAsset(amount);
    std::cout << "You have paid off your debt. Game on." << std::endl;
}

// commands: withdraw / bid #amount
void Grid::auction(std::shared_ptr<Player> p, std::shared_ptr<AcadBuilding> acad, std::string name, std::string type) {
    auto temp = players;
    temp.erase(p->getName());  // erase the player who did not purchase this building before the auction
    for (auto i = temp.begin(); i != temp.end(); i++) {
        if (i->second->getBankrupt()) {
            auto deleted = i;
            i++;
            temp.erase(i);
            if (temp.size() == 1) {
                break;
            }
        }
    }
    int participant = temp.size();
    std::cout << "Auction: Type \"bid #amount\" to place bid or \"withdraw\" to withdraw from auction when it's your turn. Bid " << name << std::endl;
    // initial amount is 0
    int highestBid = 0;
    while (participant > 1) {
        //auto it = m.cbegin(), next_it = it; it != m.cend(); it = next_it
        for (auto ply = temp.begin(), next = ply; ply != temp.end(); ply = next) {
            ++next;
            if (participant == 1) break;
            std::cout << highestBid << std::endl;
            std::cout << "Player " << ply->second->getName() << ": ";
            std::string s;
            std::cin >> s;
            if (s == "withdraw") {
                participant--;
                temp.erase(ply->first);
            } else if (s == "bid") {
                int amt;
                std::cin >> amt;
                if (amt > ply->second->getAsset()) {
                    std::cout << "You don't have enough money to bid" << std::endl;
                }
                if (amt > highestBid) {
                    highestBid = amt;
                }
            }
        }
    }
    std::cout << temp.begin()->first << ", you win " << name << std::endl;
    temp.begin()->second->changeAsset(-highestBid);
    if (type == "acad") {
        temp.begin()->second->addAcad(acad);
        acad->setOwner(temp.begin()->first);
    } else if (type == "res") {
        temp.begin()->second->addRes(name);
    } else if (type == "gym") {
        temp.begin()->second->addGym(name);
    }
}
