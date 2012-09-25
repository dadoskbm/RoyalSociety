/**
* Class representing a Circle.
* @author Brandon Dadosky
*/
#pragma once
#include "cinder\ImageIo.h"
#include <Shape.h>
#include "RoyalSocietyApp.h"

using namespace ci;

class Circle : public Shape
{
public: 
	/**
	* Creates a Circle with the given line and fill colors
	* @param line Color for the line
	* @param fill Color for the fill
	* @param xC X-coordinate for the center of the circle
	* @param yC Y-coordinate for the center of the circle
	* @param r Radius of the circle
	*/
	Circle(Color8u line, Color8u fill, int xC, int yC, int r);

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
	int xC, yC, r;
};

Circle::Circle(Color8u line, Color8u fill, int xC, int yC, int r)
{
	this->line = line;
	this->fill = fill;
	this->xC = xC;
	this->yC = yC;
	this->r = r;
}

void Circle::draw(uint8_t* dataArr)
{
	double dist;
	//Only iterate through a box that contains the circle. Much faster than going through the entire image.
	for(int x = xC - r; x <= xC + r; x++)
	{
		for(int y = yC - r; y <yC + r; y++)
		{
			//Calculate the distance from the center, if it equals (or is close to)
			// the radius, the pixel becomes part of the circle.
			dist = math<double>().sqrt((xC - x) * (xC - x) + (yC - y) * (yC - y));

			//REVIEW COMMENT: There is a bug here that isn't drawing the border of your circles at the very bottom
			//				  I can't seem to find it anywhere though.
			if(math<double>().abs(r - dist) < .5)
				modify(line, x, y, dataArr);
			else if(dist < r && fill != 0) //TODO: Fill isn't exactly right, and stays toward the right of the circle. Might be a rounding issue.
				modify(fill, x, y, dataArr);
		}
	}
}

bool Circle::isInsideShape(int xPoint, int yPoint)
{
	int dist = math<double>().sqrt((xC - xPoint) * (xC - xPoint) + (yC - yPoint) * (yC - yPoint));
	if(dist <= r)
		return true;
	else
		return false;
}

void Circle::move(int dX, int dY)
{
	int newX = xC + dX;
	int newY = yC + dY;
	if(newX - r >= 0 && newX + r < WIDTH
		&& newY - r >= 0 && newY + r < HEIGHT)
	{
		xC = newX;
		yC = newY;
	}
}