#include "interpreter.h"

#include "acadBuilding.h"
#include "grid.h"
#include "player.h"
#include "square.h"

interpreter::interpreter() {
    funcMap["Goose Nesting"] = &Grid::gooseNesting;
    funcMap["EV1"] = &Grid::academic;
    funcMap["NEEDLES HALL"] = &Grid::needlesHall;
    funcMap["EV2"] = &Grid::academic;
    funcMap["EV3"] = &Grid::academic;
    funcMap["V1"] = &Grid::residence;
    funcMap["PHYS"] = &Grid::academic;
    funcMap["B1"] = &Grid::academic;
    funcMap["CIF"] = &Grid::gym;
    funcMap["B2"] = &Grid::academic;
    funcMap["GO TO TIMS"] = &Grid::goToTims;
    funcMap["ELT"] = &Grid::academic;
    funcMap["ESC"] = &Grid::academic;
    funcMap["SLC"] = &Grid::SLC;
    funcMap["C2"] = &Grid::academic;
    funcMap["REV"] = &Grid::residence;
    funcMap["MC"] = &Grid::academic;
    funcMap["COOP FEE"] = &Grid::coop;
    funcMap["DC"] = &Grid::academic;
    funcMap["COLLECT OSAP"] = &Grid::doNothing;
    funcMap["AL"] = &Grid::academic;
    funcMap["ML"] = &Grid::academic;
    funcMap["TUITION"] = &Grid::tuition;
    funcMap["MKV"] = &Grid::residence;
    funcMap["ECH"] = &Grid::academic;
    funcMap["PAS"] = &Grid::academic;
    funcMap["HH"] = &Grid::academic;
    funcMap["DC Tims Line"] = &Grid::doNothing;
    funcMap["RCH"] = &Grid::academic;
    funcMap["PAC"] = &Grid::gym;
    funcMap["DWE"] = &Grid::academic;
    funcMap["CPH"] = &Grid::academic;
    funcMap["UWP"] = &Grid::residence;
    funcMap["LHI"] = &Grid::academic;
    funcMap["BMH"] = &Grid::academic;
    funcMap["OPT"] = &Grid::academic;
}

bool interpreter::isEligible(std::string player, std::shared_ptr<AcadBuilding> building) {
    auto block = building->getBlock();
    for (int i = 0; i < block.size(); i++) {
        if (block[i]->getOwner() != player) {
            return false;
        }
    }
    return true;
}

void interpreter::createSquares(std::shared_ptr<Display> display) {
    display->addSquare(std::make_shared<Square>("Goose Nesting", false));
    display->addSquare(std::make_shared<Square>("EV1", true));
    display->addSquare(std::make_shared<Square>("NEEDLES HALL", false));
    display->addSquare(std::make_shared<Square>("EV2", true));
    display->addSquare(std::make_shared<Square>("EV3", true));
    display->addSquare(std::make_shared<Square>("V1", false));
    display->addSquare(std::make_shared<Square>("PHYS", true));
    display->addSquare(std::make_shared<Square>("B1", true));
    display->addSquare(std::make_shared<Square>("CIF", false));
    display->addSquare(std::make_shared<Square>("B2", true));
    display->addSquare(std::make_shared<Square>("GO TO TIMS", false));
    display->addSquare(std::make_shared<Square>("EIT", true));
    display->addSquare(std::make_shared<Square>("ESC", true));
    display->addSquare(std::make_shared<Square>("SLC", false));
    display->addSquare(std::make_shared<Square>("C2", true));
    display->addSquare(std::make_shared<Square>("REV", false));
    display->addSquare(std::make_shared<Square>("NEEDLES HALL", false));
    display->addSquare(std::make_shared<Square>("MC", true));
    display->addSquare(std::make_shared<Square>("COOP FEE", false));
    display->addSquare(std::make_shared<Square>("DC", true));
    display->addSquare(std::make_shared<Square>("COLLECT OSAP", false));
    display->addSquare(std::make_shared<Square>("AL", true));
    display->addSquare(std::make_shared<Square>("SLC", false));
    display->addSquare(std::make_shared<Square>("ML", true));
    display->addSquare(std::make_shared<Square>("TUITION", false));
    display->addSquare(std::make_shared<Square>("MKV", false));
    display->addSquare(std::make_shared<Square>("ECH", true));
    display->addSquare(std::make_shared<Square>("NEEDLES HALL", false));
    display->addSquare(std::make_shared<Square>("PAS", true));
    display->addSquare(std::make_shared<Square>("HH", true));
    display->addSquare(std::make_shared<Square>("DC Tims Line", false));
    display->addSquare(std::make_shared<Square>("RCH", true));
    display->addSquare(std::make_shared<Square>("PAC", false));
    display->addSquare(std::make_shared<Square>("DWE", true));
    display->addSquare(std::make_shared<Square>("CPH", true));
    display->addSquare(std::make_shared<Square>("UWP", false));
    display->addSquare(std::make_shared<Square>("LHI", true));
    display->addSquare(std::make_shared<Square>("SLC", false));
    display->addSquare(std::make_shared<Square>("BMH", true));
    display->addSquare(std::make_shared<Square>("OPT", true));
}

