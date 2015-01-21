#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

#include <GL/glext.h>

#include <math.h>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include <fstream>
#include <assert.h>

#include "heightfield.h"

#include "Camera.h"
#include "Helicamera.h"
#include "Letter.h"
#include "Sun.h"
#include "material.h"
#include "Gates.h"
#include "Flower.h"
#include "Flowerbed.h"
#include <iostream>

#pragma comment(lib,"glew32.lib")

Camera fps_camera;
Helicamera heli_camera;
Letter letter;
Sun sun;
Gates gatesObj;
Flower flower;
Flowerbed flowerbed;

GLuint texture;
GLuint skytexture;
GLuint startTexture;

int frame = 0;
int time, timebase;

int i = 1;
float _light_position[4];
float _spotlight_position[4];
int angletest = 0;

int cursorX,cursorY;
int selected = 0;

bool landscapeMaterial = false;

int statsSubwindow,mainWindow;
char name[50];
char stdo[50];
char descriptionOne[50];
char descriptionTwo[50];
char lettersHit[50];
char gatesHit[50];
char timePassed[50];
char fps[50];
char heli[50];

bool runstarted = false;
int timer = 0;
int points = 0;
int clicks = 0;
int letters = 0;
int gates = 0;

bool g_key[256];
bool g_shift_down = false;
bool g_fps_mode = false;
bool lighting = false;
bool positionLighting = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

// Movement settings
const float g_translation_speed = 2;
const float g_rotation_speed = M_PI/180*0.2;

float bounce;
float cScale = 1.0;

SwiftHeightField hField;

void gl_select(int x, int y);
void display();


//=====================================================
//
// Function to create a glutBitmapCharacter
//
//=====================================================
void renderBitmapString(float x, float y, float z, void *font, char *string) {
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


//=====================================================
//
// Function to render all lightings (light0, light1)
//
//=====================================================
void renderLighting()
{
glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);

	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	_light_position[0] = sun.GetCurrentX();
	_light_position[1] = sun.GetCurrentY();
	_light_position[2] = sun.GetCurrentZ();
	_light_position[3] = 1.0;

	materials(&GoldMaterials);

	glBegin(GL_POLYGON);

	glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  sun.GetCurrentX()+50, sun.GetCurrentY()+50, sun.GetCurrentZ()+50 );      // P1 is red
	glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  sun.GetCurrentX()+50,  sun.GetCurrentY()+50, sun.GetCurrentZ() );      // P2 is green
	glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( sun.GetCurrentX()+50,  sun.GetCurrentY(), sun.GetCurrentZ() );      // P3 is blue
	glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( sun.GetCurrentX()+50, sun.GetCurrentY(), sun.GetCurrentZ()+50 );      // P4 is purple

	glEnd();

	materials(&noMaterials);

	_spotlight_position[0] = 0.0;
	if(sun.GetCurrentY()>0)
	{
		_spotlight_position[1] = -sun.GetCurrentY();
		if(sun.GetCurrentZ()<512)
		{
			_spotlight_position[2] = 512 - sun.GetCurrentZ();
		}
		else
		{
			_spotlight_position[2] = 512 - sun.GetCurrentZ();
		}

	}
	else
	{
		_spotlight_position[1] = - (512)-(512+sun.GetCurrentY());
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION,_light_position);

	//Light
	GLfloat lightColor0[] = {0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat lightPos0[] = {0.0f, 30.0f, 0.0f, 1};
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT1, GL_POSITION, _light_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, _spotlight_position);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
}

//=====================================================
//
// Resets to perspective projection
//
//=====================================================
void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

//=====================================================
//
// Sets to orthographic projection
//
//=====================================================
void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, 1280, 720, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}


void DrawScene()  
{  
  
    glColor3f(0.7, 0.7, 0.7);  
    glPushMatrix();  
    //glTranslatef(0.0, -1.0, 0.0);  
  
    glBegin(GL_QUADS);  
    glVertex3f(2.0, 0.0, 2.0);  
    glVertex3f(2.0, 0.0, -2.0);  
    glVertex3f(-2.0, 0.0, -2.0);  
    glVertex3f(-2.0, 0.0, 2.0);  
    glEnd();  
  
    glPopMatrix();  
    glColor3f(1.0, 1.0, 1.0);  
    glPushMatrix();  
    glTranslatef(0.0, 0.0, -0.5);  
    glutWireTeapot(1.0);  
    glPopMatrix();  
  
}  


