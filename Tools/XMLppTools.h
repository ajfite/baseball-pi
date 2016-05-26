//
// Created by aj on 5/17/16.
//

#ifndef BASEBALL_PI_XMLPPTOOLS_H
#define BASEBALL_PI_XMLPPTOOLS_H


#include "../DataStructures/Game.h"
#include "../DataStructures/XMLMemoryUnit.h"

//TODO: Rewrite of this class would be good
class XMLppTools {
public:
    static void populateGameFromScoreboardXML(Game * gameToPopulate, XMLMemoryUnit * scoreboardXMLMemory, Glib::ustring teamIDToFind);
    static void populateScoreboardXML(Game * gameObj, XMLMemoryUnit * xmlMem);
};


#endif //BASEBALL_PI_XMLPPTOOLS_H
