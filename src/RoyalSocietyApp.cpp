#include "RoyalSocietyApp.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Rectangle.h"
#include "Circle.h"
#include <Windows.h>

using namespace ci;
using namespace ci::app;
using namespace std;

void RoyalSocietyApp::setup()
{
	showInstructions = false;
	instructions = loadImage("instructions.png");
	//Establishes the sentry node. Its next and previous pointers point to itself, which is
	//very important for establishing a circular linked list.
	sentry = new Node;
	sentry->next = sentry;
	sentry->item = NULL;
	sentry->prev = sentry;

	surface = new Surface(WIDTH, HEIGHT, false);
	dataArr = surface->getData();
	//Test code
	insertAfter(sentry, new ShapeRectangle(Color8u(0, 0, 0), Color8u(255, 0, 0), 10, 10, 40, 40));
	insertAfter(sentry, new ShapeRectangle(Color8u(0, 0, 0), Color8u(0, 255, 0), 10, 20, 40, 40));
	insertAfter(sentry, new ShapeRectangle(Color8u(0, 0, 0), Color8u(0, 0, 255), 10, 30, 40, 40));
	insertAfter(sentry, new Circle(Color8u(0, 0, 0), Color8u(0xFA, 0xCA, 0xDE),225, 235, 99));
	insertAfter(sentry, new Circle(Color8u(0, 0, 0), Color8u(0xFA, 0xCA, 0xDE), 400, 400, 20));
	
}

void RoyalSocietyApp::mouseDown( MouseEvent event )
{
	if(event.isLeft())
	{
		if(event.isControlDown())
			remove(sentry->next);
		else
			reverse();
	}
	/*if(event.isLeft() && sentry->next != sentry)
		remove(sentry->next);*/
	else if(event.isRight())
		for(Node* cur = sentry->next; cur != sentry; cur = cur->next)
		{
			console() << event.getX() << "," << event.getY() << endl;
			if(cur->item->isInsideShape(event.getX(), event.getY()))
			{
				console() << "Inside " << cur->item << endl;
				promote(cur);
				break;
			}
		}
	else if(event.isMiddle())
	{
		Color8u line = Color8u(rand() % 256, rand() % 256, rand() % 256);
		Color8u fill = Color8u(rand() % 256, rand() % 256, rand() % 256);
		int x = rand() % (WIDTH - 200);
		int y = rand() % (HEIGHT - 200);
		if(rand() % 2 == 0)
			insertAfter(sentry, new ShapeRectangle(line, fill, x, y, rand() % 200, rand() % 200));
		else
			insertAfter(sentry, new Circle(line, fill, x, y, rand() % 200));
	}
}

void RoyalSocietyApp::update()
{
	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			modify(BGCOLOR, x, y, dataArr);
		}
	}
	dataArr = surface->getData();
	//Go through linked list starting from the BOTTOM and call every draw method. Each draw method will modify the pixel array through many
	//calls to modify(), therefore the surface is only updated past this point.
	for(Node* cur = sentry->prev;cur->item != NULL; cur = cur->prev)
	{
		cur->item->draw(dataArr);
	}
}

void RoyalSocietyApp::draw()
{
	
	gl::draw(*surface);
	if(showInstructions)
		gl::draw(instructions,Vec2f(0,0));
}

/**
* @brief Draw Circle
* 
* Draws a circle.
* 
* @param xC the X-coordinate of the center of the circle
* @param yC the Y-coordinate of the center of the circle
* @param r the radius of the circle
* @param line the color object containing color information for the outside line
* @param fill the color of the fill. If this value is 0, the circle won't be filled.
*/
//void drawCircle(int xC, int yC, int r, Color8u* line, Color8u* fill, uint8_t* dataArr) 
//{
//	double dist;
//	for(int x = 0; x < WIDTH; x++)
//	{
//		for(int y = 0; y < HEIGHT; y++)
//		{
//			//Calculate the distance from the center, if it equals (or is close to)
//			// the radius, the pixel becomes part of the circle.
//			dist = math<double>().sqrt((xC - x) * (xC - x) + (yC - y) * (yC - y));
//			if(math<double>().abs(r - dist) < 0.5)
//				modify(line, x, y, dataArr);
//			else if(dist < r && fill != 0) //TODO: Fill isn't exactly right, and stays toward the right of the circle. Might be a rounding issue.
//				modify(fill, x, y, dataArr);
//		}
//	}
//			
//}

/**
* Reverses the list
*/
void RoyalSocietyApp::reverse()
{
	Node* cur = sentry;
	Node* temp;
	do
	{
		temp = cur->next;
		cur->next = cur->prev;
		cur->prev = temp;
		cur = cur->next;
	} while(cur != sentry);
}

