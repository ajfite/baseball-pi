//
// Created by aj on 5/24/16.
//

#include "MLBDate.h"

using namespace Glib;
using namespace std;

/**
 * Outputs the date in the MLB URL date format
 */
Glib::ustring MLBDate::MLBDateString() {
    return *formatStr;
}

/**
 * Create the date object representing the "date"
 */
MLBDate::MLBDate(time_t date) {
    struct tm * currtime;
    currtime = localtime(&date);

    //Fixme: This has the potential to break in so many different ways
    //Going to need a more robust way to handle timezones and such
    year = currtime->tm_year + 1900; //Years are 1900 indexed
    month = currtime->tm_mon + 1; //Months are 0 indexed
    day = currtime->tm_mday; //Days are 1 indexed

    char buffer[MAX_FORMAT_LENG]; //Fixme: likiely doing something funky with buffer sizes here
    snprintf(buffer, MAX_FORMAT_LENG, "/year_%04i/month_%02i/day_%02i/", year, month, day);

    //Prevents scope issues
    //TODO: probably a better way to do this
    formatStr = new ustring();
    formatStr->append(buffer);
}

/**
 * Create the date object representing the current date
 */
MLBDate::MLBDate() : MLBDate(time(NULL)) { }




