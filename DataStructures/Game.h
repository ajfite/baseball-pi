//
// Created by aj on 5/16/16.
//

#ifndef BASEBALL_PI_GAME_H
#define BASEBALL_PI_GAME_H


#include <glibmm/ustring.h>
#include "Team.h"

/**
 * Object representing a game
 */
class Game {
public:
    Glib::ustring gameID;
    Team home;
    Team away;
};


#endif //BASEBALL_PI_GAME_H
