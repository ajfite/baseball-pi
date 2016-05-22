//
// Created by aj on 5/21/16.
//

#ifndef BASEBALL_PI_GPIOPIN_H
#define BASEBALL_PI_GPIOPIN_H


#include <glibmm/ustring.h>

class GPIOPin {
private:
    Glib::ustring gpioPinNum;
    void writeInOut(bool in);
    void writeValue(bool val);

    //Constants needed for GPIO operation
    const Glib::ustring GPIO_DIR = "/sys/class/gpio";
    const Glib::ustring GPIO_EXPORT_FILE = "/export";
    const Glib::ustring GPIO_UNEXPORT_FILE = "/unexport";
    const Glib::ustring GPIO_VALUE_FILE = "/value";
    const Glib::ustring GPIO_DIRECTION_FILE = "/direction";
    Glib::ustring GPIO_PIN_DIRECTORY;
public:
    GPIOPin();
    GPIOPin(Glib::ustring pinNum);
    ~GPIOPin();
    void makeIn();
    void makeOut();
    bool readValue();
    bool isInput();
    void writeHigh();
    void writeLow();
    bool toggle();
};


#endif //BASEBALL_PI_GPIOPIN_H
