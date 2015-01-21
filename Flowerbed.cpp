#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Flowerbed.h"
#include "material.h"
#include "Flower.h"

GLuint flowers[6];

void Flowerbed::Init()
{

	//startposition
	SetPos(400, 270, 400);
	//object = makeObject();

	for (int i = 0; i < 6; i++)
	{
		Flower flower;
		flower.Init();
		flowers[i] = flower.getObject();
	}
}

void Flowerbed::Refresh()
{
//	glColor3f(1.0, 1.0, 1.0);
//
//glMatrixMode(GL_MODELVIEW);




//glTranslatef(m_x,m_y,m_z);
	glPushMatrix();
	glRotated(55,0.0,1.0,0.0);
	glTranslated(-100,-3,80);
for (int i = 0; i < 6; i++)
{
	if(i%2 == 0)
	{
	glPushMatrix();
	glTranslated(120+(20*i),200,100);
	glScaled(25,25,25);
	glRotated(180,1.0,0.0,0.0);
	glCallList(flowers[i]);glPopMatrix();
	}
	else
	{	glPushMatrix();
	glTranslated(120+(20*i)-20,200,100);
	glRotated(90,0.0,1.0,0.0);
	glScaled(25,25,25);
	glRotated(180,1.0,0.0,0.0);
	glCallList(flowers[i]);glPopMatrix();
	}
	
}

	glPopMatrix();


glFlush();
materials(&noMaterials);

}

void Flowerbed::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	//Refresh();
}

void Flowerbed::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

int Flowerbed::GetCurrentX()
{
    return m_x;
}

int Flowerbed::GetCurrentZ()
{
    return m_z;
}


void Flowerbed::Rotate()
{
	//rotate animation

	Refresh();
}
//fractal test