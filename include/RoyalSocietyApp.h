/**
Project by Brandon Dadosky for CSE 274 homework assignment 2
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#define WIDTH 800
#define HEIGHT 600
#define TEXTURE_SIZE 1024

using namespace ci;
using namespace ci::app;
using namespace std;


class RoyalSocietyApp : public AppBasic
{
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	
};