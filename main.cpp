#include "DataStructures/XMLMemoryUnit.h"
#include "Tools/CURLTools.h"
#include "DataStructures/Game.h"
#include "Tools/XMLppTools.h"

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

    return EXIT_SUCCESS;
}