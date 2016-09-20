/*
Program that draws a Sierpinski triangle (TriForce) from
3 coordinate points the User pick.  Event triggered by the
left mouse button clicks. Drawing is made up of Dots that are
littered by way of an algorithm.
*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

const int screenWidth = 800;
const int screenHeight = 800;

typedef struct GLintPoint {
	GLint x;
	GLint y;
} GLintPoint;

GLintPoint tri[3];
int corner = 0;

void drawDot (GLint x, GLint y) {

	//draw the dots at the coordinates x and y
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

/* The mouse event function that collects the User coordinates */
void mouseEv (int button, int state, GLint x, GLint y) {

	if (button == GLUT_LEFT_BUTTON &&  state == GLUT_DOWN) {
		tri[corner].x = x;
		tri[corner].y = screenHeight - y - 1;
		corner++;
	}
}

/* Drawing of the Sierpinski gasket */
void sierpinski () {

	glClear(GL_COLOR_BUFFER_BIT);

	//GLintPoint triangle[3] = {{50,50}, {750,50}, {350,600}};

	int i;
	int index = rand()%3;
	//GLintPoint point = triangle[index];
    
    glPointSize(2.0);
	glColor3f(1.0,0.0,0.0);

	if (corner == 3) {
		GLintPoint point = tri[index];
		drawDot(point.x, point.y);

		for (i=0; i<10000; i++) {
		
			index = rand()%3;
			point.x = (point.x + tri[index].x) / 2;
			point.y = (point.y + tri[index].y) / 2;
			drawDot(point.x, point.y);

		}

		corner = 0; //reset
	}

	glFlush();
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
	glutCreateWindow("Sierpinski");

	glutDisplayFunc(sierpinski);
	glutMouseFunc(mouseEv);

	myInit();
	glutMainLoop();
}