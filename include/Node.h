#pragma once
#ifndef NODEFILE
#define NODEFILE
#include "Shape.h"
/**
* Node of the linked list. item points to the node's item, next points to the next node, prev points to the previous node.
*/

/*
 *REVIEW COMMENT: I do like how you separated your Node class from the rest of the project. It makes it easier to examine its content
				  and modify/add things if needed. It doesn't seem like you actually use this class. You're still using the Node class
				  as it is defined in RoyalSocietyApp.h
*/
class Node
{
public:
	Shape* item;
	Node* next;
	Node* prev;
	//REVIEW COMMENT: I don't understand what ~Node() is for. It has a block of code in RoyalSocietyApp.cpp that 
	//				  has 'delete item;' there. It doesn't seem like this gets used at all but I may be missing something.
	~Node();
};
#endif