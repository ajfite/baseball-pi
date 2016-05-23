//
// Created by aj on 5/21/16.
//

#include "GPIOPin.h"
#include <fstream>

using namespace std;
using namespace Glib;

//TODO: Handle error conditions in all of these functions

/**
 * Instantiates a gpio pin
 */
GPIOPin::GPIOPin(ustring pinNum) {
    ofstream exportFile; //Can't use "export" because its a reserved word

    this->gpioPinNum = pinNum;
    this->GPIO_PIN_DIRECTORY = "/gpio" + pinNum;

    exportFile.open((GPIO_DIR + GPIO_EXPORT_FILE).c_str());

    exportFile << pinNum.c_str(); //Exports pin number

    exportFile.close();
}

/**
 * Unexports the pin for other uses
 */
GPIOPin::~GPIOPin() {
    ofstream unexport;
    unexport.open((GPIO_DIR + GPIO_UNEXPORT_FILE).c_str());

    unexport << this->gpioPinNum.c_str(); //Unexports pin number

    unexport.close();
}

/**
 * Sets up pin as an in or out
 * in: true for "in", false for "out"
 */
void GPIOPin::writeInOut(bool in) {
    ofstream direction;
    direction.open((GPIO_DIR + GPIO_UNEXPORT_FILE).c_str());

    if(in) {
        direction << "in";
    } else {
        direction << (string)"out";
    }

    direction.close();
}

/**
 * Writes a value to the gpio pin
 */
void GPIOPin::writeValue(bool val) {
    ofstream value;
    value.open((GPIO_DIR + GPIO_PIN_DIRECTORY + GPIO_VALUE_FILE).c_str());

    value << (int)val; //Write value to file

    value.close();
}

/**
 * Writes a 1 to the gpio pin
 */
void GPIOPin::writeHigh() {
    writeValue(true);
}

/**
 * Writes a 0 to the gpio pin
 */
void GPIOPin::writeLow() {
    writeValue(false);
}

/**
 * Sets the pin as an input
 */
void GPIOPin::makeIn() {
    writeInOut(true);
}

/**
 * Sets the pin as an output
 */
void GPIOPin::makeOut() {
    writeInOut(false);
}

/**
 * Reads a value and returns a bool (int) indicating the value
 */
bool GPIOPin::readValue() {
    ifstream value;
    value.open((GPIO_DIR + GPIO_PIN_DIRECTORY + GPIO_VALUE_FILE).c_str());

    char val = (char) value.get();

    value.close();

    return val == '1';
}

/**
 * Toggles the current state
 * return: the state toggled from
 */
bool GPIOPin::toggle() {
    bool currVal = readValue();
    writeInOut(!currVal);
    return currVal;
}

/**
 * Gives whether the gpio is an input or not
 * FIXME: Unimplemented
 */
bool GPIOPin::isInput() {
    return false; //UNIMPLEMENTED: DO NOT USE YET
}

/**
 * Default constructor
 * just instantiates pin 4
 * Not really useful unless you want pin 4
 */
GPIOPin::GPIOPin() : GPIOPin("4") { }


