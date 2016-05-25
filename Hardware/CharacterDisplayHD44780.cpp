//
// Created by aj on 5/23/16.
//

#include <thread>
#include "CharacterDisplayHD44780.h"

using namespace std;

CharacterDisplayHD44780::CharacterDisplayHD44780() {
    //Make the pins outputs
    RS->makeOut();
    E->makeOut();
    D4->makeOut();
    D5->makeOut();
    D6->makeOut();
    D7->makeOut();

    //Startup the display in 4 bit mode
    LCDCommand(0x33, CMD);
    LCDCommand(0x32, CMD);
    LCDCommand(0x06, CMD);
    LCDCommand(0x0C, CMD);
    LCDCommand(0x28, CMD);
    LCDCommand(0x01, CMD);
}

void CharacterDisplayHD44780::LCDCommand(unsigned short command, bool type) {
    //Set Register select to character or command mode
    if(type) {
        RS->writeHigh();
    } else {
        RS->writeLow();
    }

    ClearData();

    //Send command (1st part) (upper bits)
    if((command & 0x10) == 0x10) {
        D4->writeHigh();
    }
    if((command & 0x20) == 0x20) {
        D5->writeHigh();
    }
    if((command & 0x40) == 0x40) {
        D6->writeHigh();
    }
    if((command & 0x80) == 0x80) {
        D7->writeHigh();
    }

    LCDEnableToggle();
    ClearData();

    //Send command (2nd part) (lower bits)
    if((command & 0x01) == 0x01) {
        D4->writeHigh();
    }
    if((command & 0x02) == 0x02) {
        D5->writeHigh();
    }
    if((command & 0x04) == 0x04) {
        D6->writeHigh();
    }
    if((command & 0x08) == 0x08) {
        D7->writeHigh();
    }

    LCDEnableToggle();
}

/**
 * Toggles enable pin on LCD
 */
void CharacterDisplayHD44780::LCDEnableToggle() {
    this_thread::sleep_for(DELAY);
    E->writeHigh();
    this_thread::sleep_for(DELAY);
    E->writeLow();
    this_thread::sleep_for(DELAY);
}

/**
 * Clears the data pins
 */
void CharacterDisplayHD44780::ClearData() {
    D4->writeLow();
    D5->writeLow();
    D6->writeLow();
    D7->writeLow();
}

void CharacterDisplayHD44780::SendMessage(string msg, unsigned short startAddress) {
    LCDCommand(startAddress, CMD);

    for(size_t i = 0; i < msg.length() && i < MAX_CHAR_WIDTH; i++) {
        LCDCommand((unsigned short)msg.at(i), CHAR);
    }
}

CharacterDisplayHD44780::~CharacterDisplayHD44780() {
    //TODO: Clear screen
    delete(RS);
    delete(E);
    delete(D4);
    delete(D5);
    delete(D6);
    delete(D7);
}











