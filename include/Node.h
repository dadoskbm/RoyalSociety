#pragma once
#ifndef NODEFILE
#define NODEFILE
#include "Shape.h"
/**
* Node of the linked list. item points to the node's item, next points to the next node, prev points to the previous node.
*/
class Node
{
public:
	Shape* item;
	Node* next;
	Node* prev;
	~Node();
};
#endif