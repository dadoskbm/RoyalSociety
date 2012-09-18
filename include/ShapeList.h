/**
* My implementation of the linked list, designed to work with Shapes.
*
* This class contains two subclasses, a Node, and an Iterator. The node contains
* pointers to its specified Shape, and also a pointer to the next Node. The iterator
* is responsible for iterating through the entire list and returning members as
* necessary
* 
* Satisfies most of goal A.
* @author Brandon Dadosky
*/
#pragma once
#include <Shape.h>

class ShapeList
{
public:
	/**
	* Creates a linked Shape list
	*/
	ShapeList();

	/**
	* Adds a Shape to the list
	* @param shape Pointer to the Shape to add to the list.
	*/
	void add(Shape* shape);

	/**
	* Retrieves a pointer to the shape at the given index
	* @param index Index of the Shape to retrieve from the list.
	* @return Shape at the given index.
	*/
	Shape* get(int index);

	/**
	* Removes and returns the shape at the given index
	* @param index Index of the Shape to remove.
	* @return The Shape removed from the list.
	*/
	Shape* remove(int index);

	/**
	* Checks to see if the list is empty.
	* @return true if the list is empty.
	*/
	bool isEmpty();
	class Iterator {};
private:
	/**
	* Represents a Node in the linked list. A node simply contains a pointer to the item
	* it holds, and a pointer to the next Node in the list.
	*/
	class Node
	{
	public:
		/**
		* Creates a Node with the given item and link to the next node.
		*/
		Node(Node* next, Shape* item);
		Node* next;
		Shape* item;
	};
	Node* initial;

};