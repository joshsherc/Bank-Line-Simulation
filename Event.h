/*
 * Event.h
 *
 * Class Description: A class that contains different values corresponding to an event
 * Class Invariant: none
 *
 * Last modified on: June 2017
 * Authors: Hakeem Wewala and Josh Shercliffe
 */

#pragma once
#include <iostream>
using namespace std;


class Event
{

private:
    char type;//'A' for Arrival, 'D' for departure
    int time;
    int length;

public:
    //default constructor
    Event();
    //Parametrized constructor
    // Description: Create an event with the given parameters.
    Event(char aType, int aTime, int aLength);

    //Getters and Setters

    //Description: Returns the type of the event object
    char  getType() const;

    //Description: Sets the event's type.
    void setType(const char aType);

    //Description: Returns the time of the event object
    int  getTime() const;

    //Description:Sets the event's time
    void setTime(const int aTime);

    //Description: Returns the length of the event object
    int getLength() const;

    //Description: Sets the length of the event object
    void setLength(const int aLength);


// Description: Less than operator. Compares "this" Event object with "rhs" Event object.
// Returns true if the time of "this" Event object is < the time of "rhs" Event object.
    bool operator<(const Event & rhs);

    // Description: Prints the content of an Event.
    friend ostream & operator<<(ostream & os, const Event & e);
}; // end Event
