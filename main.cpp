#include <chrono>
#include <thread>
#include "DataStructures/XMLMemoryUnit.h"
#include "Tools/CURLTools.h"
#include "DataStructures/Game.h"
#include "Tools/XMLppTools.h"
#include "Hardware/GPIOPin.h"
#include "Hardware/CharacterDisplayHD44780.h"

using namespace std;
using namespace Glib;

int main() {
    std::locale::global(std::locale("")); //Required by ustring

    XMLMemoryUnit scoreboardToday;
    Game seaVs;
    const ustring url = "http://gd2.mlb.com/components/game/mlb/year_2016/month_05/day_13/scoreboard.xml";
    const ustring team = "sea"; //TODO: Enum of the possible IDs

    RetrieveXMLFile(url, &scoreboardToday); //Pull XML from MLB API

    XMLppTools::populateGameFromScoreboardXML(url, &seaVs, &scoreboardToday, team); //Take XML and populate the Game Object
    //TODO: Need to handle double headers, this only handles the first game


    //GPIO Test
    GPIOPin * pin26 = new GPIOPin("26");
    pin26->makeOut();

    for(int i = 0; i < 10; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        pin26->toggle();
    }

    delete(pin26);

    //Screen Test
    CharacterDisplayHD44780 * disp = new CharacterDisplayHD44780();
    disp->SendMessage("HELLO WORLD", disp->LINE0);

    return EXIT_SUCCESS;
}