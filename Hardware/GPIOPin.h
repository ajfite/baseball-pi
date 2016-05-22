//
// Created by aj on 5/21/16.
//

#ifndef BASEBALL_PI_GPIOPIN_H
#define BASEBALL_PI_GPIOPIN_H


#include <glibmm/ustring.h>

class GPIOPin {
private:
    Glib::ustring gpioPinNum;
public:
    GPIOPin();
    GPIOPin(Glib::ustring pinNum);
    ~GPIOPin();

    //Constants needed for GPIO operation
    const Glib::ustring GPIO_DIR = "/sys/class/gpio";
    const Glib::ustring GPIO_EXPORT_FILE = "/export";
    const Glib::ustring GPIO_UNEXPORT_FILE = "/unexport";
};


#endif //BASEBALL_PI_GPIOPIN_H
