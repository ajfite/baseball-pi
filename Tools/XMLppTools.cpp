//
// Created by aj on 5/17/16.
//

#include <libxml++/libxml++.h>
#include <iostream>
#include "XMLppTools.h"

using namespace Glib;
using namespace xmlpp;
using namespace std;

//TODO: Handle error conditions
void XMLppTools::populateGameFromScoreboardXML(Game * gameToPopulate, XMLMemoryUnit * scoreboardXMLMemory, Glib::ustring teamIDToFind) {
    //Proof of concept XML parser
    try {
        DomParser parser;
        parser.parse_memory(*(scoreboardXMLMemory->memory));

        if(parser) {
            Node *root;
            root  = parser.get_document()->get_root_node();

            NodeSet titles;
            titles = root->find("//game");

            for(NodeSet::iterator i = titles.begin(); i != titles.end(); i++) {
                Element *enode;
                enode = dynamic_cast<Element *>(*i);

                if(enode){
                    ustring id = enode->get_attribute("id")->get_value();

                    if(id.find(teamIDToFind) != ustring::npos) {
                        gameToPopulate->gameID = id;
                        gameToPopulate->exists = true;
                    }
                }
            }
        }
    } catch (std::exception &e) {
        cout << e.what() << endl;
    }
}

void XMLppTools::populateScoreboardXML(Game *gameObj, XMLMemoryUnit *xmlMem) {
    try {
        DomParser parser;
        parser.parse_memory(*(xmlMem->memory));

        if(parser) {
            Node * root;
            root  = parser.get_document()->get_root_node();

            Element * rootElem;
            rootElem = dynamic_cast<Element *>(root);

            gameObj->away->code = rootElem->get_attribute("away_team_code")->get_value();
            gameObj->home->code = rootElem->get_attribute("home_team_code")->get_value();

            //Parse linescore
            Node * linescore;
            linescore = root->get_first_child("linescore");

            Element * linescoreElem;
            linescoreElem = dynamic_cast<Element *>(linescore);

            //Retrieve base score
            gameObj->awayRun = atoi(linescoreElem->get_attribute("away_team_runs")->get_value().c_str());
            gameObj->awayHit = atoi(linescoreElem->get_attribute("away_team_hits")->get_value().c_str());
            gameObj->awayErr = atoi(linescoreElem->get_attribute("away_team_errors")->get_value().c_str());
            gameObj->homeRun = atoi(linescoreElem->get_attribute("home_team_runs")->get_value().c_str());
            gameObj->homeHit = atoi(linescoreElem->get_attribute("home_team_hits")->get_value().c_str());
            gameObj->homeErr = atoi(linescoreElem->get_attribute("home_team_errors")->get_value().c_str());

            //Retrieve inning scores
            NodeSet innings;
            innings = linescore->find("//inning_line_score");

            for(NodeSet::iterator i = innings.begin(); i != innings.end(); i++) {
                Element * inningElem;
                inningElem = dynamic_cast<Element *>(*i);

                unsigned int inningNum = (unsigned)atoi(inningElem->get_attribute("inning")->get_value().c_str());
                int awayInningRuns = atoi(inningElem->get_attribute("away")->get_value().c_str());
                int homeInningRuns = atoi(inningElem->get_attribute("home")->get_value().c_str());

                //Fixme: Check reserve to make sure this isn't hammering memory
                if(gameObj->awayScore->size() < inningNum) {
                    gameObj->awayScore->resize(inningNum);
                }

                gameObj->awayScore->at(inningNum-1) = awayInningRuns;

                if(gameObj->homeScore->size() < inningNum) {
                    gameObj->homeScore->resize(inningNum);
                }

                gameObj->homeScore->at(inningNum-1) = homeInningRuns;
            }
        }
    } catch (std::exception &e) {
        cout << e.what() << endl;
    }
}





