#include <Rectangle.h>
#include <Circle.h>
#include "RoyalSocietyApp.h"

//Shape::Shape(Color8u* l, Color8u* f)
//{
//	line = l;
//	fill = f;
//}

ShapeRectangle::ShapeRectangle(Color8u* line, Color8u* fill, int x, int y, int l, int w)
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

Circle::Circle(Color8u* line, Color8u* fill, int xC, int yC, int r)
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
			if(math<double>().abs(r - dist) < 0.5)
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