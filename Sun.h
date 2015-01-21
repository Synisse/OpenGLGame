#ifndef __SUN_H__
#define __SUN_H__

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

class Sun
{
public:
	Sun() { Init(); }
	~Sun(){}

	void Init();
	void Refresh();
	void SetPos(float x, float y, float z);
    void GetPos(float &x, float &y, float &z);
	int GetCurrentX(void);
	int GetCurrentY(void);
	int GetCurrentZ(void);

	// Navigation
	void Rotate(void);

	void ToggleSpeed(void);

private:
	float m_x, m_y, m_z;   // Position
	float t_x, t_y, t_z;
};

#endif
