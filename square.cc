#include "square.h"

Square::Square(string name, bool isAcad) : name{name}, isAcad{isAcad}, improvements{0} {}

string Square::getName() {
    return name;
}

string Square::getNameTop() {
    std::istringstream ss(name);
    string top;
    ss >> top;
    string word = "";
    while (ss) {
        ss >> word;
        if ((top.length() + word.length() + 1) > 8) break;
        top += (" " + word);
    }
    return top;
}

void Square::printNameTop() {
    string top = this->getNameTop();
    if (top.length() < 8) {
        int empty = 8 - top.length();
        for (int i = 0; i < empty; ++i) {
            top += " ";
        }
    }
    std::cout << top;
}

void Square::printNameBottom() {
    string top = this->getNameTop();
    string bottom = "        ";
    if (name.length() > 8) bottom = name.substr(top.length() + 1);
    if (bottom.length() < 8) {
        int empty = 8 - bottom.length();
        for (int i = 0; i < empty; ++i) {
            bottom += " ";
        }
    }
    std::cout << bottom;
}

std::vector<char> Square::getPlayers() {
    return players;
}

void Square::printPlayers() {
    string output = "";
    for (auto p : players) {
        output += p;
    }
    if (output.length() < 8) {
        int empty = 8 - output.length();
        for (int i = 0; i < empty; ++i) {
            output += " ";
        }
    }
    std::cout << output;
}

void Square::addPlayer(char player) {
    players.push_back(player);
}

void Square::removePlayer(char player) {
    auto iterator = std::find(players.begin(), players.end(), player);
    players.erase(iterator);
}

bool Square::getAcad() {
    return isAcad;
}

int Square::getImprovements() {
    return improvements;
}

void Square::changeImprovements(int n) {
    improvements += n;
}

void Square::printImprovements() {
    string output = "";
    for (int i = 0; i < improvements; ++i) {
        output += "I";
    }
    int empty = 8 - output.length();
    for (int i = 0; i < empty; ++i) {
        output += " ";
    }
    std::cout << output;
}