bool interpreter::isInt(std::string str) {
    return (0 == std::count_if(str.begin(), str.end(), [](char n) { return !std::isdigit(n); }));
}

bool interpreter::accept() {
    string answer = "";
    std::cout << "Please type accept or reject of this trade" << std::endl;
    std::cin >> answer;
    while (answer != "accept" && answer != "reject") {
        std::cerr << "only enter accept or reject" << std::endl;
        std::cin >> answer;
    }
    if (answer == "accept") {
        return true;
    } else {
        return false;
    }
}

void interpreter::startGame(std::shared_ptr<Grid> grid, std::shared_ptr<Display> display) {
    int numPlayers = 0;
    std::vector<std::string> names;
    names.emplace_back("G for Goose");
    names.emplace_back("B for BRT Bus");
    names.emplace_back("D for Tim Hortons Doughnut");
    names.emplace_back("P for Professor");
    names.emplace_back("S for Student");
    names.emplace_back("$ for Money");
    names.emplace_back("L for Laptop");
    names.emplace_back("T for Pink tie");
    std::vector<std::string> chars;
    chars.emplace_back("G");
    chars.emplace_back("B");
    chars.emplace_back("D");
    chars.emplace_back("P");
    chars.emplace_back("S");
    chars.emplace_back("$");
    chars.emplace_back("L");
    chars.emplace_back("T");

    display->notify();
    std::cout << "Would you like to use this default board layout?" << std::endl;
    std::cout << "Enter 'y' to proceed with this board, or 'n' if you would like a randomly generated board" << std::endl;
    std::cout << "(Do not save the game if you choose to use a randomly generated board, as only the default board will be saved. Finish the game within a single session if using randomly generated boards.)" << std::endl;
    std::string temp1;
    while (getline(std::cin, temp1)) {
        if (temp1 == "y") break;
        if (temp1 == "n") {
            std::cout << "Randomly Generated new board:" << std::endl;
            display->rearrange();
            display->notify();
            std::cout << "Would you like to use this new board layout?" << std::endl;
            std::cout << "Enter 'y' to proceed with this board, or 'n' if you would like another randomly generated board" << std::endl;
        } else {
            std::cout << "Please enter either 'y' or 'n'" << std::endl;
        }
    }

    std::cout << "Please enter the number of players from 2 to 8:" << std::endl;
    while (getline(std::cin, temp1)) {
        if (isInt(temp1)) {
            numPlayers = std::stoi(temp1);
            if (numPlayers <= 8 && numPlayers >= 2) break;
        }
        std::cerr << "Please enter number from 2 to 8" << std::endl;
    }
    for (int i = 1; i <= numPlayers; i++) {
        std::cout << "Player " << i << ", please choose from the following as your character by entering character:" << std::endl;
        for (int k = 0; k < names.size(); k++) {
            std::cout << names[k] << std::endl;
        }
        std::string character;
        int count = 0;
        bool found = false;
        while (getline(std::cin, character)) {
            for (count; count < chars.size(); count++) {
                if (chars[count] == character) {
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            } else {
                std::cerr << "Incorrect character input" << std::endl;
                count = 0;
            }
        }
        std::shared_ptr<Player> newPlayer = std::make_shared<Player>(character, false, 0, 0, 1500, 0, 0);
        grid->addPlayer(newPlayer);
        display->updatePlayer(character[0], -1, 0);
        names.erase(names.begin() + count);
        chars.erase(chars.begin() + count);
    }
}

bool interpreter::endGame(std::shared_ptr<Grid> grid) {
    auto players = grid->getPlayers();
    return (std::count_if(players.begin(), players.end(), [](std::pair<string, std::shared_ptr<Player>> n) { return !n.second->getBankrupt(); }) <= 1);
}

void interpreter::use(Grid& grid, std::shared_ptr<Display> display, std::string name, std::shared_ptr<Player> player) {
    (grid.*funcMap[name])(player, display);
}

int interpreter::roll() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dis({1, 1, 1, 1, 1, 1});
    int num = dis(gen) + 1;
    return num;
}

