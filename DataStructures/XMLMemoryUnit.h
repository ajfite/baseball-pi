//
// Created by aj on 5/16/16.
//

#ifndef BASEBALL_PI_XMLMEMORYUNIT_H
#define BASEBALL_PI_XMLMEMORYUNIT_H

#include <glibmm/ustring.h>

class XMLMemoryUnit {
public:
    Glib::ustring * memory;

    XMLMemoryUnit();

    ~XMLMemoryUnit();

    //Note that the write callback may be called multiple times
    size_t WriteCallback(char * ptr, size_t sizeDataItem, size_t numData);
};


#endif //BASEBALL_PI_XMLMEMORYUNIT_H