//=====================================================
//
// Draws start and endbutton backcover shields
//
//=====================================================
void drawStartButtonShields()
{
		glLoadName(28);
	glPushMatrix();
	glTranslatef(100,200,302);
	glScaled(1.0,1.0,0.1);
	glutSolidCube(30);
	glPopMatrix();
	glLoadName(35);
	glPushMatrix();
	glTranslatef(297,200,200);
	glScaled(0.1,1.0,1.0);
	glutSolidCube(40);
	glPopMatrix();
}

//=====================================================
//
// Draws the main content of the scene
//
//=====================================================
void drawMainScene()
{
	glLoadName(7);
	letter.Refresh();
	glLoadName(14);
	sun.Refresh();
	glPushMatrix();
	if(landscapeMaterial){
		materials(&brassMaterials);
	}
	glLoadName(21);
	hField.Render();
	materials(&noMaterials);
	glPopMatrix();
	
	drawStartButtonShields();

	glPushMatrix();
	gatesObj.Refresh();
	glPopMatrix();
}

//=====================================================
//
// Checks for all objects hit (computes the action)
//
//=====================================================
void list_hits(GLint hits, GLuint *names)
 {
 	int i;
 
 	/*
 		For each hit in the buffer are allocated 4 bytes:
 		1. Number of hits selected (always one,
 									beacuse when we draw each object
 									we use glLoadName, so we replace the
 									prevous name in the stack)
 		2. Min Z
 		3. Max Z
 		4. Name of the hit (glLoadName)
 	*/
 
 	printf("%d hits:\n", hits);
 
 	for (i = 0; i < hits; i++)
	{
 		printf(	"Number: %d\n"
 				"Min Z: %d\n"
 				"Max Z: %d\n"
 				"Name on stack: %d\n",
 				(GLubyte)names[i * 4],
 				(GLubyte)names[i * 4 + 1],
 				(GLubyte)names[i * 4 + 2],
 				(GLubyte)names[i * 4 + 3]
 				);
		if(((GLubyte)names[i * 4 + 3])==7)
		{
			printf("letter");
			letters++;
			
			points += 5;
		}
		if(((GLubyte)names[i * 4 + 3])==14)
		{
			printf("sun");
		}
		if(((GLubyte)names[i * 4 + 3])==21)
		{
			printf("landscape");
		}
		if(((GLubyte)names[i * 4 + 3])==28)
		{
			printf("stone1");
		}
		if(((GLubyte)names[i * 4 + 3])==35)
		{
			printf("stone2");
		}
		if(((GLubyte)names[i * 4 + 3])==42)
		{
			printf("startbutton");
			runstarted = true;
		}
		if(((GLubyte)names[i * 4 + 3])==49)
		{
			printf("stopbutton");
			runstarted = false;
		}
		if(((GLubyte)names[i * 4 + 3])==56)
		{
			printf("stopbutton");
			gatesObj.SetGatePassed(1);
			gates++;
			points+=200;
		}
		if(((GLubyte)names[i * 4 + 3])==63)
		{
			printf("stopbutton");
			gatesObj.SetGatePassed(2);
			gates++;
			points+=200;
		}
		if(((GLubyte)names[i * 4 + 3])==70)
		{
			printf("stopbutton");
			gatesObj.SetGatePassed(3);
			gates++;
			points+=200;
		}
		if(((GLubyte)names[i * 4 + 3])==77)
		{
			printf("stopbutton");
			gatesObj.SetGatePassed(4);
			gates++;
			points+=200;
		}
	}
 	printf("\n");
 }

