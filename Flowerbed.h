#ifndef __FLOWERBED_H__
#define __FLOWERBED_H__
#include <gl/glut.h>

class Flowerbed
{
public:
	Flowerbed() { Init(); }
	~Flowerbed(){}

	GLuint object;

	void Init();
	void Refresh();
	void SetPos(float x, float y, float z);
    void GetPos(float &x, float &y, float &z);
	int GetCurrentX(void);
	int GetCurrentZ(void);

	// Navigation
	void Rotate(void);

private:
	float m_x, m_y, m_z;   // Position
};

#endif
