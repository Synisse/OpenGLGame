#include <GL/glut.h>
#include "material.h"

materialStruct brassMaterials = {
    {0.33, 0.22, 0.03, 1.0},
    {0.78, 0.57, 0.11, 1.0},
    {0.99, 0.91, 0.81, 1.0},
    27.8
};

materialStruct redPlasticMaterials = {
    {0.3, 0.0, 0.0, 1.0},
    {0.6, 0.0, 0.0, 1.0},
    {0.8, 0.6, 0.6, 1.0},
    32.0
};

materialStruct whiteShineyMaterials = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    100
};

materialStruct noMaterials = {
    {0.2, 0.2, 0.2, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 0.0},
    0
};

materialStruct BronzeMaterials = {
    {0.212500, 0.127500, 0.054000, 1.000000},
    {0.714000, 0.428400, 0.181440, 1.000000},
    {0.393548, 0.271906, 0.166721, 1.000000},
    25.600000
};

materialStruct Polished_BronzeMaterials = {
    {0.250000, 0.148000, 0.064750, 1.000000},
    {0.400000, 0.236800, 0.103600, 1.000000},
    {0.774597, 0.458561, 0.200621, 1.000000},
    76.800003
};

materialStruct ChromeMaterials = {
    {0.250000, 0.250000, 0.250000, 1.000000},
    {0.400000, 0.400000, 0.400000, 1.000000},
    {0.774597, 0.774597, 0.774597, 1.000000},
    76.800003
};

materialStruct CopperMaterials = {
    {0.191250, 0.073500, 0.022500, 1.000000},
    {0.703800, 0.270480, 0.082800, 1.000000},
    {0.256777, 0.137622, 0.086014, 1.000000},
    12.800000
};

materialStruct Polished_CopperMaterials = {
    {0.229500, 0.088250, 0.027500, 1.000000},
    {0.550800, 0.211800, 0.066000, 1.000000},
    {0.580594, 0.223257, 0.069570, 1.000000},
    51.200001
};

materialStruct GoldMaterials = {
    {0.247250, 0.199500, 0.074500, 1.000000},
    {0.751640, 0.606480, 0.226480, 1.000000},
    {0.628281, 0.555802, 0.366065, 1.000000},
    51.200001
};

materialStruct Polished_GoldMaterials = {
    {0.247250, 0.224500, 0.064500, 1.000000},
    {0.346150, 0.314300, 0.090300, 1.000000},
    {0.797357, 0.723991, 0.208006, 1.000000},
    83.199997
};

materialStruct PewterMaterials = {
    {0.105882, 0.058824, 0.113725, 1.000000},
    {0.427451, 0.470588, 0.541176, 1.000000},
    {0.333333, 0.333333, 0.521569, 1.000000},
    9.846150
};

materialStruct SilverMaterials = {
    {0.192250, 0.192250, 0.192250, 1.000000},
    {0.507540, 0.507540, 0.507540, 1.000000},
    {0.508273, 0.508273, 0.508273, 1.000000},
    51.200001
};

materialStruct Polished_SilverMaterials = {
    {0.231250, 0.231250, 0.231250, 1.000000},
    {0.277500, 0.277500, 0.277500, 1.000000},
    {0.773911, 0.773911, 0.773911, 1.000000},
    89.599998
};

materialStruct EmeraldMaterials = {
    {0.021500, 0.174500, 0.021500, 0.550000},
    {0.075680, 0.614240, 0.075680, 0.550000},
    {0.633000, 0.727811, 0.633000, 0.550000},
    76.800003
};

materialStruct JadeMaterials = {
    {0.135000, 0.222500, 0.157500, 0.950000},
    {0.540000, 0.890000, 0.630000, 0.950000},
    {0.316228, 0.316228, 0.316228, 0.950000},
    12.800000
};

materialStruct ObsidianMaterials = {
    {0.053750, 0.050000, 0.066250, 0.820000},
    {0.182750, 0.170000, 0.225250, 0.820000},
    {0.332741, 0.328634, 0.346435, 0.820000},
    38.400002
};

materialStruct PearlMaterials = {
    {0.250000, 0.207250, 0.207250, 0.922000},
    {1.000000, 0.829000, 0.829000, 0.922000},
    {0.296648, 0.296648, 0.296648, 0.922000},
    11.264000
};

materialStruct RubyMaterials = {
    {0.174500, 0.011750, 0.011750, 0.550000},
    {0.614240, 0.041360, 0.041360, 0.550000},
    {0.727811, 0.626959, 0.626959, 0.550000},
    76.800003
};

materialStruct TurquoiseMaterials = {
    {0.100000, 0.187250, 0.174500, 0.800000},
    {0.396000, 0.741510, 0.691020, 0.800000},
    {0.297254, 0.308290, 0.306678, 0.800000},
    12.800000
};

materialStruct Black_PlasticMaterials = {
    {0.000000, 0.000000, 0.000000, 1.000000},
    {0.010000, 0.010000, 0.010000, 1.000000},
    {0.500000, 0.500000, 0.500000, 1.000000},
    32.000000
};

materialStruct Black_RubberMaterials = {
    {0.020000, 0.020000, 0.020000, 1.000000},
    {0.010000, 0.010000, 0.010000, 1.000000},
    {0.400000, 0.400000, 0.400000, 1.000000},
    10.000000
};

GLfloat diffuse0[] = {1.0, 1.0, 1.0, 1.0};
GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};
GLfloat ambient0[] = {0.2, 0.2, 0.2, 1.0};

GLfloat ambient1[] = {0.0, 0.0, 0.2, 1.0}; //low ambient light
GLfloat diffuse1[] = {1.0, 1.0, 1.0, 1.0}; // full white
GLfloat spotDirection1[] = {0.0, -1.0, -1.0};
GLfloat spotAngle1 = 40.0; // angle is 0 to 180
GLfloat spotExponent1 = 0.0; // exponent is 0 to 128

void light0(GLfloat light_pos[]) {
	//glEnable(GL_LIGHT0);

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	//glEnable(GL_NORMALIZE);
}

void light1(GLfloat light_pos[]) {
	//glEnable(GL_LIGHT1);

	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);    
	//glLightfv(GL_LIGHT1, GL_POSITION, light_pos);    
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection1);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle1); // set cutoff angle
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent1); // set focusing strength

	//glEnable(GL_NORMALIZE);
}

// front_back: GL_FRONT_AND_BACK, GL_BACK, GL_FRONT

void materials(GLint front_back, materialStruct *materials) {
	glMaterialfv(front_back, GL_AMBIENT, materials->ambient);
	glMaterialfv(front_back, GL_DIFFUSE, materials->diffuse);
	glMaterialfv(front_back, GL_SPECULAR, materials->specular);
	glMaterialf(front_back, GL_SHININESS, materials->shininess);
}
void materials(materialStruct *material){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess);
}
