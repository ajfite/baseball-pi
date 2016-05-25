//
// Created by aj on 5/23/16.
//

#ifndef BASEBALL_PI_CHARACTERDISPLAYHD44780_H
#define BASEBALL_PI_CHARACTERDISPLAYHD44780_H

#include <chrono>
#include "GPIOPin.h"

/**
 * This project uses a Hitachi HD44780 4x20 character display
 * it should be compatible with any 4x20 character display based on the Hitachi controller
 *
 * More information on the controller can be found here
 *
 * My pin set up is as follows
 * #  | LCD | Description | GPIO
 * 1  - VSS - Power 5v    - 5v
 * 2  - VDD - Power Gnd   - Gnd
 * 3  - V0  - Contrast    - 10k Potentiometer
 * 4  - RS  - Reg Select  - 25
 * 5  - RW  - Read/Write  - Gnd (future use)
 * 6  - E   - Enable      - 24
 * 7  - D0  - Unused      - X
 * 8  - D1  - Unused      - X
 * 9  - D2  - Unused      - X
 * 10 - D3  - Unused      - X
 * 11 - D4  - Data 4      - 23
 * 12 - D5  - Data 5      - 17
 * 13 - D6  - Data 6      - 21
 * 14 - D7  - Data 7      - 22
 * 15 - A   - Light 5v    - 5v (future transistor for backlight control)
 * 16 - K   - Light Gnd   - Gnd
 */
class CharacterDisplayHD44780 {
private:
    const int MAX_CHAR_WIDTH = 40;
    const int MAX_LINES = 4;
    const std::chrono::milliseconds DELAY = std::chrono::milliseconds(5);

    const bool CMD = false;
    const bool CHAR = true;

    GPIOPin * RS = new GPIOPin("25");
    GPIOPin * E  = new GPIOPin("24");
    GPIOPin * D4 = new GPIOPin("23");
    GPIOPin * D5 = new GPIOPin("17");
    GPIOPin * D6 = new GPIOPin("21");
    GPIOPin * D7 = new GPIOPin("22");

    void LCDEnableToggle();
    void ClearData();
    void LCDCommand(unsigned short command, bool type);
public:
    const unsigned short LINE0 = 0x80;
    const unsigned short LINE1 = 0xC0;
    const unsigned short LINE2 = 0x94;
    const unsigned short LINE3 = 0xD4;

    CharacterDisplayHD44780();
    ~CharacterDisplayHD44780();
    void SendMessage(std::string msg, unsigned short startAddress);
    //TODO: Make the LCD screen commands
    //TODO: Safely destroy screen
    //TODO: General clear command
    //TODO: Implement shifting
    //TODO: Implement Cursor controls
};


#endif //BASEBALL_PI_CHARACTERDISPLAYHD44780_H
