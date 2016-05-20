//
// Created by aj on 5/17/16.
//

#ifndef BASEBALL_PI_XMLPPTOOLS_H
#define BASEBALL_PI_XMLPPTOOLS_H


#include "../DataStructures/Game.h"
#include "../DataStructures/XMLMemoryUnit.h"

class XMLppTools {
public:
    static void populateGameFromScoreboardXML(Glib::ustring url, Game * gameToPopulate, XMLMemoryUnit * scoreboardXMLMemory, Glib::ustring teamIDToFind);
};


#endif //BASEBALL_PI_XMLPPTOOLS_H
