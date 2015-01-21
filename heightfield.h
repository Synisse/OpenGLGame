#include <windows.h>

class Vert{
public:
	float x;
	float y;
	float z;
};

class Norm{
public:
	float nx;
	float ny;
	float nz;
};

class TexCoord{
public:
	float u;
	float v;
};

class SwiftHeightField {
private:
	int hmHeight;
	int hmWidth;

	int vhVertexCount;
	Vert *vhVertices;
	TexCoord *vhTexCoords;
	Norm *vhNormals;

	unsigned int vhVBOVertices;
	unsigned int vhVBOTexCoords;
	unsigned int vhVBONormals;

	unsigned int tID[2];

	int compareArray[1024][1024];

	bool Init(void);

public:
	bool Create(char *hFileName, const int hWidth, const int hHeight);

	void Render(void);

	int GetHeightOnPosition(int x, int z);

	int hLOD;

	BYTE hHeightField[1024][1024];
};