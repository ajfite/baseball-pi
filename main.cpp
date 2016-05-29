#include <chrono>
#include <thread>
#include <iostream>
#include <csignal>
#include "DataStructures/XMLMemoryUnit.h"
#include "Tools/CURLTools.h"
#include "DataStructures/Game.h"
#include "Tools/XMLppTools.h"
#include "Hardware/CharacterDisplayHD44780.h"
#include "DataStructures/MLBDate.h"
#include "Hardware/HD44780CharacterMap.h"

using namespace std;
using namespace Glib;

bool quitGracefully = false;

//Handle CTRL+C interrupt
//TODO: Develop signal handling more
void happyQuit(int signal) {
    quitGracefully = true;
}

int main() {
    std::locale::global(std::locale("")); //Required by ustring
    struct sigaction interruptHandler;
    interruptHandler.sa_handler = happyQuit;

    sigemptyset(&interruptHandler.sa_mask);
    interruptHandler.sa_flags = 0;

    sigaction(SIGINT, &interruptHandler, NULL);

    XMLMemoryUnit scoreboardToday;
    Game * seaVS = new Game();
    MLBDate * today = new MLBDate(5,25,2016);
    CharacterDisplayHD44780 * disp = new CharacterDisplayHD44780();

    const ustring urlScoreboard = "http://gd2.mlb.com/components/game/mlb" + today->MLBDateString() + "scoreboard.xml";
    const ustring team = "sea"; //TODO: Enum of the possible IDs

    CURLTools::RetrieveXMLFile(urlScoreboard, &scoreboardToday); //Pull XML from MLB API

    XMLppTools::populateGameFromScoreboardXML(seaVS, &scoreboardToday, team); //Take XML and populate the Game Object
    //TODO: Need to handle double headers, this only handles the first game (lowish priority at the moment)

    //Grab game score
    //GDB finds an erroneous "statement always true" here, suppressing warning for now

    if(seaVS->exists) {
        cout << "Game found" << endl;
        const ustring gameScoreboard = "http://gd2.mlb.com/components/game/mlb" + today->MLBDateString() + "gid_" + seaVS->gameID + "/boxscore.xml";

        for(int i = 0; i < 480; i++) { //Runs for a maximum of 4 hours for now
            cout << "Polling for score (attempt " << i << ")" << endl;

            XMLMemoryUnit gameboard;

            CURLTools::RetrieveXMLFile(gameScoreboard, &gameboard);

            XMLppTools::populateScoreboardXML(seaVS, &gameboard);

            bool LastDisp = false;
            if(seaVS->homeRun > seaVS->awayRun && *(seaVS->homeScore->end()) == 0) {
                LastDisp = true;
            }

            char buffer[disp->MAX_LINES][disp->MAX_CHAR_WIDTH];
            snprintf(buffer[0], disp->MAX_CHAR_WIDTH, "    123456789  R H E");
            snprintf(buffer[1], disp->MAX_CHAR_WIDTH, "%3s %9s %2i%2i%2i", seaVS->away->code.uppercase().c_str(), Game::scoreToStr(seaVS->awayScore, false).c_str(), seaVS->awayRun, seaVS->awayHit, seaVS->awayErr);
            snprintf(buffer[2], disp->MAX_CHAR_WIDTH, "%3s %9s %2i%2i%2i", seaVS->home->code.uppercase().c_str(), Game::scoreToStr(seaVS->homeScore, LastDisp).c_str(), seaVS->homeRun, seaVS->homeHit, seaVS->homeErr);
            snprintf(buffer[3], disp->MAX_CHAR_WIDTH, "%c2016 AJ Fite", HD44780CharacterMap::COPYRIGHT);

            cout << buffer[0] << endl;
            cout << buffer[1] << endl;
            cout << buffer[2] << endl;
            cout << buffer[3] << endl;

            disp->SendMessage(buffer[0], disp->LINE0);
            disp->SendMessage(buffer[1], disp->LINE1);
            disp->SendMessage(buffer[2], disp->LINE2);
            disp->SendMessage(buffer[3], disp->LINE3);

            if(quitGracefully) {
                break;
            }

            this_thread::sleep_for(chrono::seconds(30)); //Poll every 30 seconds
        }
    } else {
        cout << "Game not found, Mariners may not play today!" << endl;
        disp->SendMessage("No game today!",disp->LINE0);
    }

    delete(disp); //Make sure the screen is safely reset

    return EXIT_SUCCESS;
}