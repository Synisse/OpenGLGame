#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Flower.h"
#include "material.h"

int firstLayerCounter = 0;

void Flower::Init()
{

	//startposition
	SetPos(400, 270, 400);
	object = makeObject();
}

void Flower::Refresh()
{
	glColor3f(1.0, 1.0, 1.0);

glMatrixMode(GL_MODELVIEW);


glPushMatrix();

//glTranslatef(m_x,m_y,m_z);

	//LOL START
	//
	//LOLENDE
glPopMatrix();

glFlush();
materials(&noMaterials);

}

void Flower::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	//Refresh();
}

void Flower::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

GLuint Flower::getObject()
{
	return object;
}
int Flower::GetCurrentX()
{
    return m_x;
}

int Flower::GetCurrentZ()
{
    return m_z;
}


void Flower::Rotate()
{
	//rotate animation

	Refresh();
}
//fractal test

//**********************************************************
// Draws a triangle
void drawTriangle(Point a, Point b, Point c)
{ 
if(a.y <= -0.25){
	materials(&redPlasticMaterials);
}
else
{
	materials(&EmeraldMaterials);
}
firstLayerCounter++;
	glBegin(GL_TRIANGLES);
     glVertex2f(a.x,a.y);
     glVertex2f(b.x,b.y);
     glVertex2f(c.x,c.y);
   glEnd();
   materials(&noMaterials);
} // end draw triangle

//*******************************************************
// Function from class to draw the Sierpinski fractal
//   Recursion is FUN!
void drawSierpinski(Point a, Point b, Point c, int level)
{  
	if(level<2)
	{
		materials(&EmeraldMaterials);
	}
	else
	{
		materials(&redPlasticMaterials);
	}
   Point m0, m1, m2;
   if (level > 0) {
     m0.x = (a.x+b.x) /2.0;
     m0.y = (a.y+b.y) /2.0;
     m1.x = (a.x+c.x) /2.0;
     m1.y = (a.y+c.y) /2.0;
     m2.x = (b.x+c.x) /2.0;
     m2.y = (c.y+b.y) /2.0;
     drawSierpinski(a,m0,m1,level-1);
     drawSierpinski(b,m2,m0,level-1);
     drawSierpinski(c,m1,m2,level-1);
   } else drawTriangle(a,b,c);
   materials(&noMaterials);
} // end draw Sierpinski
GLuint Flower::makeObject()
{  
   GLuint list;
   list = glGenLists(1);
   glNewList(list, GL_COMPILE);
     // set the initial color
     glColor3f( 1.0, 0.0, 0.0 );
     // points for triangle to draw Sierpinski Gasket
     Point a, b, c;
     a.x=-0.5; a.y=-0.5;
     b.x=0.5; b.y=-0.5;
     c.x=0.0; c.y=0.5;
     drawSierpinski(a,b,c,3);
   glEndList();
   return list;
} // end make object