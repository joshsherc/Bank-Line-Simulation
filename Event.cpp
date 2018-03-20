/*
 * Event.cpp
 *
 * Class Description: A class that contains different values corresponding to an event
 * Class Invariant: none
 *
 * Last modified on: June 2017
 * Authors: Hakeem Wewala and Josh Shercliffe
 */

#include <iostream>
#include "Event.h"

//Default Constructor
Event::Event()
{
    type = ' ';
    time = 0;
    length = 0;
}

//Parametrized Constructor
// Description: Create an event with the given parameters.

Event::Event(char aType, int aTime, int aLength)
{
    type = aType;
    time = aTime;
    length = aLength;
}

//Getters and Setters

//Description: Returns the type of the event object
char Event::getType() const
{
    return type;
}//end getType

//Description: Sets the event's type.
void Event::setType(const char aType)
{
    type = aType;
}//end setType

//Description: Returns the time of the event object
int  Event::getTime() const
{
    return time;
}//end getTime

//Description:Sets the event's time
void Event::setTime(const int aTime)
{
    time = aTime;
}//end setTime

//Description: Returns the length of the event object
int Event::getLength() const
{
    return length;
}// end getLength

//Description: Sets the length of the event object
void Event::setLength(const int aLength)
{
    length = aLength;
}//end setLength

// Description: Less than operator. Compares "this" Event object with "rhs" Event object.
// Returns true if the time  of "this" Event object is < the time of "rhs" Event object.
//if they have equal time, returns true if arrival is on lhs and departure on rhs
//if they are equal in time and type, then returns true
bool Event::operator<(const Event & rhs)
{
    if(this->time < rhs.time)//compare the time
        return true;
    else if(this->time == rhs.time && (this->type < rhs.type || this->type == rhs.type)) //if the events have equal time, which ever is an arrival gets higher priority
        return true;                                                                 //if the two events are identical, then lhs gets priority

    return false; //otherwise return false
} // end operator <

// Description: Prints the content of an Event.
ostream &operator<<(ostream & os, const Event & e)
{

    os << "Type: " << e.type << ", Time: " << e.time << ", Length: " << e.length << endl;

    return os;

} // end of operator<<

//end of Event.cpp
