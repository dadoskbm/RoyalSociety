/**
* Class representing a Rectangle. A Rectangle has a position (x,y coordinate of upper-left corner), a length, and a width.
* Author: Brandon Dadosky
*/

#pragma once

#include <Shape.h>
#include "cinder\ImageIo.h"
#include "RoyalSocietyApp.h"

using namespace ci;

class ShapeRectangle : public Shape
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
	ShapeRectangle(Color8u line, Color8u fill, int x, int y, int l, int w);
	
	/**
	* Uses the modification methods in RoyalSocietyApp.cpp to draw the shape
	*/
	void draw(uint8_t* dataArr);

	/**
	 Moves the shape. The shape will not move any further if moving it would
	 take any part of it off the screen
	 @param dX Amount in the X to move it
	 @param dY Amount in the Y to move it
	 */
	void move(int dX, int dY);

	/**
	* Checks to see if the given coordinates fall within the shape's bounds
	* @param x X-coordinate
	* @param y Y-coordinate
	* @return true if the given coordinates fall within the boundaries of the shape.
	*/
	bool isInsideShape(int x, int y);
protected:
	int x,y,l,w;
};

ShapeRectangle::ShapeRectangle(Color8u line, Color8u fill, int x, int y, int l, int w)
{
	this->x = x;
	this->y = y;
	this->l = l;
	this->w = w;
	this->fill = fill;
	this->line = line;
}

void ShapeRectangle::draw(uint8_t* dataArr)
{
	int x2 = x + w;
	int y2 = y + l;
	drawLine(x, y, x, y2, line, dataArr);
	drawLine(x, y, x2, y, line, dataArr);
	drawLine(x, y2, x2, y2, line, dataArr);
	drawLine(x2, y, x2, y2, line, dataArr);

	if(fill != 0)
	{
		for(int xFill = x + 1; xFill < x2; xFill++)
		{
			for(int yFill = y + 1; yFill < y2; yFill++)
			{
				modify(fill, xFill, yFill, dataArr);
			}
		}
	}
}

bool ShapeRectangle::isInsideShape(int pointX, int pointY)
{
	if(pointX > x && pointX <= x + w
		&& pointY >= y && pointY <= y + l)
		return true;
	else
		return false;
}

void ShapeRectangle::move(int dX, int dY)
{
	int newX = x + dX;
	int newY = y + dY;
	if(newX >= 0 && newX + w < WIDTH
		&& newY >= 0 && newY + l < HEIGHT)
	{
		x = newX;
		y = newY;
	}
}