void interpreter::buyImprove(std::shared_ptr<Player> player, std::shared_ptr<AcadBuilding> building, std::shared_ptr<Display> display) {
    std::string name = player->getName();
    if (!isEligible(name, building)) {
        std::cerr << "You cannot buy improvements for the non-monopoly buildings" << std::endl;
        return;
    }
    if (building->getImproveNum() >= 5) {
        std::cerr << "You cannot buy more improvements for this building" << std::endl;
        return;
    }
    if (player->getAsset() < building->getImproveCost()) {
        std::cerr << "You don't have enough money for improvement" << std::endl;
        return;
    }
    player->changeAsset(-(building->getImproveCost()));
    building->improve(1);
    display->updateImp(building->getName(), 1);
}

void interpreter::sellImprove(std::shared_ptr<Player> player, std::shared_ptr<AcadBuilding> building, std::shared_ptr<Display> display) {
    std::string name = player->getName();
    if (building->getOwner() != name) {
        std::cerr << "You cannot sell improvements for the buildings you don't own" << std::endl;
        return;
    }
    if (building->getImproveNum() <= 0) {
        std::cerr << "You cannot sell improvements for the buildings with no improvements" << std::endl;
        return;
    }
    player->changeAsset(building->getImproveCost() / 2);
    building->improve(-1);
    display->updateImp(building->getName(), -1);
    display->notify();
}

void interpreter::mortgage(std::shared_ptr<Player> player, std::string property) {
    if (player->getOwnedAcad().count(property) == 1) {
        if (player->getOwnedAcad()[property]->getImproveNum() > 0) {
            std::cerr << "You cannot mortgage buildings with improvements" << std::endl;
            return;
        } else if (player->getOwnedAcad()[property]->getMortgaged()) {
            std::cerr << "You cannot mortgage one building twice" << std::endl;
            return;
        } else {
            player->changeAsset(player->getOwnedAcad()[property]->getPurchaseCost() / 2);
            player->setAcadMortgaged(property, true);
            return;
        }
    }
    if (player->getOwnedRes().count(property) == 1) {
        if (player->getOwnedRes()[property] == true) {
            std::cerr << "You cannot mortgage one building twice" << std::endl;
            return;
        } else {
            player->changeAsset(100);
            player->setResMortgage(property, true);
            return;
        }
    }
    if (player->getOwnedGym().count(property) == 1) {
        if (player->getOwnedGym()[property] == true) {
            std::cerr << "You cannot mortgage one building twice" << std::endl;
            return;
        } else {
            player->changeAsset(75);
            player->setGymMortgated(property, true);
            return;
        }
    }
    std::cerr << "The building you are trying to mortgage is not yours" << std::endl;
}

