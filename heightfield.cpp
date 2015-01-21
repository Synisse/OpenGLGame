#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>


#include "jpeg.h"
#include "heightfield.h"

bool SwiftHeightField::Init(void){
	glGenBuffersARB(1, &vhVBOVertices);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 3 * sizeof(float), vhVertices, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBOTexCoords);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 2 * sizeof(float), vhTexCoords, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBONormals);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 3 * sizeof(float), vhNormals, GL_STATIC_DRAW_ARB);

	delete [] vhVertices;
	vhVertices = NULL;

	//delete [] vhTexCoords;
	//vhTexCoords = NULL;

	return true;
}

bool SwiftHeightField::Create(char *hFileName, const int hWidth, const int hHeight){
	hmHeight = hHeight;
	hmWidth = hWidth;

	FILE *fp;

	fp = fopen(hFileName, "rb");

	fread(hHeightField, 1, hWidth * hHeight, fp);

	fclose(fp);

	vhVertexCount = (int)(hmHeight * hHeight * 6) / (hLOD * hLOD);
	vhVertices = new Vert[vhVertexCount];
	vhTexCoords = new TexCoord[vhVertexCount];
	vhNormals = new Norm[vhVertexCount];

	int nIndex = 0;
	float flX;
	float flZ;


	for (int hMapX = 0; hMapX < hmWidth; hMapX+=hLOD){
		for (int hMapZ = 0; hMapZ < hmHeight; hMapZ+=hLOD){
			for (int nTri = 0; nTri < 6; nTri++){
				flX = (float)hMapX + ((nTri == 1 || nTri == 2 || nTri == 5) ? hLOD : 0);
				flZ = (float)hMapZ + ((nTri == 2 || nTri == 4 || nTri == 5) ? hLOD : 0);

				vhVertices[nIndex].x = flX;
				vhVertices[nIndex].y = hHeightField[(int)flX][(int)flZ];
				vhVertices[nIndex].z = flZ;

				vhNormals[nIndex].nx = 0.0;
				vhNormals[nIndex].ny = 1.0;
				vhNormals[nIndex].nz = 0.0;

				vhTexCoords[nIndex].u = flX / 1024;
				vhTexCoords[nIndex].v = flZ / 1024;
				nIndex++;
			}
		}
	}

	SwiftTextureJpeg(tID, "texture.jpg", 0);

	Init();

	return true;
}

int SwiftHeightField::GetHeightOnPosition(int x, int z){
	int testIndex = 0;

	for (int hMapX = 0; hMapX < x; hMapX+=hLOD){
		for (int hMapZ = 0; hMapZ < z; hMapZ+=hLOD){
			for (int nTri = 0; nTri < 6; nTri++){
				testIndex++;
			}
		}
	}
	return (int)vhTexCoords[testIndex].v;
}

void SwiftHeightField::Render(void){
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tID[0]);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);

	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	glNormalPointer(GL_FLOAT,0, (char *) NULL);

//	glEnableClientState(GL_NORMAL_ARRAY);
//	glNormalPointer(GL_FLOAT, sizeof(vhVertices), BUFFER_OFFSET(12));

	glDrawArrays(GL_TRIANGLES, 0, vhVertexCount);

	glDisableClientState(GL_VERTEX_ARRAY);

	glDisableClientState(GL_NORMAL_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}