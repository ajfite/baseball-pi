#include <iostream>
#include <libxml++/libxml++.h>
#include "DataStructures/XMLMemoryUnit.h"
#include "Tools/CURLTools.h"

using namespace std;
using namespace Glib;

int main() {
    std::locale::global(std::locale(""));  //Required by ustring

    XMLMemoryUnit mem;

    ustring str = "http://gd2.mlb.com/components/game/mlb/year_2016/month_05/day_12/scoreboard.xml";

    RetrieveXMLFile(str, &mem);

    //Proof of concept XML parser
    try {
        xmlpp::DomParser parser;
        parser.parse_memory(*(mem.memory));

        if(parser) {
            xmlpp::Node *root;
            root = parser.get_document()->get_root_node();

            xmlpp::NodeSet titles;
            titles = root->find("//game");

            for(xmlpp::NodeSet::iterator i = titles.begin(); i != titles.end(); i++)
            {
                xmlpp::Element *enode;
                enode = dynamic_cast<xmlpp::Element *>(*i);
                if(enode){
                    Glib::ustring str = "id";
                    cout << enode->get_attribute(str)->get_value() << endl;
                }
            }
        }
    } catch (exception &e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

    //mem.print();

    return EXIT_SUCCESS;
}