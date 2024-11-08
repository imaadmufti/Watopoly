#include "display.h"

int Display::getPosition(string building) {
    int count = 0;
    for (auto s : squares) {
        if (s->getName() == building) break;
        ++count;
    }
    return getSquareNum(count); // converts square number to position, which is returned
}

int Display::getSquareNum(int position) {
    if (position < 20) return position + 20;
    return position - 20;
}

void Display::addSquare(std::shared_ptr<Square> square) {
    squares.push_back(square);
}

void Display::updatePlayer(char player, int oldPos, int newPos) {
    if (oldPos != -1) squares[getSquareNum(oldPos)]->removePlayer(player);
    if (newPos != -1) squares[getSquareNum(newPos)]->addPlayer(player);
}

void Display::updateImp(string building, int impNum) {
    squares[getSquareNum(getPosition(building))]->changeImprovements(impNum);
}

string Display::getName(int position) {
    return squares[getSquareNum(position)]->getName();
}

void Display::rearrange() {
    int first = rand() % 40 + 0;
    int second = rand() % 40 + 0;
    std::shared_ptr<Square> temp;
    for (int i = 0; i < 39; ++i) {
        while (first == 20) first = rand() % 40 + 0;
        while (second == 20) second = rand() % 40 + 0;
        temp = squares[second];
        squares[second] = squares[first];
        squares[first] = temp;
        first = 20;
        second = 20;
    }
}


void Display::notify() {
    const string WATOPOLY[5][6] = {
        {"      | #", "   #  ## ", " #####  #", "##  ###  ", " ###  #  ", "  #   # |"},
        {"      | #", "   # #  #", "   #   # ", "  # #  # ", "#   # #  ", "  #   # |"},
        {"      | #", " # # ####", "   #   # ", "  # ###  ", "#   # #  ", "   # #  |"},
        {"      | #", " # # #  #", "   #   # ", "  # #    ", "#   # #  ", "    #   |"},
        {"      | #", "#### #  #", "   #    #", "##  #    ", " ###  ###", "#   #   |"}
    };
    
    // top border
    for (int i = 0; i < 11; ++i) {
        cout << "_________";
    }
    cout << "_" << endl;
    // ROW
    for (int row = 0; row < 11; ++row) {
        // LINE
        for (int line = 0; line < 5; ++line) {
            cout << "|";
            // COLUMN
            for (int col = 0; col < 11; ++col) {
                if (1 <= row && row <= 9 && 1 <= col && col <= 9) {  // within squares
                    if (row == 9 && line == 4) {                     // top border of bottom row
                        if (col == 9) {
                            cout << "________|";
                        } else {
                            cout << "_________";
                        }
                    } else {  // common white space
                        if (row == 5 && 0 <= line && line <= 4 && 2 <= col && col <= 7) {
                            cout << WATOPOLY[line][col-2];
                        } else if (row == 4 && line == 3 && 2 <= col && col <= 7) {
                            cout << (col == 2 ? "       _" : "_________");
                            if (row == 4 && line == 3 && col == 7) cout << " ";
                        } else if (row == 6 && line == 0 && 2 <= col && col <= 7) {
                            if (col == 2) cout << "      |__";
                            else if (col == 7) cout << "________|";
                            else cout << "_________";
                        } else if (row == 4 && line == 4 && col == 2) {
                            cout << "      |  ";
                        } else if (row == 4 && line == 4 && col == 7) {
                            cout << "        |";
                            
                            } else if (col == 9) {
                                cout << "        |";
                            } else {
                                cout << "         ";
                            }
                        }
                // } else if (row == 0 || row == 10) {
                } else {
                    int curr = 0;
                    if (row == 0 || row == 10) {
                        curr = (row * 3 - 2 * (row / 10 * col) + col);
                    } else {
                        curr = ((40 - (3 * col)) + 2 * (col / 10 * row) - row);
                    }
                    switch (line) {
                        case 0:
                            if (squares[curr]->getAcad()) {
                                squares[curr]->printImprovements();
                            } else {
                                squares[curr]->printNameTop();
                            }
                            break;
                        case 1:
                            if (squares[curr]->getAcad()) {
                                cout << "--------";
                            } else {
                                squares[curr]->printNameBottom();
                            }
                            break;
                        case 2:
                            if (squares[curr]->getAcad()) {
                                squares[curr]->printNameTop();
                            } else {
                                cout << "        ";
                            }
                            break;
                        case 3:
                            squares[curr]->printPlayers();
                            break;
                        case 4:
                            cout << "________";
                            break;
                    }
                    cout << "|";
                }
            }  // END OF COLUMN
            cout << endl;
        }  // END OF LINE
    }      // END OF ROW
}