/**
* Class representing a single shape. Shapes have a line color and a fill color.
* @author Brandon Dadosky
*/
#pragma once
#include "cinder\ImageIo.h"

using namespace ci;

class Shape
{
public: 

	/**
	* Uses the modification methods in RoyalSocietyApp.cpp to draw the shape
	*/
	virtual void draw(uint8_t* dataArr) = 0;

	/**
	 Moves the shape. The shape will not move any further if moving it would
	 take any part of it off the screen
	 @param dX Amount in the X to move it
	 @param dY Amount in the Y to move it
	 */
	virtual void move(int dX, int dY) = 0;

	/**
	* Checks to see if the given coordinates fall within the shape's bounds
	* @param x X-coordinate
	* @param y Y-coordinate
	* @return true if the given coordinates fall within the boundaries of the shape.
	*/
	virtual bool isInsideShape(int x, int y) = 0;

	/**
	* Adds a child shape.
	* @param shape Shape to add as a child.
	*/
	void addChild(Shape* shape);

protected:
	Color8u line;
	Color8u fill;

};