/*
 * Node.h
 *
 * Class Description: node of a singly linked list (Priority Queue) ADT
 *                      in which the data is of "int" data type
 * Last modified on: June 2017
 * Author: Hakeem Wewala and Josh Shercliffe
 */
#pragma once
#include <iostream>
template <class ElementType>
class Node
{
public:
    ElementType data; // the data in the node
    int priority; //priority of the node in the queue
    Node* next; //Pointer to next node

    //constructors
    Node();
    Node(ElementType theData);
    Node(ElementType theData, Node* theNextNode);
};
//end Node.h

//constructors
template <class ElementType>
Node<ElementType>::Node()
{
    next = NULL;
}
template <class ElementType>
Node<ElementType>::Node(ElementType theData)
{
    data = theData;
    next = NULL;
}
template <class ElementType>
Node<ElementType>::Node(ElementType theData, Node* theNextNode)
{
    data = theData;
    next = theNextNode;
}

//end Node.cpp