//=====================================================
//
// Sets the selection mode
//
//=====================================================
void gl_select(int x, int y)
 {
 	GLuint buff[64] = {0};
 	GLint hits, view[4];
 	int id;
 	glSelectBuffer(64, buff);
 
 	glGetIntegerv(GL_VIEWPORT, view);
 
 	glRenderMode(GL_SELECT);
 
 	glInitNames();
 
 	glPushName(0);
 
 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
 		glLoadIdentity();
 
 		gluPickMatrix(x, y, 1.0, 1.0, view);
 		gluPerspective(60, 1.0, 0.0001, 1000.0);
 
 		glMatrixMode(GL_MODELVIEW);
 
 		glutSwapBuffers();
 		display();
 
 		glMatrixMode(GL_PROJECTION);
 	glPopMatrix();
 
 
 	hits = glRenderMode(GL_RENDER);
 
 	
 	list_hits(hits, buff);
 
 	glMatrixMode(GL_MODELVIEW);
 }
 

//=====================================================
//
// Selects all object hit
//
//=====================================================
 void gl_selall(GLint hits, GLuint *buff)
 {
 	GLuint *p;
 	int i;
 
 	display();
 
 	p = buff;
 	for (i = 0; i < 6 * 4; i++)
 	{
 		printf("Slot %d: - Value: %d\n", i, p[i]);
 	}
 
 	printf("Buff size: %x\n", (GLbyte)buff[0]);
 }


//=====================================================
//
// Loads the given texture
//
//=====================================================
 GLuint LoadTexture( const char * filename, int width, int 
height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture );

    glBindTexture( GL_TEXTURE_2D, texture ); 

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 
GL_MODULATE ); 

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
 GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
 GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 
GL_REPEAT );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
 GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data );
    return texture;
}

 //=====================================================
//
// Deletes the texture
//
//=====================================================
void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture ); 
}

void square (void) {
    glBindTexture( GL_TEXTURE_2D, texture );
    glRotatef( angletest, 1.0f, 1.0f, 1.0f );
    glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0,0.0); glVertex2d(+1.0,-1.0);
    glTexCoord2d(1.0,1.0); glVertex2d(+1.0,+1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0,+1.0);
    glEnd();
}

//=====================================================
//
// Draws the gun that is attached to the camera projection
//
//=====================================================
void drawGun()
{

	glPushMatrix();

    glBindTexture( GL_TEXTURE_2D, texture );

	glTranslatef(7,-4,-10);
	glRotatef(-50,0.0,1.0,0.0);
	glRotatef(-20,0.0,0.0,1.0);
	

	//lauf	
	glBegin (GL_QUADS);

	glTexCoord2d(0.0,0.0);
	glVertex2d(-6.0,0.0);

	glTexCoord2d(1.0,0.0); 
	glVertex2d(+1.0,0.0);

	glTexCoord2d(1.0,1.0); 
	glVertex2d(+1.0,+1.0);

	glTexCoord2d(0.0,1.0); 
	glVertex2d(-6.0,+1.0);

	glEnd();

	//griff
	glBegin (GL_QUADS);

	glTexCoord2d(0.0,0.0);
	glVertex2d(-1.0,-3.0);

	glTexCoord2d(1.0,0.0); 
	glVertex2d(0.0,-3.0);

	glTexCoord2d(1.0,1.0); 
	glVertex2d(0.0,0.0);

	glTexCoord2d(0.0,1.0); 
	glVertex2d(-1.0,0.0);

	glEnd();

	//abzug
	glBegin (GL_QUADS);

	glTexCoord2d(0.0,0.0);
	glVertex2d(-1.8,-1.0);

	glTexCoord2d(1.0,0.0); 
	glVertex2d(-1.5,-1.0);

	glTexCoord2d(1.0,1.0); 
	glVertex2d(-1.5,0.0);

	glTexCoord2d(0.0,1.0); 
	glVertex2d(-1.8,0.0);

	glEnd();

	glPopMatrix();
}


