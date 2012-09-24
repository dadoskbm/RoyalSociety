/**
Project by Brandon Dadosky for CSE 274 homework assignment 2
*/
#pragma once
/**
* @file RoyalSocietyApp.h
* 
* @author Brandon Dadosky
* @date September 2012
* 
* @note This file is (c) 2012.  It is licensed under the
* CC gv 3.0 license (http://creativecommons.org/licenses/by/3.0/),
* which means you are free to use, share, and remix it as long as you
* give attribution.  Commercial uses are allowed.
*/
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Shape.h"

#define WIDTH 800
#define HEIGHT 600
#define SURFACE_SIZE 1024
#define BGCOLOR Color8u(255,255,255)

using namespace ci;
using namespace ci::app;
using namespace std;

//Drawing methods (Note: Outside of any class)
void drawLine(int xI, int yI, int xF, int yF, Color8u color,uint8_t* dataArr);
bool modify(Color8u color, int x, int y,uint8_t* dataArr);

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


class RoyalSocietyApp : public AppBasic
{
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	//void prepareSettings(Settings* settings);
private:
	/**
	* Moves a group of nodes.
	* @param first First member to move
	* @param last Last member to move
	* @param to Member to place the group after.
	*/
	void moveGroup(Node* first, Node* last, Node* to);
	/**
	* Adds a Shape to the list after the given Node
	* @param where Where to place the new item after
	* @param shape Shape to add.
	*/
	void insertAfter(Node* where, Shape* item);
	/**
	* Removes the given node from the list, assigning the pointer before
	* it to the node after it.
	* @param node Node to be removed.
	*/
	void remove(Node* node);
	/**
	* Moves the node "node" to after the node "to"
	*/
	void move(Node* node, Node* to);
	/**
	* Moves the specified node to the very top of the list
	*/
	void promote(Node* node);
	/**
	* Reverses the list
	*/
	void reverse();
	
	Surface* surface;
	uint8_t* dataArr;
	//The first node in the linked list. The first one always has a null pointer for its item,
	//and when initially created, next will point to itself.
	Node* sentry;
	bool showInstructions;
	gl::Texture instructions;
	
};

