#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Camera.h"

void Camera::Init()
{
	//angle on y-axis
	m_yaw = 45.0;
	//angle on x-axis
	m_pitch = -0.1;

	//startposition
	SetPos(5, 250, 5);
}

void Camera::Refresh()
{
	// Camera parameter according to Riegl's co-ordinate system
	// x/y for flat, z for height

	printf("yaw %06.3f -- pitch %06.3f\n",m_yaw,m_pitch);

	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//std::cout << "Current position( x" << xpos<< ", y" << ypos << ", z" << zpos << " );" << std::endl;
	gluLookAt(m_x, m_y, m_z, m_x + m_lx, m_y + m_ly, m_z + m_lz, 0.0,1.0,0.0);
	
}

void Camera::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	Refresh();
}

void Camera::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

void Camera::GetDirectionVector(float &x, float &y, float &z)
{
    x = m_lx;
    y = m_ly;
    z = m_lz;
}

float Camera::GetCurrentX()
{
	//printf("x %06.3f -- y %06.3f -- z %06.3f\n",m_x,m_y,m_z);
    return m_x;
}

float Camera::GetCurrentY()
{
    return m_y;
}

float Camera::GetCurrentZ()
{
    return m_z;
}

void Camera::SetCurrentY(float y)
{
    m_y = y;
}

void Camera::Move(float incr)
{
    float lx = cos(m_yaw)*cos(m_pitch);
    float ly = sin(m_pitch);
    float lz = sin(m_yaw)*cos(m_pitch);

	m_x = m_x + incr*lx;
	m_y = m_y + incr*ly;
	m_z = m_z + incr*lz;

	Refresh();
}

void Camera::Strafe(float incr)
{
	m_x = m_x + incr*m_strafe_lx;
	m_z = m_z + incr*m_strafe_lz;

	Refresh();
}

void Camera::Fly(float incr)
{
	m_y = m_y + incr;

	Refresh();
}

void Camera::RotateYaw(float angle)
{
	m_yaw += angle;

	Refresh();
}

void Camera::RotatePitch(float angle)
{
    const float limit = 89.0 * M_PI / 180.0;

	m_pitch -= angle;

    if(m_pitch < -limit)
        m_pitch = -limit;

    if(m_pitch > limit)
        m_pitch = limit;

	Refresh();
}

void Camera::SetYaw(float angle)
{
	m_yaw = angle;

	Refresh();
}

void Camera::SetPitch(float angle)
{
    m_pitch = angle;

    Refresh();
}

float Camera::GetYaw()
{
	return m_yaw;
}

float Camera::GetPitch()
{
    return m_pitch;
}