//=====================================================
//
// Draws the skybox
//
//=====================================================
void drawAroundPlanetGrid(double radius, int overSample, int numStrips, int numQuads, float radiusRatio)
{

double b = radius * 0.9966463577;//Geoid's semi-minor axis
double e2 = 0.0067; //Geoid's squared eccentricity, derived from flattening factor

float texY1=float(0)/float(numStrips);
double lat1=(M_PI*double(0))/double(numStrips)-0.5*M_PI;
double s1=sin(lat1);
double c1=cos(lat1);
double chi1=sqrt(1.0-e2*s1*s1);
double xy1=radius*radiusRatio/chi1*c1;
double z1=radius*(1.0-e2)/chi1*s1;

//* Draw latitude quad strips: *
for(int i=1;i<numStrips+1;++i)
    {
    float texY0=texY1;
    double s0=s1;
    double c0=c1;
    double xy0=xy1;
    double z0=z1;
    texY1=float(i)/float(numStrips);
	lat1=(M_PI*double(i))/double(numStrips)-0.5*M_PI;
    s1=sin(lat1);
    c1=cos(lat1);
    chi1=sqrt(1.0-e2*s1*s1);
    xy1=radius/chi1*c1;
    z1=radius*(1.0-e2)/chi1*s1;

    glBegin(GL_QUAD_STRIP);
    for(int j=0;j<=numQuads;++j)
    {
    float texX=float(j)/float(numQuads)+0.5f;
	double lng=(2.0*M_PI*double(j))/double(numQuads);
    double cl=cos(lng)*radiusRatio;
    double sl=sin(lng)*radiusRatio;

    glTexCoord2f(texX,texY1);
    glNormal3d(c1*cl,c1*sl,s1);
    glVertex3d(xy1*cl,xy1*sl,z1);

    glTexCoord2f(texX,texY0);
    glNormal3d(c0*cl,c0*sl,s0);
    glVertex3d(xy0*cl,xy0*sl,z0);
    }
    glEnd();
    }
}

//=====================================================
//
// Draws start and endbutton
//
//=====================================================
void drawStartButton()
{
	glLoadName(42);
	startTexture = LoadTexture("timerstart.raw", 256,256);
	glPushMatrix();
	glTranslated(100,200,300);
	glRotated(180,1.0,0.0,0.0);
	glRotated(180,0.0,1.0,0.0);
	glScaled(10,10,1);
	glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0,0.0); glVertex2d(+1.0,-1.0);
    glTexCoord2d(1.0,1.0); glVertex2d(+1.0,+1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0,+1.0);
    glEnd();
	glPopMatrix();
	FreeTexture(startTexture);

	glLoadName(49);
	startTexture = LoadTexture("timerstop.raw", 256,256);
	glPushMatrix();
	glTranslated(300,200,200);
	glRotated(180,1.0,0.0,0.0);
	glRotated(270,0.0,1.0,0.0);
	glScaled(10,10,1);
	glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0,0.0); glVertex2d(+1.0,-1.0);
    glTexCoord2d(1.0,1.0); glVertex2d(+1.0,+1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0,+1.0);
    glEnd();
	glPopMatrix();
	FreeTexture(startTexture);
}

