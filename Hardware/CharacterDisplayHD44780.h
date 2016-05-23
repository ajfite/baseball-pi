//
// Created by aj on 5/23/16.
//

#ifndef BASEBALL_PI_CHARACTERDISPLAYHD44780_H
#define BASEBALL_PI_CHARACTERDISPLAYHD44780_H

/* My pin set up is as follows
 * LCD-GPIO
 * 1  -
 * 2  -
 * 3  -
 * 4  -
 * 5  -
 * 6  -
 * 7  -
 * 8  -
 * 9  -
 * 10 -
 * 11 -
 * 12 -
 * 13 -
 * 14 -
 * 15 -
 * 16 -
 */


class CharacterDisplayHD44780 {
private:

public:
    const int MAX_CHAR_WIDTH = 40;
    const int MAX_LINES = 4;

    CharacterDisplayHD44780();
    ~CharacterDisplayHD44780();
};


#endif //BASEBALL_PI_CHARACTERDISPLAYHD44780_H
