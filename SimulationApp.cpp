#include "Event.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

//Global variables to keep track of teller status, wait times, and the current time
bool tellerAvailable = true;
int currentTime = 0;
double totalWaitTime = 0;

using namespace std;
// Description: Processes an arrival event.
//              Function will either take a customer to a teller, or insert the customer into the bank queue is teller is
//              unavailable at the current time.
void processArrival(Event arrivalEvent, PriorityQueue<Event> &eventQueueEvent, Queue<Event> &bankLineEvent);

// Description: Processes departure event.
//              Function will take a customer who currently has to wait in line, and
//              insert them into the bank line.
void processDeparture(Event arrivalEvent, PriorityQueue<Event> &eventQueueEvent, Queue<Event> &bankLineEvent);

int main(int argc, char* argv[])
{
    cout << "Simulation Begins"<< endl;
    Queue<Event> bankLine;
    PriorityQueue<Event> eventQueue;
    Event tempEvent; // temporary event object to store customers into the priority queue.
    Event newEvent;
    int totalPeople;
    double avgWaitTime;
    string line;
    int inputLength, inputTime;
    ifstream the_file(argv[1]); //creates an ifstream of the file inputted via the command line
    while(getline(the_file >> ws, line)) // while there is still data in the file
    {
        stringstream ss(line); // store the line into a string "ss"
        ss >> inputTime >> inputLength; // take the first variable and store into integer inputLength, second variable into inputTime
        tempEvent.setType('A'); // set event to arrival
        tempEvent.setTime(inputTime); // set customer arrival time to inputTime
        tempEvent.setLength(inputLength); // set customer length to inputLength
        eventQueue.enqueue(tempEvent); // Push the customer into the priority queue.
    }
    totalPeople = eventQueue.getElementCount(); // get the total number of people for the simulation
    while(true)
    {
        try
        {
            // try to peek into the queue, and set the first element as the first person arriving.
            newEvent = eventQueue.peek();
        }
        catch (EmptyDataCollectionException&anException)
        {
            break; // break if trying to peek into an empty queue (there are no more customers)
        }
        currentTime = newEvent.getTime(); // current time is now what time the person got here.
        if(newEvent.getType() == 'A') // type A defines an arrival
        {
            cout << "Processing an arrival event at time:\t" << setw(2) << right << currentTime << endl;
            processArrival(newEvent, eventQueue, bankLine);
        }
        else // will be type 'D', suggesting a departure.
        {
            cout << "Processing a departure event at time:\t"  << setw(2) << right << currentTime << endl;
            processDeparture(newEvent, eventQueue, bankLine);
        }
    }
    avgWaitTime = totalWaitTime/totalPeople; // take the average wait time of the customers.

    cout << "Simulation Ends" << endl << endl;
    cout << "Final Statistics:" << endl;
    cout << "\tTotal number of people processed:  " << totalPeople << endl;
    cout << "\tAverage amount of time spent waiting: " << avgWaitTime << endl;
    return 0;
}

// Description: Processes an arrival event.
//              Function will either take a customer to a teller, or insert the customer into the bank queue is teller is
//              unavailable at the current time.
void processArrival(Event arrivalEvent, PriorityQueue<Event> &eventQueueEvent, Queue<Event> &bankLineEvent)
{
    int departureTime;
    Event newDepartureEvent;
    eventQueueEvent.dequeue(); // person has arrived, dequeue them from the priority queue
    if(bankLineEvent.isEmpty() == true && tellerAvailable == true)
    {
        departureTime = currentTime + arrivalEvent.getLength(); //departure time is the time they got there, plus the time of interaction
        // set the time, type, and length of their departure event.
        newDepartureEvent.setTime(departureTime);
        newDepartureEvent.setLength(0); // departure length will be 0, since leaving takes 0 time.
        newDepartureEvent.setType('D');
        eventQueueEvent.enqueue(newDepartureEvent); // push the departing customer into the priority queue.
        tellerAvailable = false; // teller is not available, since they are busy assisting customer.
    }
    else
    {
        bankLineEvent.enqueue(arrivalEvent); // bank teller was unavailable, make them wait in line
    }
    return;
}//end processArrival

// Description: Processes departure event.
//              Function will take a customer who currently has to wait in line, and
//              insert them into the bank line.
void processDeparture(Event arrivalEvent, PriorityQueue<Event> &eventQueueEvent, Queue<Event> &bankLineEvent)
{
    int departureTime;
    Event newDepartureEvent;
    eventQueueEvent.dequeue();
    Event customer;
    {
        try
        {
            customer = bankLineEvent.peek(); // peek into the bank line and see if empty
        }
        catch (EmptyDataCollectionException&anException)
        {
            tellerAvailable = true; // if peeking into an empty queue, means bank line is empty, teller is now available
            return;
        }
        bankLineEvent.dequeue(); // customer was processed by the bankLine, dequeue them
        departureTime = currentTime + customer.getLength(); // update their departure time
        totalWaitTime += departureTime - customer.getLength() - customer.getTime();
        newDepartureEvent.setLength(0); // create a departure event for them, same as above in arrival.
        newDepartureEvent.setTime(departureTime);
        newDepartureEvent.setType('D');
        eventQueueEvent.enqueue(newDepartureEvent); // push them into the priority queue to process their departure.
    }
    return;
}//end processDeparture
