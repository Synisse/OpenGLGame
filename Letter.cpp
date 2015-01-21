#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Letter.h"
#include "material.h"

GLfloat pos_x = 0, pos_y = 0;

void Letter::Init()
{

	//startposition
	SetPos(400, 270, 400);
}

void Letter::Refresh()
{
	pos_x++;
	pos_y++;
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


glPushMatrix();

glTranslatef(m_x,m_y,m_z);
glRotatef(pos_x, 0.0, 1.0, 0.0);

	//LOL START
	//
	//
	glPushMatrix();
	glTranslatef(1,1,1);
		materials(&redPlasticMaterials);
		glScaled(1.0,5.0,1.0);
		glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1-25,1+10);
		glScaled(1.0,1.0,3.0);
		glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1,1+40);
		glScaled(1.0,5.0,1.0);
		glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1-25,1+50);
		glScaled(1.0,1.0,3.0);
		glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1,1+60);
		glScaled(1.0,5.0,1.0);
		glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1+20,1+50);
		glScaled(1.0,1.0,3.0);
		glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1,1+80);
		materials(&redPlasticMaterials);
		glScaled(1.0,5.0,1.0);
		glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1-25,1+90);
		glScaled(1.0,1.0,3.0);
		glutSolidCube(10);
	glPopMatrix();
	//LOLENDE
glPopMatrix();

glFlush();
materials(&noMaterials);

}

void Letter::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	//Refresh();
}

void Letter::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}


int Letter::GetCurrentX()
{
    return m_x;
}

int Letter::GetCurrentZ()
{
    return m_z;
}


void Letter::Rotate()
{
	//rotate animation

	Refresh();
}