#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Sun.h"
#include "material.h"

GLfloat angle = 0;
GLfloat smallStep = 0.1;
GLfloat bigStep = 0.5;
GLfloat stepSize = 0;

void Sun::Init()
{

	//startposition
	SetPos(512, 100, 512);
	stepSize = bigStep;
}

void Sun::Refresh()
{
	angle += stepSize;

	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(m_x,m_y,m_z);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glTranslatef(0,0,500);
	materials(&GoldMaterials);
	glColor3d(255,255,0);
	//glutSolidSphere(40,16,16);
	glTranslatef(m_x,m_y,m_z);
	glColor3d(255,255,255);
	glPopMatrix();

	//z is x
	//x = r * cos(A) + x0;
	//y = r * sin(A) + y0;

	//v2

	//X = x + (r/2)*cos(angle);
	//Y = y + (r/2)*sin(angle);
	t_z = (500 * cos(-(angle/100))) + 512;
	t_y = (500 * sin(-(angle/100))) + 100;

	glFlush();
	materials(&noMaterials);
}

void Sun::ToggleSpeed()
{
	if(stepSize==smallStep)
	{
		stepSize = bigStep;
	}
	else
	{
		stepSize = smallStep;
	}
}

void Sun::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	//Refresh();
}

void Sun::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}


int Sun::GetCurrentX()
{
    return m_x;
}

int Sun::GetCurrentY()
{
    return t_y;
}

int Sun::GetCurrentZ()
{
    return t_z;
}


void Sun::Rotate()
{
	//rotate animation

	Refresh();
}