/**
* @brief Draw a line
* 
* Draws a straight line between the two points.
* 
* @param x1 the x coordinate of the first point
* @param y2 the y coordinate of the first point
* @param x1 the x coordinate of the second point
* @param y2 the y coordinate of the second point
* @param color the Color to of the line
*/
void drawLine(int x1, int y1, int x2, int y2, Color8u color, uint8_t* dataArr)
{
	//Implementation of Bresenham's line algorithm, derived from pseudocode
	//from Wikipedia.

	math<int> intMath = math<int>();
	int dx = intMath.abs(x2 - x1);
	int dy = intMath.abs(y2 - y1);

	int sx = intMath.signum(x2 - x1);
	int sy = intMath.signum(y2 - y1);
	int err = dx - dy;
	int x = x1;
	int y = y1;

	while(true)
	{
		modify(color,x,y, dataArr);
		if(x == x2 && y == y2)
			break;
		int e2 = 2 * err;
		if(e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if(e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

/*
 *REVIEW COMMENT: I understand that you had moved the drawRectangle(draw()) method into Shape defs.cpp (Even though I moved it again)
				  but when looking at the method it had changed. It wasn't a small change. It seems fairly drastic. To
				  me that warrants either A. delete the old code or B. explain what changed for the next coder to read.
				  Maybe there's a reason I would want to use one or the other.
*/

/**
* @brief Draw Rectangle
* 
* Draws a rectangle from point (x1,y1) to point (x2,y2).
* 
* @param xA the X-coordinate of the first point
* @param yA the Y-coordinate of the first point
* @param xB the X-coordinate of the second point
* @param yB the Y-coordinate of the secondpoint
* @param line the color for the line
* @param fill the color for the fill. If this is 0, the rectangle will not be filled.
*/

//void drawRectangle(int xA, int yA, int xB, int yB, Color8u* line, Color8u* fill, uint8_t* dataArr)
//{
//	int x1, x2, y1, y2;
//
//	//Swap values so x1 < x2 and y1 < y2
//	if(xB < xA && yB < yA)
//	{
//		x1 = xB;
//		y1 = yB;
//		x2 = xA;
//		y2 = yA;
//	}
//	else if(xB < xA && yB > yA)
//	{
//		x1 = xB;
//		y1 = yA;
//		x2 = xA;
//		y2 = yB;
//	}
//	else if(xB > xA && yB < yA)
//	{
//		x1 = xA;
//		y1 = xB;
//		x2 = xB;
//		y2 = yA;
//	}
//	else
//	{
//		x1 = xA;
//		x2 = xB;
//		y1 = yA;
//		y2 = yB;
//	}
//	
//
//	drawLine(x1, y1, x1, y2, line, dataArr);
//	drawLine(x1, y1, x2, y1, line, dataArr);
//	drawLine(x1, y2, x2, y2, line, dataArr);
//	drawLine(x2, y1, x2, y2, line, dataArr);
//
//	if(fill != 0)
//	{
//		for(int x = x1 + 1; x < x2; x++)
//		{
//			for(int y = y1 + 1; y < y2; y++)
//			{
//				modify(fill, x, y, dataArr);
//			}
//		}
//	}
//}


/**
* @brief Modify Pixel
* 
* Modifies a single pixel to a given color at a given 
* coordinate on the image. This method serves mainly to
* abstract the row-major order of the data array, provide
* one specific place to modify it, and perform bounds
* checking
* 
* @param color the Color8u object that contains of the desired color.
* @param x the X-coordinate
* @param y the Y-coordinate
* 
* @returns false if and only if the X or Y coordinates are out of bounds.
*/
bool modify(Color8u color, int x, int y, uint8_t* dataArr)
{
	if(x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
	{
		console() << "Draw failed: (" << x << "," << y << ") is out of bounds." << endl;
		return false;
	}
	int index = 3 * (x + y * WIDTH);
	dataArr[index] = color.r;
	dataArr[index + 1] = color.g;
	dataArr[index + 2] = color.b;
	return true;
}



void RoyalSocietyApp::insertAfter(Node* where, Shape* shape)
{
	Node* center = new Node;
	where->next->prev = center;
	center->item = shape;
	center->next = where->next;
	center->prev = where;
	where->next = center;

}

void RoyalSocietyApp::remove(Node* node)
{
	if(node == sentry)
	{
		console() << "WARNING: Attempted sentry node deletion. Program will terminate.";
		exit(1);
	}
	node->next->prev = node->prev;
	node->prev->next = node->next;
	delete node;
}

void RoyalSocietyApp::moveGroup(Node* first, Node* last, Node* to)
{
	first->prev->next = last->next;
	last->next->prev = first->prev;
	to->next->prev = last;
	to->next = first;
}

void RoyalSocietyApp::keyDown(KeyEvent event)
{
#define SPEED 5

	/*
	 *REVIEW COMMENT: I really like how you used switch(event.getChar()) as opposed to the way I did it.
					  It simplifies the code and at first glance is easier to understand.
	*/
	switch(event.getChar())
	{
	case 'w':
		sentry->next->item->move(0, -SPEED);
		break;
	case 'a':
		sentry->next->item->move(-SPEED, 0);
		break;
	case 's':
		sentry->next->item->move(0, SPEED);
		break;
	case 'd':
		sentry->next->item->move(SPEED, 0);
		break;
		/*
		 *REVIEW COMMENT: You had this set to KEY_SLASH which wasn't the instructions we were given but it did work
						  I changed it to work with '?' instead.				
		*/
	case '?':
		showInstructions = !showInstructions;
		break;
	}
}

void RoyalSocietyApp::move(Node* node, Node* to)
{
	if(node == sentry)
	{
		console() << "WARNING: Attempted sentry node move. Program will terminate.";
		exit(2);
	}
	node->next->prev = node->prev;
	node->prev->next = node->next;
	node->next = to->next;
	node->prev = to;
	to->next = node;
	node->next->prev = node;
	
}

void RoyalSocietyApp::promote(Node* node)
{
	move(node,sentry);
}

//TODO: This method is buggy and distorts the image.
//void RoyalSocietyApp::prepareSettings(Settings* settings)
//{
//	settings->setWindowSize(WIDTH, HEIGHT);
//	settings->setResizable(false);
//}

//Destructor for Node, needed to delete the enclosed Shape when delete gets called on the object.
Node::~Node()
{
	delete item;
}
CINDER_APP_BASIC( RoyalSocietyApp, RendererGl )