//=====================================================
//
// Display function that draw all the content
// containing allviewports
//
//=====================================================
void display (void) {

	//heli window
	glViewport(0, 0, 512, 288);
	float placeholderYaw = fps_camera.GetYaw();
	float placeholderPitch = fps_camera.GetPitch();
	float placeholderY = fps_camera.GetCurrentY();
		fps_camera.SetCurrentY(placeholderY+70);
	fps_camera.SetYaw(51.88);
	fps_camera.SetPitch(-1.553);

	drawMainScene();
	glTranslatef(fps_camera.GetCurrentX(),placeholderY,fps_camera.GetCurrentZ());
	glutSolidSphere(1,16,16);
	//stats window
	glViewport(0,288,512,432);
	char c[50];

	sprintf(c,"Clicks: %d", clicks);
	sprintf(lettersHit,"Letter hits: %d", letters);
	sprintf(name,"Playername: Stefan");
	sprintf(stdo,"Points: %d", points);
	sprintf(descriptionOne,"Shoot all gates in the right order!");
	sprintf(descriptionTwo,"Dont forget to start the timer!");
	sprintf(timePassed,"Timer: %d0 ms" , timer);
	sprintf(gatesHit,"Gates passed: %d", gates);
	sprintf(heli,"Helicoper View");
	
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(fps,"FPS:%4.2f",
			frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
	}
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	materials(&whiteShineyMaterials);
	renderBitmapString(5,50,0,GLUT_BITMAP_HELVETICA_18,name);
	renderBitmapString(5,110,0,GLUT_BITMAP_HELVETICA_18,descriptionOne);
	renderBitmapString(5,140,0,GLUT_BITMAP_HELVETICA_18,descriptionTwo);
	renderBitmapString(5,170,0,GLUT_BITMAP_HELVETICA_12, c);
	renderBitmapString(5,200,0,GLUT_BITMAP_HELVETICA_12, lettersHit);
	renderBitmapString(500,50,0,GLUT_BITMAP_HELVETICA_18, fps);
	renderBitmapString(5,230,0,GLUT_BITMAP_HELVETICA_12, gatesHit);
	renderBitmapString(5,290,0,GLUT_BITMAP_HELVETICA_18,stdo);

	renderBitmapString(5,340,0,GLUT_BITMAP_HELVETICA_18, timePassed);

	renderBitmapString(5,700,0,GLUT_BITMAP_HELVETICA_18, heli);
	materials(&noMaterials);
	glPopMatrix();

	restorePerspectiveProjection();
	fps_camera.SetYaw(placeholderYaw);
	fps_camera.SetPitch(placeholderPitch);
	fps_camera.SetCurrentY(placeholderY);
	glutSwapBuffers();
	angletest++;

		//main window
	glViewport(512, 0, 1280, 720);
	glutSetWindow(mainWindow);
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  
	glEnable( GL_TEXTURE_2D );
	drawGun();

	fps_camera.Refresh();
	//drawGun();
	glPushMatrix();
	square();
	glPopMatrix();
	skytexture = LoadTexture("sky.raw", 1000,667);
	glPushMatrix();
	glTranslated(512,100,512);
	glScaled(50,50,50);
	drawAroundPlanetGrid(20,5,16,16,1);
	glPopMatrix();
	FreeTexture(skytexture);
		//startbutton
	drawStartButton();
	glDisable( GL_TEXTURE_2D);
	drawMainScene();

	flowerbed.Refresh();
	renderLighting();
}



//=====================================================
//
// Initializes all buffers for the heightmap creation
//
//=====================================================
void initExtensions(void){
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
}

//=====================================================
//
// init function that creates the heightmap
//
//=====================================================
void Init (void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	initExtensions();

	hField.hLOD = 8;

	hField.Create("heightField.raw", 1024, 1024);

	flower.Init();
	flowerbed.Init();
}


//=====================================================
//
// Creates the exit call, aswell as sets the fps mode (space)
//
//=====================================================
void Keyboard(unsigned char key, int x, int y)
{
	if(key == 27) {
		exit(0);
	}

	if(key == ' ') {
		g_fps_mode = !g_fps_mode;

		if(g_fps_mode) {
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
			glutWarpPointer(g_viewport_width/2, g_viewport_height/2);
		}
		else {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}

	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		g_shift_down = true;
	}
	else {
		g_shift_down = false;
	}

	g_key[key] = true;
}

//=====================================================
//
// Keyboard up event, to stop movement
//
//=====================================================
void KeyboardUp(unsigned char key, int x, int y)
{
	g_key[key] = false;
}

//=====================================================
//
// Timer function
//
//=====================================================
void Timer(int value)
{
	if(g_fps_mode) {
		if(g_key['w'] || g_key['W']) {
			//std::cout << "Terrain at( y" << hField.GetHeightOnPosition(fps_camera.GetCurrentX(), fps_camera.GetCurrentZ()) << std::endl;
			fps_camera.Move(g_translation_speed);
			heli_camera.Move(g_translation_speed);
		}
		else if(g_key['s'] || g_key['S']) {
			fps_camera.Move(-g_translation_speed);
			heli_camera.Move(-g_translation_speed);
		}
		else if(g_key['a'] || g_key['A']) {
			fps_camera.Strafe(g_translation_speed);
			heli_camera.Strafe(g_translation_speed);
		}
		else if(g_key['d'] || g_key['D']) {
			fps_camera.Strafe(-g_translation_speed);
			heli_camera.Strafe(-g_translation_speed);
		}
		else if(g_key['l'] || g_key['L']) {

		}
		//DEPRECATED
		else if(g_mouse_left_down) {
			//fps_camera.Fly(-g_translation_speed);
		}
		else if(g_mouse_right_down) {
			//fps_camera.Fly(g_translation_speed);
		}
	}
	
	if(runstarted)
	{
		timer++;
	}

	glutTimerFunc(1, Timer, 0);
}