void interpreter::umortgage(std::shared_ptr<Player> player, std::string property) {
    if (player->getOwnedAcad().count(property) == 1) {
        if (player->getOwnedAcad()[property]->getMortgaged() == false) {
            std::cerr << "You cannot umortgage the building that haven't been mortgaged" << std::endl;
            return;
        } else if (player->getAsset() < player->getOwnedAcad()[property]->getPurchaseCost() * 0.6) {
            std::cerr << "You donn't have enough money to umortgage this building" << std::endl;
        } else {
            player->changeAsset(-player->getOwnedAcad()[property]->getPurchaseCost() * 0.6);
            player->setAcadMortgaged(property, false);
            return;
        }
    }
    if (player->getOwnedRes().count(property) == 1) {
        if (player->getOwnedRes()[property] == false) {
            std::cerr << "You cannot umortgage the building that haven't been mortgaged" << std::endl;
            return;
        } else if (player->getAsset() < 200 * 0.6) {
            std::cerr << "You donn't have enough money to umortgage this building" << std::endl;
        } else {
            player->changeAsset(-200 * 0.6);
            player->setResMortgage(property, false);
            return;
        }
    }
    if (player->getOwnedGym().count(property) == 1) {
        if (player->getOwnedGym()[property] == false) {
            std::cerr << "You cannot umortgage the building that haven't been mortgaged" << std::endl;
            return;
        } else if (player->getAsset() < 150 * 0.6) {
            std::cerr << "You donn't have enough money to umortgage this building" << std::endl;
        } else {
            player->changeAsset(-150 * 0.6);
            player->setGymMortgated(property, false);
            return;
        }
    }
    std::cerr << "The building you are trying to umortgage is not yours" << std::endl;
}

void interpreter::buyFrom(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::string property, int price) {
    if (player2->getBankrupt()) {
        std::cerr << "You cannot trade with lost players" << std::endl;
        return;
    }
    if (player1->getAsset() < price) {
        std::cerr << "You don't have enough money to offer this trade" << std::endl;
        return;
    }
    if (player2->getOwnedAcad().count(property) == 1) {
        for (int i = 0; i < player2->getOwnedAcad()[property]->getBlock().size(); i++) {
            if (player2->getOwnedAcad()[property]->getBlock()[i]->getImproveNum() != 0) {
                std::cerr << "You cannot offer a trade for a property which its monopoly block includes properties with improvements" << std::endl;
                return;
            }
        }
        std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to buy " << property << " from you with a price of " << price << std::endl;
        if (accept()) {
            auto building = player2->getOwnedAcad()[property];
            building->setOwner(player1->getName());
            player1->addAcad(building);
            player2->deleteAcad(property);
            player1->changeAsset(-price);
            player2->changeAsset(price);
            return;
        }
    } else if (player2->getOwnedRes().count(property) == 1) {
        std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to buy " << property << " from you with a price of " << price << std::endl;
        if (accept()) {
            player1->addRes(property);
            player2->deleteRes(property);
            player1->changeAsset(-price);
            player2->changeAsset(price);
            return;
        }
    } else if (player2->getOwnedGym().count(property) == 1) {
        std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to buy " << property << " from you with a price of " << price << std::endl;
        if (accept()) {
            player1->addGym(property);
            player2->deleteGym(property);
            player1->changeAsset(-price);
            player2->changeAsset(price);
            return;
        }
    } else {
        std::cerr << "Player " << player2->getName() << " doesn't own " << property << std::endl;
        return;
    }
}

void interpreter::sellTo(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::string property, int price) {
    if (player2->getBankrupt()) {
        std::cerr << "You cannot trade with lost players" << std::endl;
        return;
    }
    if (player2->getAsset() < price) {
        std::cerr << "Player " << player2->getName() << " doesn't have enough money to accept this trade" << std::endl;
        return;
    }
    if (player1->getOwnedAcad().count(property) == 1) {
        for (int i = 0; i < player1->getOwnedAcad()[property]->getBlock().size(); i++) {
            if (player1->getOwnedAcad()[property]->getBlock()[i]->getImproveNum() != 0) {
                std::cerr << "You cannot offer a trade for a property which its monopoly block includes properties with improvements" << std::endl;
                return;
            }
        }
        std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to sell " << property << " to you with a price of " << price << std::endl;
        if (accept()) {
            auto building = player1->getOwnedAcad()[property];
            building->setOwner(player2->getName());
            player2->addAcad(building);
            player1->deleteAcad(property);
            player2->changeAsset(-price);
            player1->changeAsset(price);
            return;
        }
    } else if (player1->getOwnedRes().count(property) == 1) {
        std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to sell " << property << " to you with a price of " << price << std::endl;
        if (accept()) {
            player2->addRes(property);
            player1->deleteRes(property);
            player2->changeAsset(-price);
            player1->changeAsset(price);
            return;
        }
    } else if (player1->getOwnedGym().count(property) == 1) {
        std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to sell " << property << " to you with a price of " << price << std::endl;
        if (accept()) {
            player2->addGym(property);
            player1->deleteGym(property);
            player2->changeAsset(-price);
            player1->changeAsset(price);
            return;
        }
    } else {
        std::cerr << "Player " << player1->getName() << " doesn't own " << property << std::endl;
        return;
    }
}

