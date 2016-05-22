//
// Created by aj on 5/21/16.
//

#include "GPIOPin.h"
#include <fstream>

using namespace std;

/**
 * Instantiates a gpio pin
 */
GPIOPin::GPIOPin(Glib::ustring pinNum) {
    this->gpioPinNum = pinNum;
    this->GPIO_PIN_DIRECTORY = "/gpio" + pinNum;
    ofstream export;
    export.open((GPIO_DIR + GPIO_EXPORT_FILE).c_str());

    export << pinNum.c_str(); //Exports pin number

    export.close();
}

/**
 * DO NOT USE
 * Default constructor just sets up pin 4
 */
GPIOPin::GPIOPin() {
    this->GPIOPin("4");
}

GPIOPin::~GPIOPin() {
    ofstream unexport;
    unexport.open((GPIO_DIR + GPIO_UNEXPORT_FILE).c_str());

    unexport << this->gpioPinNum.c_str(); //Unexports pin number

    unexport.close();
}

void GPIOPin::writeInOut(bool in) {
    ofstream direction;
    direction.open((GPIO_DIR + GPIO_UNEXPORT_FILE).c_str());

    if(in) {
        direction << "in";
    } else {
        direction << "out";
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

void GPIOPin::makeIn() {
    writeInOut(true);
}

void GPIOPin::makeOut() {
    writeInOut(false);
}








