#include <gl\glut.h>
//Klasse für die verschiedenen Materialien
#ifndef _MATERIAL_H_INCLUDED
#define _MATERIAL_H_INCLUDED

typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

extern materialStruct brassMaterials;
extern materialStruct redPlasticMaterials;
extern materialStruct whiteShineyMaterials;
extern materialStruct noMaterials;

extern materialStruct BrassMaterials;
extern materialStruct BronzeMaterials;
extern materialStruct Polished_BronzeMaterials;
extern materialStruct ChromeMaterials;
extern materialStruct CopperMaterials;
extern materialStruct Polished_CopperMaterials;
extern materialStruct GoldMaterials;
extern materialStruct Polished_GoldMaterials;
extern materialStruct PewterMaterials;
extern materialStruct SilverMaterials;
extern materialStruct Polished_SilverMaterials;
extern materialStruct EmeraldMaterials;
extern materialStruct JadeMaterials;
extern materialStruct ObsidianMaterials;
extern materialStruct PearlMaterials;
extern materialStruct RubyMaterials;
extern materialStruct TurquoiseMaterials;
extern materialStruct Black_PlasticMaterials;
extern materialStruct Black_RubberMaterials;


extern GLfloat diffuse0[];
extern GLfloat specular0[];
extern GLfloat ambient0[];

void materials(GLint front_back, materialStruct *materials);
void materials(materialStruct *materials);
void light0(GLfloat light_pos[]);
void light1(GLfloat light_pos[]);

#endif

