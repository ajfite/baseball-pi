//
// Created by aj on 5/16/16.
//

#ifndef BASEBALL_PI_CURLTOOLS_H
#define BASEBALL_PI_CURLTOOLS_H

#include <glibmm/ustring.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include "../DataStructures/XMLMemoryUnit.h"

void RetrieveXMLFile(Glib::ustring URL, XMLMemoryUnit * data);

#endif //BASEBALL_PI_CURLTOOLS_H
