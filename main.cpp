#include <chrono>
#include <thread>
#include <iostream>
#include "DataStructures/XMLMemoryUnit.h"
#include "Tools/CURLTools.h"
#include "DataStructures/Game.h"
#include "Tools/XMLppTools.h"
#include "Hardware/CharacterDisplayHD44780.h"
#include "DataStructures/MLBDate.h"

using namespace std;
using namespace Glib;

int main() {
    std::locale::global(std::locale("")); //Required by ustring

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
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    if(seaVS != NULL) {
        cout << "Game found" << endl;
        const ustring gameScoreboard = "http://gd2.mlb.com/components/game/mlb" + today->MLBDateString() + "gid_" + seaVS->gameID + "/boxscore.xml";

        for(int i = 0; i < 480; i++) { //Runs for a maximum of 4 hours for now
            XMLMemoryUnit gameboard;

            cout << "Polling for score (attempt " << i << ")" << endl;
            CURLTools::RetrieveXMLFile(gameScoreboard, &gameboard);

            XMLppTools::populateScoreboardXML(seaVS, &gameboard);

            cout << seaVS->away->code << endl;
            cout << seaVS->home->code << endl;

            disp->SendMessage(seaVS->away->code, disp->LINE1);
            disp->SendMessage(seaVS->home->code, disp->LINE2);

            delete(gameboard.memory); //Clear out the *memory*

            this_thread::sleep_for(chrono::seconds(30)); //Poll every 30 seconds
        }
    } else {
        cout << "Game not found, Mariners may not play today?" << endl;
        disp->SendMessage("No game today!",disp->LINE0);
    }
#pragma clang diagnostic pop

    return EXIT_SUCCESS;
}