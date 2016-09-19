#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct GLintPoint {
	GLint x;
	GLint y;
} GLintPoint;

const int screenWidth = 800;
const int screenHeight = 800;

void paramHouse (GLintPoint peak, GLint width, GLint height, float r, float g, float b) {
	
	//Shell
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);

	glVertex2i(peak.x, peak.y); //peak point

	glVertex2i(peak.x+width/2, peak.y-3*height/8); //top right
	glVertex2i(peak.x+width/2, peak.y-height); //bottom right
	
	glVertex2i(peak.x-width/2, peak.y-height); //order important
	glVertex2i(peak.x-width/2, peak.y-3*height/8);

	glEnd();
	glFlush();

	//Door
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);

	glVertex2i(peak.x, peak.y-height);
	glVertex2i(peak.x, peak.y-3*height/4);
	glVertex2i(peak.x-width/6, peak.y-3*height/4);
	glVertex2i(peak.x-width/6, peak.y-height);

	glEnd();
	glFlush();

	//window
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);

	glVertex2i(peak.x+width/3, peak.y-3*height/8);
	glVertex2i(peak.x+width/6, peak.y-3*height/8);
	glVertex2i(peak.x+width/6, peak.y-5*height/9);
	glVertex2i(peak.x+width/3, peak.y-5*height/9);

	glEnd();
	glFlush();

	//chimney
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);

	glVertex2i(peak.x-width/3, peak.y-3*height/8);
	glVertex2i(peak.x-width/6, peak.y-3*height/8);
	glVertex2i(peak.x-width/6, peak.y+height/32);
	glVertex2i(peak.x-width/3, peak.y+height/32);

	glEnd();
	glFlush();

}

void house1 (void) {
	GLintPoint p;
	p.x = 200;
	p.y = 200;

	paramHouse(p,100,150, 1, 0, 0); //red house

}

void myInit (void) {
	glClearColor(1.0,1.0,1.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

int main (int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Parameterized House");

	glutDisplayFunc(house1);

	myInit();
	glutMainLoop();
}