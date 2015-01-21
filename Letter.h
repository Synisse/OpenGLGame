#ifndef __LETTER_H__
#define __LETTER_H__

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

class Letter
{
public:
	Letter() { Init(); }
	~Letter(){}

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
