#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Helicamera.h"

void Helicamera::Init()
{
	//angle on y-axis
	m_yaw = 51.88;
	//angle on x-axis
	m_pitch = -1.553;

	//startposition
	SetPos(100, 500, 100);
}

void Helicamera::Refresh()
{
	// Camera parameter according to Riegl's co-ordinate system
	// x/y for flat, z for height
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//std::cout << "Current position( x" << xpos<< ", y" << ypos << ", z" << zpos << " );" << std::endl;
	gluLookAt(m_x, m_y, m_z, m_x + m_lx, m_y + m_ly, m_z + m_lz, 0.0,1.0,0.0);

	//printf("Camera: %f %f %f Direction vector: %f %f %f\n", m_x, m_y, m_z, m_lx, m_ly, m_lz);
}

void Helicamera::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	Refresh();
}

void Helicamera::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

void Helicamera::GetDirectionVector(float &x, float &y, float &z)
{
    x = m_lx;
    y = m_ly;
    z = m_lz;
}

int Helicamera::GetCurrentX()
{
	printf("x %06.3f -- y %06.3f -- z %06.3f\n",m_x,m_y,m_z);
    return m_x;
}

int Helicamera::GetCurrentZ()
{
    return m_z;
}


void Helicamera::Move(float incr)
{
    float lx = cos(m_yaw)*cos(m_pitch);
    float ly = sin(m_pitch);
    float lz = sin(m_yaw)*cos(m_pitch);

	m_x = m_x + incr*lx;
	m_y = m_y + incr*ly;
	m_z = m_z + incr*lz;

	Refresh();
}

void Helicamera::Strafe(float incr)
{
	m_x = m_x + incr*m_strafe_lx;
	m_z = m_z + incr*m_strafe_lz;

	Refresh();
}

void Helicamera::Fly(float incr)
{
	m_y = m_y + incr;

	Refresh();
}

void Helicamera::RotateYaw(float angle)
{
	/*m_yaw += angle;*/

	Refresh();
}

void Helicamera::RotatePitch(float angle)
{
 //   const float limit = 89.0 * M_PI / 180.0;

	//m_pitch -= angle;

 //   if(m_pitch < -limit)
 //       m_pitch = -limit;

 //   if(m_pitch > limit)
 //       m_pitch = limit;

	Refresh();
}

void Helicamera::SetYaw(float angle)
{
	m_yaw = angle;

	Refresh();
}

void Helicamera::SetPitch(float angle)
{
    m_pitch = angle;

    Refresh();
}