void interpreter::tradeProperty(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::string property1, std::string property2) {
    if (player2->getBankrupt()) {
        std::cerr << "You cannot trade with lost players" << std::endl;
        return;
    }
    if (player1->getOwnedAcad().count(property1) == 1) {
        for (int i = 0; i < player1->getOwnedAcad()[property1]->getBlock().size(); i++) {
            if (player1->getOwnedAcad()[property1]->getBlock()[i]->getImproveNum() != 0) {
                std::cerr << "You cannot offer a trade for a property which its monopoly block includes properties with improvements" << std::endl;
                return;
            }
        }
        if (player2->getOwnedAcad().count(property2) == 1) {
            for (int i = 0; i < player2->getOwnedAcad()[property2]->getBlock().size(); i++) {
                if (player2->getOwnedAcad()[property2]->getBlock()[i]->getImproveNum() != 0) {
                    std::cerr << "You cannot offer a trade for a property which its monopoly block includes properties with improvements" << std::endl;
                    return;
                }
            }
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                auto building1 = player1->getOwnedAcad()[property1];
                auto building2 = player2->getOwnedAcad()[property2];
                building1->setOwner(player2->getName());
                building2->setOwner(player1->getName());
                player1->addAcad(building2);
                player2->addAcad(building1);
                player1->deleteAcad(property1);
                player2->deleteAcad(property2);
                return;
            }
        } else if (player2->getOwnedRes().count(property2) == 1) {
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                auto building1 = player1->getOwnedAcad()[property1];
                building1->setOwner(player2->getName());
                player1->addRes(property2);
                player2->addAcad(building1);
                player1->deleteAcad(property1);
                player2->deleteRes(property2);
                return;
            }
        } else if (player2->getOwnedGym().count(property2) == 1) {
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                auto building1 = player1->getOwnedAcad()[property1];
                building1->setOwner(player2->getName());
                player1->addGym(property2);
                player2->addAcad(building1);
                player1->deleteAcad(property1);
                player2->deleteGym(property2);
                return;
            }
        } else {
            std::cerr << "Player " << player2->getName() << " doesn't own " << property2 << std::endl;
            return;
        }
    } else if (player1->getOwnedRes().count(property1) == 1) {
        if (player2->getOwnedAcad().count(property2) == 1) {
            for (int i = 0; i < player2->getOwnedAcad()[property2]->getBlock().size(); i++) {
                if (player2->getOwnedAcad()[property2]->getBlock()[i]->getImproveNum() != 0) {
                    std::cerr << "You cannot offer a trade for a property which its monopoly block includes properties with improvements" << std::endl;
                    return;
                }
            }
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                auto building2 = player2->getOwnedAcad()[property2];
                building2->setOwner(player1->getName());
                player1->addAcad(building2);
                player2->addRes(property1);
                player1->deleteRes(property1);
                player2->deleteAcad(property2);
                return;
            }
        } else if (player2->getOwnedRes().count(property2) == 1) {
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                player1->addRes(property2);
                player2->addRes(property1);
                player1->deleteRes(property1);
                player2->deleteRes(property2);
                return;
            }
        } else if (player2->getOwnedGym().count(property2) == 1) {
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                player1->addGym(property2);
                player2->addRes(property1);
                player1->deleteRes(property1);
                player2->deleteGym(property2);
                return;
            }
        } else {
            std::cerr << "Player " << player2->getName() << " doesn't own " << property2 << std::endl;
            return;
        }
    } else if (player1->getOwnedRes().count(property1) == 1) {
        if (player2->getOwnedAcad().count(property2) == 1) {
            for (int i = 0; i < player2->getOwnedAcad()[property2]->getBlock().size(); i++) {
                if (player2->getOwnedAcad()[property2]->getBlock()[i]->getImproveNum() != 0) {
                    std::cerr << "You cannot offer a trade for a property which its monopoly block includes properties with improvements" << std::endl;
                    return;
                }
            }
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                auto building2 = player2->getOwnedAcad()[property2];
                building2->setOwner(player1->getName());
                player1->addAcad(building2);
                player2->addGym(property1);
                player1->deleteGym(property1);
                player2->deleteAcad(property2);
                return;
            }
        } else if (player2->getOwnedRes().count(property2) == 1) {
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                player1->addRes(property2);
                player2->addGym(property1);
                player1->deleteGym(property1);
                player2->deleteRes(property2);
                return;
            }
        } else if (player2->getOwnedGym().count(property2) == 1) {
            std::cout << "Player " << player2->getName() << ", Player " << player1->getName() << " is trying to give " << property1 << " to you to exchange " << property2 << std::endl;
            if (accept()) {
                player1->addGym(property2);
                player2->addGym(property1);
                player1->deleteGym(property1);
                player2->deleteGym(property2);
                return;
            }
        } else {
            std::cerr << "Player " << player2->getName() << " doesn't own " << property2 << std::endl;
            return;
        }
    } else {
        std::cerr << "Player " << player1->getName() << " doesn't own " << property1 << std::endl;
        return;
    }
}

