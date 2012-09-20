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
	* Checks to see if the given coordinates fall within the shape's bounds
	* @param x X-coordinate
	* @param y Y-coordinate
	* @return true if the given coordinates fall within the boundaries of the shape.
	*/
	virtual bool isInsideShape(int x, int y) = 0;

protected:
	Color8u* line;
	Color8u* fill;
};