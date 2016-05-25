//
// Created by aj on 5/16/16.
//

#ifndef BASEBALL_PI_CURLTOOLS_H
#define BASEBALL_PI_CURLTOOLS_H

#include <glibmm/ustring.h>
#include "../DataStructures/XMLMemoryUnit.h"

class CURLTools {
public:
    static void RetrieveXMLFile(Glib::ustring URL, XMLMemoryUnit *data);
};
#endif //BASEBALL_PI_CURLTOOLS_H
