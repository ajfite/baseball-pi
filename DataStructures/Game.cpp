//
// Created by aj on 5/16/16.
//

#include "Game.h"
#include "../Hardware/HD44780CharacterMap.h"

using namespace std;

Game::Game(Glib::ustring id) : Game() {
    gameID = id;
}

Game::Game() {
    home = new Team();
    away = new Team();

    awayScore = new vector<int>();
    awayScore->reserve(20);

    homeScore = new vector<int>();
    homeScore->reserve(20);
}

std::string Game::scoreToStr(std::vector<int> *score, bool noLast) {
    string str;

    for(std::vector<int>::iterator i = score->begin(); i < score->end(); i++) {
        if(noLast && i == score->end() - 1) {
            str.append("X");
        } else {
            //FIXME: Hack for greater than 9, need to program in some chars to handle this
            if((*i) > 9) {
                str += (char)HD44780CharacterMap::CIRCLE;
            } else {
                str.append(to_string(*i));
            }
        }
    }

    return str;
}





