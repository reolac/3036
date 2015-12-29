#include "WindowingSystem.h"


float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

void drawScene(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 1; i < 500; i++)
	{
		red -= .09f;
		green -= .12f;
		blue -= .15f;
		if (red < 0.15) red = 1.0f;
		if (green < 0.15) green = 1.0f;
		if (blue < 0.15) blue = 1.0f;
		glPointSize(5.0f);
		glColor3f(red, green, blue);

		glBegin(GL_POINTS);



		glVertex2i(i, 250);
		i = i + 10;
	}
	glEnd();

	glFlush();
	glutSwapBuffers();

}

void updateScene(int value) {

}

void resize(int w, int h) {

}

void setup(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;
	gluOrtho2D(0, 500, 0, 500);


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