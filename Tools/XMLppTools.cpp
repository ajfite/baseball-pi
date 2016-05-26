//
// Created by aj on 5/17/16.
//

#include <libxml++/libxml++.h>
#include <iostream>
#include "XMLppTools.h"

using namespace Glib;
using namespace std;

//TODO: Handle error conditions
void XMLppTools::populateGameFromScoreboardXML(Game * gameToPopulate, XMLMemoryUnit * scoreboardXMLMemory, Glib::ustring teamIDToFind) {
    //Proof of concept XML parser
    try {
        xmlpp::DomParser parser;
        parser.parse_memory(*(scoreboardXMLMemory->memory));

        if(parser) {
            xmlpp::Node *root;
            root  = parser.get_document()->get_root_node();

            xmlpp::NodeSet titles;
            titles = root->find("//game");

            for(xmlpp::NodeSet::iterator i = titles.begin(); i != titles.end(); i++) {
                xmlpp::Element *enode;
                enode = dynamic_cast<xmlpp::Element *>(*i);

                if(enode){
                    ustring id = enode->get_attribute("id")->get_value();

                    if(id.find(teamIDToFind) != ustring::npos) {
                        gameToPopulate->gameID = id;
                    }
                }
            }
        }
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}

void XMLppTools::populateScoreboardXML(Game *gameObj, XMLMemoryUnit *xmlMem) {
    try {
        xmlpp::DomParser parser;
        parser.parse_memory(*(xmlMem->memory));

        if(parser) {
            xmlpp::Node * root;
            root  = parser.get_document()->get_root_node();

            xmlpp::Element * rootElem;
            rootElem = dynamic_cast<xmlpp::Element *>(root);

            gameObj->away->code = rootElem->get_attribute("away_team_code")->get_value();
            gameObj->home->code = rootElem->get_attribute("home_team_code")->get_value();

            //Parse linescore
            xmlpp::NodeSet titles;
            titles = root->find("//linescore");

            for(xmlpp::NodeSet::iterator i = titles.begin(); i != titles.end(); i++) {
                xmlpp::Element *enode;
                enode = dynamic_cast<xmlpp::Element *>(*i);

            }
        }
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}





