/*
*      We will use this template for all OpenGL examples in ICP3036
*
*      This file must contain your code for:
*           void drawScene(GLvoid);
*           void resize(int w, int h);
*           void setup(void);
*           void keyInput(unsigned char key, int x, int y);
*/

#include "WindowingSystem.h"                // Header File for WindowingSystem.cpp
#include "BMPLoader.h"

using namespace std;

#define MAX_NO_TEXTURES 2

#define CUBE_TEXTURE 0
#define FCUBE_TEXTURE 1

GLuint texture_id[MAX_NO_TEXTURES];

float xrot;
float yrot;
float xspeed;			// X Rotation Speed
float yspeed;			// Y Rotation Speed
float z = -4.0f;		    // Depth Into The Screen

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

GLuint	filter;				// Which Filter To Use
bool	light = TRUE;			// Lighting ON/OFF
bool	lp;					// L Pressed?

							/* This is where you put all your OpenGL drawing commands */
void drawScene(void)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	glPushMatrix();
	glTranslatef(0.0, 0.0, z);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_id[1]);	
	glBegin(GL_QUADS);
	// Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glPopMatrix();
	xrot += xspeed;
	yrot += yspeed;

	glutSwapBuffers();      //swaps the front and back buffers
}

void updateScene(void)
/*
The global idle callback can perform background processing tasks or continuous animation
when window system events are not being received. If enabled, the idle callback is continuously
called when events are not being received.

The amount of computation and rendering done in an idle callback should be minimized to avoid
affecting the program's interactive response. In general, not more than a single frame of
rendering should be done in an idle callback.
*/
{
	glutPostRedisplay(); // activates drawScene callback to refresh the display for contiuous animation
}

/* Initialisation routine - acts like your typical constructor in a Java program. */
void setup(void)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// Type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glEnable(GL_TEXTURE_2D);
	glGenTextures(2, texture_id);

	// Load in the BMP image
	BMPClass bangor;
	BMPLoad("bangor.bmp", bangor);

	BMPClass lena;
	BMPLoad("lena512.bmp", lena);

	// This texture uses a nearest neighbour filter
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bangor.width, bangor.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bangor.bytes);

	// This texture will be better quality as it uses Linear interpolation
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, lena.width, lena.height, 0, GL_RGB, GL_UNSIGNED_BYTE, lena.bytes);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// Position The Light
														//	glEnable(GL_LIGHT1);								// Enable Light One
}

/* Tells the program how to resize your OpenGL Window */
void resize(int width, int height)
{

	if (height == 0)										// Prevent a divide by zero by
	{										            // making height equal one
		height = 1;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);		// Set viewport size to be entire OpenGL window

	glMatrixMode(GL_PROJECTION);						// Select the Projection Matrix
	glLoadIdentity();									// Reset the Projection Matrix
	 
														// Calculate The Aspect Ratio Of The Window
	gluPerspective(80.0f, (GLfloat)width / (GLfloat)height, 1.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);							// Select the Modelview Matrix
	glLoadIdentity();									// Reset the Modelview Matrix
	gluLookAt(0, 0, 30,
		0, 0, 10,
		0.0f, 1.0f, 0.0f);
}

/* Keyboard input processing routine */
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Press escape to exit.
	case 27:
		exit(0);
		break;
	case 'f': // toggle between the two texture filters loaded
		filter += 1;
		if (filter>1) filter = 0;
		break;
	case 'l': // turn light on and off
		lp = TRUE;
		light = !light;
		if (!light) glDisable(GL_LIGHTING);
		else glEnable(GL_LIGHTING);
	default:
		break;
	}
}

void keyUp(unsigned char d_keys, int x, int y)
{
	glutIdleFunc(updateScene);
	switch (d_keys)
	{
	case 'f':
		filter += 1;
		if (filter > 1) filter = 0;
		break;
	default:
		break;
	}
}

void keySpecial(int a_keys, int x, int y)  // Create Special Function (required for arrow keys)
{
	glutIdleFunc(updateScene);
	switch (a_keys) {
	case GLUT_KEY_UP:     // When Up Arrow is Pressed...
		xspeed -= 0.01f;
		break;
	case GLUT_KEY_DOWN:   // When Down Arrow is Pressed...
		xspeed += 0.01f;
		break;
	case GLUT_KEY_RIGHT:  // When Right Arrow is Pressed...
		yspeed += 0.01f;
		break;
	case GLUT_KEY_LEFT:  // When Left Arrow is Pressed...
		yspeed -= 0.01f;
		break;
	case GLUT_KEY_F1:    // When F1 key is Pressed...
		glutFullScreen();
		break;
	case GLUT_KEY_F2:    // When F2 key is Pressed...
		glutReshapeWindow(500, 500);
		break;
	case GLUT_KEY_PAGE_UP:
		z += 0.02;
		break;
	case GLUT_KEY_PAGE_DOWN:
		z -= 0.02;
		break;
	default:
		break;
	}

}