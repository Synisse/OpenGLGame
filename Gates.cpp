#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Gates.h"
#include "material.h"

bool firstGatePassed = false;
bool secondGatePassed = false;
bool thirdGatePassed = false;
bool fourthGatePassed = false;

void Gates::Init()
{

	//startposition
	SetPos(250, 200, 250);
}

void Gates::Refresh()
{

	glColor3f(1.0, 1.0, 1.0);

glMatrixMode(GL_MODELVIEW);
//glPushMatrix();
//
//glTranslatef(m_x,m_y,m_z);
//glRotatef(pos_x, 0.0, 1.0, 0.0);
//glTranslatef(10,10,10);
//materials(&redPlasticMaterials);
//glScaled(1.0,5.0,1.0);
//glutSolidCube(10);
//glTranslatef(m_x,m_y,m_z);
//glPopMatrix();
//
//glPushMatrix();
//glTranslatef(m_x,m_y-25,m_z+10);
//glRotatef(pos_x, 0.0, 1.0, 0.0);
//glTranslatef(10,10,10);
//materials(&redPlasticMaterials);
//glScaled(1.0,1.0,3.0);
//glutSolidCube(10);
//glTranslatef(m_x,m_y-25,m_z+10);
//glPopMatrix();

glLoadName(56);
glPushMatrix();

glTranslatef(150,200,500);
if(!firstGatePassed)
{
	materials(&RubyMaterials);
}
else
{
	materials(&JadeMaterials);
}
glutSolidTorus(10,40,16,32);
	
glPopMatrix();


glLoadName(63);
glPushMatrix();

glTranslatef(430,300,850);
glRotated(90,0.0,1.0,0.0);
if(!secondGatePassed)
{
	materials(&RubyMaterials);
}
else
{
	materials(&JadeMaterials);
}
glutSolidTorus(10,40,16,32);
	
glPopMatrix();


glLoadName(70);
glPushMatrix();

glTranslatef(850,170,550);
glRotated(-10,0.0,1.0,0.0);
if(!thirdGatePassed)
{
	materials(&RubyMaterials);
}
else
{
	materials(&JadeMaterials);
}
glutSolidTorus(10,40,16,32);
	
glPopMatrix();


glLoadName(77);
glPushMatrix();

glTranslatef(400,170,150);
glRotated(90,0.0,1.0,0.0);
if(!fourthGatePassed)
{
	materials(&RubyMaterials);
}
else
{
	materials(&JadeMaterials);
}
glutSolidTorus(10,40,16,32);
	
glPopMatrix();

glFlush();
materials(&noMaterials);

glLoadName(84);
}

void Gates::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	//Refresh();
}

void Gates::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}


int Gates::GetCurrentX()
{
    return m_x;
}

int Gates::GetCurrentZ()
{
    return m_z;
}


void Gates::Rotate()
{
	//rotate animation

	Refresh();
}

void Gates::SetGatePassed(int gateNumber)
{
	//rotate animation
	if(gateNumber==1)
	{
		firstGatePassed = true;
	}
	if(gateNumber==2)
	{
		secondGatePassed = true;
	}
	if(gateNumber==3)
	{
		thirdGatePassed = true;
	}
	if(gateNumber==4)
	{
		fourthGatePassed = true;
	}
}