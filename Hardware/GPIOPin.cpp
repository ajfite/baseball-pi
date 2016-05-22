//
// Created by aj on 5/21/16.
//

#include "GPIOPin.h"
#include <iostream>
#include <fstream>

using namespace std;

GPIOPin::GPIOPin(Glib::ustring pinNum) {
    this->gpioPinNum = pinNum;

    ofstream export;
    ofstream.open((GPIO_DIR + GPIO_EXPORT_FILE).c_str());

    export << pinNum.c_str(); //Exports pin number

    ofstream.close();
}

GPIOPin::GPIOPin() {
    this->GPIOPin("4");
}

GPIOPin::~GPIOPin() {
    ofstream export;
    ofstream.open((GPIO_DIR + GPIO_UNEXPORT_FILE).c_str());

    export << this->gpioPinNum.c_str(); //Exports pin number

    ofstream.close();
}





