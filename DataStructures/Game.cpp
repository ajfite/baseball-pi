//
// Created by aj on 5/16/16.
//

#include "Game.h"

Game::Game(Glib::ustring id) : Game() {
    gameID = id;
}

Game::Game() {
    home = new Team();
    away = new Team();
}