void interpreter::all(std::shared_ptr<Grid> grid) {
    for (auto i : grid->getPlayers()) {
        if (!i.second->getBankrupt()) {
            std::cout << std::endl;
            assets(i.second);
        }
    }
}

void interpreter::assets(std::shared_ptr<Player> player) {
    std::cout << "Player " << player->getName() << " :" << std::endl;
    std::cout << std::endl;
    std::cout << "Saving: " << player->getAsset() << std::endl;
    std::cout << std::endl;
    std::cout << "Roll Up the Rim Cup: " << player->getCup() << std::endl;
    std::cout << std::endl;
    std::cout << "Own Academic buildings: " << std::endl;
    for (auto i : player->getOwnedAcad()) {
        if (i.second->getMortgaged()) {
            std::cout << i.first << ": mortgaged" << std::endl;
        } else {
            std::cout << i.first << " with " << i.second->getImproveNum() << " improvements" << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Own residences: " << std::endl;
    for (auto i : player->getOwnedRes()) {
        std::cout << i.first;
        if (i.second) {
            std::cout << " mortgaged";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Own gyms: " << std::endl;
    for (auto i : player->getOwnedGym()) {
        std::cout << i.first;
        if (i.second) {
            std::cout << " mortgaged";
        }
        std::cout << std::endl;
    }
}

void interpreter::saveNotAcad(std::shared_ptr<Grid> grid, std::shared_ptr<std::ofstream> file, string property) {
    bool found = false;
    for (auto i : grid->getPlayers()) {
        if (i.second->getOwnedRes().count(property) != 0) {
            if (i.second->getOwnedRes()[property] == false) {
                *file << property << " " << i.second->getName() << " 0" << std::endl;
            } else {
                *file << property << " " << i.second->getName() << " -1" << std::endl;
            }
            found = true;
            break;
        }
        if (i.second->getOwnedGym().count(property) != 0) {
            if (i.second->getOwnedGym()[property] == false) {
                *file << property << " " << i.second->getName() << " 0" << std::endl;
            } else {
                *file << property << " " << i.second->getName() << " -1" << std::endl;
            }
            found = true;
            break;
        }
    }
    if (!found) {
        *file << property << " BANK 0" << std::endl;
    }
}

void interpreter::save(std::shared_ptr<Grid> grid, std::shared_ptr<std::ofstream> file, std::shared_ptr<Display> display) {
    auto players = grid->getPlayers();
    int alive = std::count_if(players.begin(), players.end(), [](std::pair<string, std::shared_ptr<Player>> n) { return !n.second->getBankrupt(); });
    *file << alive << std::endl;
    int count = 1;
    for (auto i : grid->getPlayers()) {
        if (!i.second->getBankrupt()) {
            if (i.second->getNewPos() != display->getPosition("DC Tims Line")) {
                *file << "player" << count << " " << i.second->getName() << " " << i.second->getCup() << " " << i.second->getAsset() << " " << i.second->getNewPos() << std::endl;
            } else {
                if (i.second->getGoTims()) {
                    *file << "player" << count << " " << i.second->getName() << " " << i.second->getCup() << " " << i.second->getAsset() << " " << i.second->getNewPos() << " 1 " << i.second->getTurnsInTims() << std::endl;
                } else {
                    *file << "player" << count << " " << i.second->getName() << " " << i.second->getCup() << " " << i.second->getAsset() << " " << i.second->getNewPos() << " 0" << std::endl;
                }
            }
            count += 1;
        }
    }
    for (auto i : grid->getAcadBuildings()) {
        if (i.second->getOwner() != "") {
            if (!i.second->getMortgaged()) {
                *file << i.first << " " << i.second->getOwner() << " " << i.second->getImproveNum() << std::endl;
            } else {
                *file << i.first << " " << i.second->getOwner() << " -1" << std::endl;
            }
        } else {
            *file << i.first << " BANK " << i.second->getImproveNum() << std::endl;
        }
    }
    saveNotAcad(grid, file, "MKV");
    saveNotAcad(grid, file, "UWP");
    saveNotAcad(grid, file, "V1");
    saveNotAcad(grid, file, "REV");
    saveNotAcad(grid, file, "PAC");
    saveNotAcad(grid, file, "CIF");
}
void interpreter::loadGame(std::shared_ptr<Grid> grid, std::shared_ptr<std::ifstream> file, std::shared_ptr<Display> display) {
    int players = 0;
    int pos = 0;
    int cup = 0;
    string name = "";
    int money = 0;
    string line;
    bool isInTims = false;
    int turnsInTims = 0;
    *file >> players;
    for (int i = 0; i < players; i++) {
        *file >> name;
        *file >> name;
        *file >> cup;
        *file >> money;
        *file >> pos;
        if (pos == display->getPosition("DC Tims Line")) {
            *file >> turnsInTims;
            if (turnsInTims == 1) {
                isInTims = true;
                *file >> turnsInTims;
            }
        }
        grid->addPlayer(std::make_shared<Player>(name, isInTims, pos, pos, money, cup, turnsInTims));
        display->updatePlayer(name[0], -1, pos);
        isInTims = false;
    }
    string owner;
    int improve;
    auto buildings = grid->getAcadBuildings();
    auto player = grid->getPlayers();
    for (int i = 0; i < 22; i++) {
        *file >> name;
        *file >> owner;
        *file >> improve;
        if (improve == -1) {
            if (owner != "BANK") {
                buildings[name]->setOwner(owner);
                player[owner]->addAcad(buildings[name]);
            }
            buildings[name]->setMortgaged(true);
        } else {
            if (owner != "BANK") {
                buildings[name]->setOwner(owner);
                player[owner]->addAcad(buildings[name]);
            }
            buildings[name]->improve(improve);
            display->updateImp(name, improve);
        }
    }
    auto playerMap = grid->getPlayers();
    for (int i = 0; i < 4; i++) {
        *file >> name;
        *file >> owner;
        *file >> improve;
        if (owner != "BANK") {
            playerMap[owner]->addRes(name);
            if (improve == -1) {
                playerMap[owner]->setResMortgage(name, true);
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        *file >> name;
        *file >> owner;
        *file >> improve;
        if (owner != "BANK") {
            playerMap[owner]->addGym(name);
            if (improve == -1) {
                playerMap[owner]->setGymMortgated(name, true);
            }
        }
    }
}
