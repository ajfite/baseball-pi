//
// Created by aj on 5/16/16.
//

#include "XMLMemoryUnit.h"

XMLMemoryUnit::XMLMemoryUnit() {
    memory = new Glib::ustring();
}

XMLMemoryUnit::~XMLMemoryUnit() {
    delete memory;
}

/**
 * Callback for cURL, takes in ptr and stores it in the class
 */
size_t XMLMemoryUnit::WriteCallback(char *ptr, size_t sizeDataItem, size_t numData) {
    size_t sizePreAppend = memory->bytes(); //Keep track of how full it is

    memory->append(ptr); //Must append since this function is called in chunks

    return memory->bytes() - sizePreAppend;
}