//=====================================================
//
// Idle function
//
//=====================================================
void Idle()
{
	display();
}

//=====================================================
//
// Mouseevents
//
//=====================================================
void Mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) {
		if(button == GLUT_LEFT_BUTTON) {
				cursorX = x;
				cursorY = y;

				gl_select(cursorX,cursorY);

			clicks++;

			g_mouse_left_down = true;
		}
		else if(button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = true;
		}
	}
	else if(state == GLUT_UP) {
		if(button == GLUT_LEFT_BUTTON) {
			g_mouse_left_down = false;
		}
		else if(button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = false;
		}
	}
}

//=====================================================
//
// Mouse motion for smooth mouse movement
//
//=====================================================
void MouseMotion(int x, int y)
{
	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
	// This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

	if(just_warped) {
		just_warped = false;
		return;
	}

	if(g_fps_mode) {
		int dx = x - (g_viewport_width/2+256);
		int dy = y - (g_viewport_height/2);

		if(dx) {
			fps_camera.RotateYaw(g_rotation_speed*dx);
		}

		if(dy) {
			fps_camera.RotatePitch(g_rotation_speed*dy);
		}

		glutWarpPointer(g_viewport_width/2+256, g_viewport_height/2);

		just_warped = true;
	}
}

//=====================================================
//
// Init the projection, viewport and perspective
//
//=====================================================
void reshape (int w, int h) {

	g_viewport_width = w;
	g_viewport_height = h;

	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1800.0);
	glMatrixMode (GL_MODELVIEW);
}

//=====================================================
//
// Enum for all menu entries
//
//=====================================================
enum MENU_TYPE
{
	MENU_SUN,
	MENU_LIGHTING,
	MENU_LIGHTINGTWO,
	MENU_MATERIAL,
};

//MENU_TYPE show = MENU_MATERIAL;

//=====================================================
//
// Picks a menu option
//
//=====================================================
void menu(int item)
{
	switch (item)
	{
	case MENU_SUN: 
		{ 
			sun.ToggleSpeed(); 
		}
		break;
	case MENU_LIGHTING:
		{
			lighting = !lighting;
			if(!lighting){
				glDisable(GL_LIGHT0);
			}
			else
			{
				glEnable(GL_LIGHT0);
			}
		}
		break;
	case MENU_LIGHTINGTWO:
		{
			positionLighting = !positionLighting;
			if(!positionLighting){
				glDisable(GL_LIGHT1);
			}
			else
			{
				glEnable(GL_LIGHT1);
			}
		}
		break;
	case MENU_MATERIAL:
		{
			landscapeMaterial = !landscapeMaterial;
		}
		break;
	default:
		{}
		break;
	}

	glutPostRedisplay();

	return;
}

//=====================================================
//
// main
//
//=====================================================
int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(1792, 720);
	glutInitWindowPosition(100, 100);
	mainWindow = glutCreateWindow("A basic OpenGL Window");
	Init();

	// Create a menu
	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("Toggle Sun speed", MENU_SUN);
	glutAddMenuEntry("Toggle light 0", MENU_LIGHTING);
	glutAddMenuEntry("Toggle light 1", MENU_LIGHTINGTWO);
	glutAddMenuEntry("Toggle landscape material", MENU_MATERIAL);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	

	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	//glutIdleFunc(renderEveryWindow);
	glutReshapeFunc(reshape);
	//glutIdleFunc(Idle);
		

	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardUpFunc(KeyboardUp);
	glutTimerFunc(1, Timer, 0);
	//FreeTexture(texture);
	texture = LoadTexture("iron.raw",512,320);
	glutMainLoop ();
	FreeTexture(texture);
	return 0;
}