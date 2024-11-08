#include <sstream>

#include "grid.h"
#include "interpreter.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {
    bool test = false;
    bool loaded = false;
    std::shared_ptr<std::ifstream> file;
    auto mygrid = std::make_shared<Grid>();
    auto display = std::make_shared<Display>();
    interpreter inter;
    inter.createSquares(display);
    for (int i = 0; argv[i] != nullptr; i++) {
        string arg = argv[i];
        if (arg == "-testing") {
            test = true;
        }
        if (arg == "-load") {
            file = std::make_shared<std::ifstream>(argv[i + 1]);
            inter.loadGame(mygrid, file, display);
            loaded = true;
        }
    }
    if (loaded == false) {
        inter.startGame(mygrid, display);  // function startGame interact with the user and initialize the grid by the input of the players
    }
    while (inter.endGame(mygrid) == false) {
        auto maps = mygrid->getPlayers();
        auto i = maps.begin();
        while (i != maps.end()) {
            if (i->second->getBankrupt()) {
                i++;
                if (i == mygrid->getPlayers().end()) {
                    break;
                }
            }
            if (inter.endGame(mygrid)) {
                break;
            }
            std::string command = "";
            bool rolled = false;
            int rolltimes = 0;
            while (true) {
                cout << "Player " << i->second->getName() << " , it is your turn." << endl;
                cout << "You can choose from the following commands:" << endl;
                cout << "roll" << endl;
                cout << "next" << endl;
                cout << "trade <name> <give> <receive>" << endl;
                cout << "improve <property> buy/sell" << endl;
                cout << "mortgage <property>" << endl;
                cout << "unmortgage <property>" << endl;
                cout << "assets" << endl;
                cout << "all" << endl;
                cout << "save <Filename>" << endl;
                getline(cin, command);
                if (cin.eof()) {
                    return 0;
                }
                int die1 = 0;
                int die2 = 0;
                char name = i->second->getName()[0];
                int jailNumber = 0;
                int pos = 0;
                std::string squareName;
                Grid& ref = *mygrid;
                std::istringstream str(command);
                std::string word;
                str >> word;
                if (word == "roll") {
                    if (rolled == true) {
                        cerr << "You have already rolled, give the control to the next player" << endl;
                        i++;
                        break;
                    }
                    if (i->second->getGoTims()) {
                        cout << "You cannot move until you get out of the Tims Line" << endl;
                        jailNumber = mygrid->timsLine(i->second, display);
                        if (i->second->getBankrupt()) {
                            cout << "You lose the game, player " << name << endl;
                            i++;
                            display->updatePlayer(name, display->getPosition("DC Tims Line"), -1);
                            display->notify();
                            break;
                        } else if (jailNumber > 0) {
                            cout << "You finally get out Tims Line, but you cannot roll and you can only move by the dice you rolled in Tims" << endl;
                            i->second->setPos(jailNumber);
                            pos = i->second->getNewPos();
                            display->updatePlayer(name, i->second->getCurrPos(), i->second->getNewPos());
                            display->notify();
                            squareName = display->getName(pos);
                            inter.use(ref, display, squareName, i->second);
                            rolled = true;
                            rolltimes = 0;
                            if (i->second->getBankrupt()) {
                                cout << "You lose the game, player " << name << endl;
                                i++;
                                display->updatePlayer(name, pos, -1);
                                display->notify();
                                break;
                            }
                        } else {  // jailNumber == 0
                            if (i->second->getGoTims()) {
                                cout << "You didn't get out of Tims. So no moves this round" << endl;
                                rolled = true;
                                rolltimes = 0;
                            } else {
                                cout << "You are out of Tims Line. You can roll now" << endl;
                                if (test) {  // same rolling process.
                                    if (!(str >> die1 && str >> die2)) {
                                        die1 = inter.roll();
                                        die2 = inter.roll();
                                    }
                                } else {
                                    die1 = inter.roll();
                                    die2 = inter.roll();
                                }
                                cout << "You rolled " << die1 + die2 << endl;
                                i->second->setPos(die1 + die2);
                                pos = i->second->getNewPos();
                                squareName = display->getName(pos);
                                display->updatePlayer(name, i->second->getCurrPos(), i->second->getNewPos());
                                display->notify();
                                inter.use(ref, display, squareName, i->second);
                                if (i->second->getBankrupt()) {
                                    cout << "You lose the game, player " << name << endl;
                                    i++;
                                    display->updatePlayer(name, pos, -1);
                                    display->notify();
                                    break;
                                }
                                if (die1 == die2) {
                                    rolltimes += 1;
                                    cout << "You rolled double. You can roll again" << endl;
                                } else {
                                    rolltimes = 0;
                                    rolled = true;
                                }
                            }
                        }
                    } else {
                        if (test) {
                            if (!(str >> die1 && str >> die2)) {
                                die1 = inter.roll();
                                die2 = inter.roll();
                            }
                        } else {
                            die1 = inter.roll();
                            die2 = inter.roll();
                        }
                        cout << "You rolled " << die1 + die2 << endl;
                        i->second->setPos(die1 + die2);
                        pos = i->second->getNewPos();
                        squareName = display->getName(pos);
                        display->updatePlayer(name, i->second->getCurrPos(), i->second->getNewPos());
                        display->notify();
                        inter.use(ref, display, squareName, i->second);
                        if (i->second->getBankrupt()) {
                            cout << "You lose the game, player " << name << endl;
                            i++;
                            display->updatePlayer(name, pos, -1);
                            display->notify();
                            break;
                        }
                        if (die1 == die2) {
                            rolltimes += 1;
                            cout << "You rolled double. You can roll again" << endl;
                        } else {
                            rolltimes = 0;
                            rolled = true;
                        }
                    }
                    if (rolltimes >= 3) {
                        cout << "You coded too much. Go to Tims to get a coffee" << endl;
                        mygrid->goToTims(i->second, display);
                        rolltimes = 0;
                        rolled = true;
                    }
                } else if (word == "next") {
                    if (rolled == false) {
                        cerr << "You cannot give control to other players before rolling" << endl;
                    } else {
                        i++;
                        display->notify();
                        break;
                    }
                } else if (word == "trade") {
                    std::string player2;
                    std::string give;
                    std::string receive;
                    str >> player2;
                    str >> give;
                    str >> receive;
                    if (mygrid->getPlayers().count(player2) == 0) {
                        cerr << "Player " << player2 << " doesn't exist" << endl;
                    } else if (i->second->getName() == player2) {
                        cerr << "You cannot trade with yourself" << endl;
                    } else {
                        if (inter.isInt(give)) {
                            if (inter.isInt(receive)) {
                                cerr << "Cannot trade money with money" << endl;
                            } else {
                                inter.buyFrom(i->second, mygrid->getPlayers()[player2], receive, std::stoi(give));
                            }
                        } else {
                            if (inter.isInt(receive)) {
                                inter.sellTo(i->second, mygrid->getPlayers()[player2],give, std::stoi(receive));
                            } else {
                                inter.tradeProperty(i->second, mygrid->getPlayers()[player2], give, receive);
                            }
                        }
                    }
                    display->notify();
                } else if (word == "improve") {
                    std::string action;
                    std::string property;
                    str >> property;
                    str >> action;
                    if (mygrid->getAcadBuildings().count(property) == 0) {
                        cerr << "This building does not exist" << endl;
                    } else {
                        if (action == "buy") {
                            inter.buyImprove(i->second, mygrid->getAcadBuildings()[property], display);
                        } else if (action == "sell") {
                            inter.sellImprove(i->second, mygrid->getAcadBuildings()[property], display);
                        } else {
                            cerr << "Wrong command: only buy and sell on improve" << endl;
                        }
                    }
                    display->notify();
                } else if (word == "mortgage") {
                    std::string mortgage;
                    str >> mortgage;
                    inter.mortgage(i->second, mortgage);
                    display->notify();
                } else if (word == "unmortgage") {
                    std::string unmortgage;
                    str >> unmortgage;
                    inter.umortgage(i->second, unmortgage);
                    display->notify();
                } else if (word == "assets") {
                    inter.assets(i->second);
                    display->notify();
                } else if (word == "all") {
                    inter.all(mygrid);
                    display->notify();
                } else if (word == "save") {
                    std::string file;
                    str >> file;
                    auto outfile = std::make_shared<std::ofstream>(file);
                    inter.save(mygrid, outfile, display);
                    display->notify();
                }
            }
        }
    }
    std::string lastPlayer;
    for (auto i : mygrid->getPlayers()) {
        if (i.second->getBankrupt() == false) {
            lastPlayer = i.second->getName();
            break;
        }
    }
    cout << "Congraduations! Player " << lastPlayer << " wins!" << endl;
}
