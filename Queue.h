/*
 * Queue.h
 *
 * Class Description: Circular array based queue constructed as an ADT.
 *                    Class is designed as a template class, to allow insertion of any
                      data types.
 * Last modified on: July 4th 2017
 * Author: Hakeem Wewala and Josh Shercliffe
 */
#pragma once
#include "EmptyDataCollectionException.h"

using namespace std;
template <class ElementType>
class Queue
{

private:
    static const int MAX_ELEMENTS = 100;
    int ElementCount;
    int front;
    int back;
    ElementType elements[MAX_ELEMENTS];

public:
    // Let's put our constructor(s) and destructor (if any) ***here***.
    //Default Constructor
    Queue();
    /******* Public Interface - START - *******/

    // Description: Returns the number of elements in the Queue.
    // (This method eases testing.)
    // Time Efficiency: O(1)
    int getElementCount() const;

    // Description: Returns "true" is this Queue is empty, otherwise "false".
    // Time Efficiency: O(1)
    bool isEmpty() const;

    // Description: Adds newElement to the "back" of this Queue
    //              (not necessarily the "back" of its data structure) and
    //              returns "true" if successful, otherwise "false".
    // Time Efficiency: O(1)
    bool enqueue(const ElementType& newElement);

    // Description: Removes the element at the "front" of this Queue
    //              (not necessarily the "front" of its data structure) and
    //              returns "true" if successful, otherwise "false".
    // Precondition: This Queue is not empty.
    // Time Efficiency: O(1)
    bool dequeue();

    // Description: Returns (a copy of) the element located at the "front" of this Queue.
    // Precondition: This Queue is not empty.
    // Postcondition: This Queue is unchanged.
    // Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
    // Time Efficiency: O(1)
    ElementType peek() const throw(EmptyDataCollectionException);

    /******* Public Interface - END - *******/

// Let's feel free to add other private helper methods to our Queue class.

}; // end Queue

//Default Constructor
template <class ElementType>
Queue<ElementType>::Queue() : ElementCount(0), front(0), back(0)
{
}

// Description: Returns the number of elements in the Queue.
// (This method eases testing.)
// Time Efficiency: O(1)
template <class ElementType>
int Queue<ElementType>::getElementCount() const
{
    return ElementCount;
}

// Description: Returns "true" is this Queue is empty, otherwise "false".
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::isEmpty() const
{
    if(getElementCount() > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Description: Adds newElement to the "back" of this Queue
//              (not necessarily the "back" of its data structure) and
//              returns "true" if successful, otherwise "false".
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::enqueue(const ElementType& newElement)
{
    //check to see if the array is full
    if((front == 0 && back == (MAX_ELEMENTS -1)) || (front == back+1))
    {
        return false;
    }
    //check to see if the array got reset from a previous dequeue
    if( front == -1)
    {
        front = 0; // reset front and back positions back to 0
        back = 0;
    }
    else
    {
        if(back == MAX_ELEMENTS-1) // check to see if the back of the array is at the last element
        {
            back = 0; // reset back to the first position
        }
        else
        {
            back = back +1; //increment back by 1
        }
        elements[back] = newElement; // insert the element in the back of the circular array
        ElementCount++; // increment the ElementCount
    }
    return true;

}

// Description: Removes the element at the "front" of this Queue
//              (not necessarily the "front" of its data structure) and
//              returns "true" if successful, otherwise "false".
// Precondition: This Queue is not empty.
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::dequeue()
{
    if(isEmpty() == true )
    {
        return false; // return false if the queue is empty
    }
    ElementCount--; // element was dequeued, so remove decrement ElementCount
    if (front == back)
    {
        front = -1; // front is the back, reset the circular array
        back = -1;
    }
    else
    {
        if(front == (MAX_ELEMENTS -1)) // check to see if the front is right before the end of the array
        {
            front = 0; // front is just before the end, so loop back to start
        }
        else
        {
            front = front +1; // front has now moved up 1
        }
    }
    return true;
}

// Description: Returns (a copy of) the element located at the "front" of this Queue.
// Precondition: This Queue is not empty.
// Postcondition: This Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType Queue<ElementType>::peek() const throw(EmptyDataCollectionException)
{
    if(isEmpty() == true)
    {
        throw EmptyDataCollectionException("peek() called with an empty queue."); // throw exception if the queue was empty
    }
    return elements[front+1]; // returns the first element in the circular array, which is 1 position above the front.
}
