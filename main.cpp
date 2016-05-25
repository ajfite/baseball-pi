#include <chrono>
#include <thread>
#include "DataStructures/XMLMemoryUnit.h"
#include "Tools/CURLTools.h"
#include "DataStructures/Game.h"
#include "Tools/XMLppTools.h"
#include "Hardware/GPIOPin.h"
#include "Hardware/CharacterDisplayHD44780.h"
#include "DataStructures/MLBDate.h"

using namespace std;
using namespace Glib;

int main() {
    std::locale::global(std::locale("")); //Required by ustring

    XMLMemoryUnit scoreboardToday;
    Game seaVs;
    MLBDate * today = new MLBDate();

    const ustring urlScoreboard = "http://gd2.mlb.com/components/game/mlb" + today->MLBDateString() + "scoreboard.xml";
    const ustring team = "sea"; //TODO: Enum of the possible IDs

    CURLTools::RetrieveXMLFile(urlScoreboard, &scoreboardToday); //Pull XML from MLB API

    XMLppTools::populateGameFromScoreboardXML(urlScoreboard, &seaVs, &scoreboardToday, team); //Take XML and populate the Game Object
    //TODO: Need to handle double headers, this only handles the first game (lowish priority at the moment)


    //GPIO Test
    GPIOPin * pin26 = new GPIOPin("26");
    pin26->makeOut();

    for(int i = 0; i < 10; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));
        pin26->toggle();
    }

    delete(pin26);

    //Screen Test
    //Mockup Scoreboard
    CharacterDisplayHD44780 * disp = new CharacterDisplayHD44780();
    disp->SendMessage("   123456789 RHE", disp->LINE0);
    disp->SendMessage("SEA040002001 790", disp->LINE1);
    disp->SendMessage("LAA000001000 141", disp->LINE2);
    disp->SendMessage("Final Win: Hernandez", disp->LINE3);

    return EXIT_SUCCESS;
}