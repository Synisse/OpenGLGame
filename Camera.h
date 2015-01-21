#ifndef __CAMERA_H__
#define __CAMERA_H__

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

class Camera
{
public:
	Camera() { Init(); }
	~Camera(){}

	void Init();
	void Refresh();
	void SetPos(float x, float y, float z);
    void GetPos(float &x, float &y, float &z);
	float GetCurrentX(void);
	float GetCurrentY(void);
	float GetCurrentZ(void);
	void SetCurrentY(float y);
	float GetPitch(void);
	float GetYaw(void);
    void GetDirectionVector(float &x, float &y, float &z);
	void SetYaw(float angle);
	void SetPitch(float angle);

	// Navigation
	void Move(float incr);
	void Strafe(float incr);
	void Fly(float incr);
	void RotateYaw(float angle);
	void RotatePitch(float angle);

private:
	float m_x, m_y, m_z;   // Position
    float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
	float m_yaw, m_pitch; // Various rotation angles
	float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector
};

#endif