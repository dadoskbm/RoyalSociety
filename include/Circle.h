/**
* Class representing a Circle.
* @author Brandon Dadosky
*/
#pragma once
#include "cinder\ImageIo.h"
#include <Shape.h>

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
	Circle(Color8u* line, Color8u* fill, int xC, int yC, int r);

	/**
	* Uses the modification methods in RoyalSocietyApp.cpp to draw the shape
	*/
	void draw(uint8_t* dataArr);

	/**
	* Checks to see if the given coordinates fall within the shape's bounds
	* @param x X-coordinate
	* @param y Y-coordinate
	* @return true if the given coordinates fall within the boundaries of the shape.
	*/
	bool isInsideShape(int x, int y);
private:
	Color8u line, fill;
	int xC, yC, r;
};