#ifndef __FLOWER_H__
#define __FLOWER_H__
struct Point {
	float x;
	float y;
}; // end Point
class Flower
{
public:
	Flower() { Init(); }
	~Flower(){}

	GLuint object;

	void Init();
	void Refresh();
	void SetPos(float x, float y, float z);
    void GetPos(float &x, float &y, float &z);
	int GetCurrentX(void);
	int GetCurrentZ(void);
	GLuint getObject(void);
	GLuint makeObject(void);

	// Navigation
	void Rotate(void);

private:
	float m_x, m_y, m_z;   // Position
};

#endif
