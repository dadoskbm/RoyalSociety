/**
* Class representing a Rectangle. A Rectangle has a position (x,y coordinate of upper-left corner), a length, and a width.
* Author: Brandon Dadosky
*/

#pragma once

#include <Shape.h>
#include "cinder\ImageIo.h"

using namespace ci;

class Rectangle : public Shape
{
public:
	/**
	* Creates a Rectangle
	* @param line Color for the line
	* @param fill Color for the fill
	* @param x X-coordinate of the upper-left corner of the rectangle
	* @param y Y-coordinate of the upper-left corner of the rectangle
	* @param l Length of the rectangle
	* @param w Width of the rectangle
	*/
	Rectangle(Color8u* line, Color8u* fill, int x, int y, int l, int w);

	/**
	* Uses the modification methods in RoyalSocietyApp.cpp to draw the shape
	*/
	void draw();

	/**
	* Checks to see if the given coordinates fall within the shape's bounds
	* @param x X-coordinate
	* @param y Y-coordinate
	* @return true if the given coordinates fall within the boundaries of the shape.
	*/
	bool isInsideShape(int x, int y);
};


