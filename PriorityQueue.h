/*
 * PriorityQueue.h
 *
 * Class Description: A position-oriented data collection ADT.
 * Class Invariant:  The elements stored in this Priority Queue are always sorted.
 *
 * Last modified on: June 2017
 * Author: Hakeem Wewala and Josh Shercliffe
 */
#include "Node.h"
#include "EmptyDataCollectionException.h"
template <class ElementType>
class PriorityQueue
{

private:
    int elementCount; // Number of elements stored in the Queue
    Node<ElementType> *head; //Pointer to the first node in the Queue

//Private helper methods

    //Description: Removes and deletes all nodes in the linked list
    void deleteAll();

public:

// Let's put our constructor(s) and destructor (if any) ***here***.

//default constructor
//Description: initializes empty queue
    PriorityQueue();

//destructor
    ~PriorityQueue();

//for testing purposes, prints the priorityQueue
    void printPriorityQueue();
    /******* Public Interface - START - *******/

    // Description: Returns the number of elements in the Priority Queue.
    // (This method eases testing.)
    // Time Efficiency: O(1)
    int getElementCount() const;

    // Description: Returns "true" is this Priority Queue is empty, otherwise "false".
    // Time Efficiency: O(1)
    bool isEmpty() const;

    // Description: Inserts newElement in sort order.
    //              It returns "true" if successful, otherwise "false".
    // Precondition: This Priority Queue is sorted.
    // Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
    // Time Efficiency: O(n)
    bool enqueue(const ElementType& newElement);

    // Description: Removes the element with the "highest" priority.
    //              It returns "true" if successful, otherwise "false".
    // Precondition: This Priority Queue is not empty.
    // Time Efficiency: O(1)
    bool dequeue();

    // Description: Returns (a copy of) the element with the "highest" priority.
    // Precondition: This Priority Queue is not empty.
    // Postcondition: This Priority Queue is unchanged.
    // Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
    // Time Efficiency: O(1)
    ElementType peek() const throw(EmptyDataCollectionException);

    /******* Public Interface - END - *******/

// Let's feel free to add other private helper methods to our Priority Queue class.

}; // end method Declarations
//Description: initializes empty queue
template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue()
{
    head = NULL;
    elementCount = 0;
} // end constructor

//Destructor
template <class ElementType>
PriorityQueue<ElementType>::~PriorityQueue()
{
    //Delete all dynamically allocated memory
    deleteAll();
} // end destructor

//Description: Removes and deletes all nodes in the linked list
template <class ElementType>
void PriorityQueue<ElementType>::deleteAll()
{
    Node<ElementType> *nodeToDelete = head;

    //Cycle through the list
    while (nodeToDelete != NULL)
    {
        head = head->next; //move head to next node
        nodeToDelete->next = NULL;
        delete nodeToDelete; //delete the old head
        nodeToDelete = NULL;
        nodeToDelete = head; //new head will be deleted next
    }
    elementCount = 0;
    head = NULL;
} //end deleteAll()

// Description: Returns the number of elements in the Priority Queue.
// (This method eases testing.)
// Time Efficiency: O(1)
template <class ElementType>
int PriorityQueue<ElementType>::getElementCount() const
{
    return elementCount;
}


// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const
{
    return (head == NULL);
}

// Description: Inserts newElement in sort order.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is sorted.
// Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
// Time Efficiency: O(n)
template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(const ElementType& newElement)
{
    bool nodePlaced; //bool variable used to determine whether the new Element has already been placed or not
    Node<ElementType> *newNode, *q1, *q2; //q1 and q2 are used to traverse the list
    newNode = new Node<ElementType>;
    newNode->data = newElement;

    //Corner cases
    if (isEmpty()) //if there are no elements in the queue, newElement will be at the head with the highest priority
    {
        newNode->priority = 1;
        head = newNode;
        elementCount++;
        return true;
    }
    if (newNode->data < head->data) //check if data has higher priority than head
    {
        newNode->next = head;
        newNode->priority = 1;
        head = newNode;
        elementCount++;
        return true;
    }
    if (getElementCount() == 1 && (head->data < newNode->data)) //if there is one element in the list and the new node has lower priority than it.
    {
        head->next = newNode;
        newNode->priority = 2;
        elementCount++;
        return true;
    }
//By now we know there are two or more elements in the queue
    q1 = head->next; //2nd element in list


    if (getElementCount() == 2 && q1->data < newNode->data) //2 elements in the list and newNode goes at the end
    {
        q1->next = newNode;
        newNode->priority = 3;
        elementCount++;
        return true;
    }
    if (newNode->data < q1->data) //if data has 1 less priority than head
    {
        head->next = newNode;
        newNode->next = q1;
        newNode->priority = 2;
        elementCount++;
        return true;
    }
//By now we know there are 3 or more elements in the list
    q2 = q1->next; //3rd element in list
    //General case
    while (q2->next != NULL) //loops through the queue
    {
        if (newNode->data < q2->data && nodePlaced == false) //once we find the spot where our newNode node should be, we place it between q1 and q2
        {
            q1->next = newNode; //q1 is the node before newNode
            newNode->next = q2; //q2 is the node after newNode
            newNode->priority = q2->priority; //newNode now has the priority of the node which it went in front of
            elementCount++;
            nodePlaced = true; //node has now been placed
        }
        if (nodePlaced == true) // if the node has been placed, all nodes after it will have their priority increased by 1
        {
            q2->priority += 1;
        }

        q1 = q1->next;//traversing the queue
        q2 = q2->next;//traversing the queue
    }
    //corner case to check the last node in the queue
    if(newNode->data < q2->data && nodePlaced == false) //check if the data goes before the last element in the list
    {
        q1->next = newNode;
        newNode->next = q2;
        newNode->priority = q2->priority;
        elementCount++;
        nodePlaced = true;
    }

    if(nodePlaced == false) //if we loops through the queue and the node was not placed, it means it has lowest priority and goes at the end of the queue)
    {
        q2->next = newNode;
        newNode->priority = q2->priority + 1;
        elementCount++;
        nodePlaced = true;
    }

    if (nodePlaced == true)
        return true;

    return false; // if somehow the node was not placed, return false (should never be the case)
} //end enqueue;

// Description: Removes the element with the "highest" priority.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is not empty.
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::dequeue()
{
    if(isEmpty())
        return false;

    Node<ElementType> *nodeToDelete = head; //set nodeToDelete as the head
    head = head->next;//move the head to the right by one
    nodeToDelete->next = NULL; //make pointer to next node null
    delete nodeToDelete; //delete the old head
    nodeToDelete = NULL; //set the node to null
    elementCount --;

    return true;
}//end dequeue

// Description: Returns (a copy of) the element with the "highest" priority.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType PriorityQueue<ElementType>::peek() const throw(EmptyDataCollectionException)
{
    // Enforce precondition
    if (isEmpty())
        throw EmptyDataCollectionException("peek() called with empty queue.");

    // Queue is not empty; return data of element at front of queue
    return head->data;
} // end peek

template <class ElementType>
void PriorityQueue<ElementType>::printPriorityQueue() //function to print the priority queue (testing purposes)
{
    Node<ElementType> *currentNode = head;
    while(currentNode!=NULL)
    {
        cout << currentNode->data << endl;
        currentNode = currentNode->next;
    }
}











