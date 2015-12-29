#include "WindowingSystem.h"

#include "bunny.h"

GLfloat yrot;				// Y Rotation

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };
 
void drawScene(void) {
	static GLfloat color[] = { 0.5, 0.25, 5.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

														// Exercise -----------------------------------------------------------------------------
														// Add code here to enble client state for vertex and normal arrays:
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Specify glNormalPointers and glVertexPointer:
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glVertexPointer(3, GL_FLOAT, 0, &bunny[0]);

	glPushMatrix();
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	// Draw the bunny
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

	//Specify the appropriate function call for glDrawElements here:
	glDrawElements(GL_TRIANGLES, 3 * NUM_TRIANGLES, GL_UNSIGNED_INT,
		&triangles[0]);

	// ----------------------------------------------------------------------------------------

	glPopMatrix();

	// Update the position of the bunny before it is rendered in the next frame:
	yrot += 0.2f;

	// Disable client states:
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);

	glutSwapBuffers();      //swaps the front and back buffers
}

void updateScene() {
	glutPostRedisplay();
}

void resize(int width, int height) {
	if (height == 0)							// Prevent a divide by zero by
	{										  // making height equal one
		height = 1;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);// Reset the current Viewport

	glMatrixMode(GL_PROJECTION);				// Select the Projection Matrix
	glLoadIdentity();							// Reset the Projection Matrix

												// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 2.0f);

	glMatrixMode(GL_MODELVIEW);					// Select the Modelview Matrix
	glLoadIdentity();							// Reset the Modelview Matrix
	gluLookAt(-0.2, 0.11, 0.25, 0, 0.11, 0, 0, 1, 0);
}

void setup(void) {
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Really Nice Perspective Calculations
	glEnable(GL_LIGHTING);

	// Set up  the light
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);	// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);	// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);	// Position The Light
	glEnable(GL_LIGHT0);
}

void keyInput(unsigned char key, int x, int y) {

}

void keySpecial(int key, int x, int y) {

}

void keyUp(unsigned char key, int x, int y) {

}

void keyUpSpecial(int key, int x, int y) {

}

void close(void) {

}