/*
This program allows the User to doodle and draw.
Utilized polyLines and its edge coordinates to trace and
display the User mouse movement.

Coordinates are obtained by the mouse event such as
mouse movement and mouse button clicks. Coordinates  
are then stored in an array and a display function
loops through the indices to connect the points.
*/

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

GLintPoint array[20000];
int index = 0;

/* Displays the points stored in the array */
void myDisplay() {

	glBegin(GL_LINE_STRIP);

	for(int i=0; i<index; i++)
		glVertex2i(array[i].x, array[i].y);

	glEnd();
	glFlush();

	glutSwapBuffers();
}

/* mouse buttons event */
void mouseEvent (int button, int state, GLint mouseX, GLint mouseY) {

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0,1.0,1.0,0.0);
		index = 0; //reset the index
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		index = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		/* store coordinates x and y in the array */
    	array[index].x = mouseX;
    	array[index].y = screenHeight - mouseY - 1;
    	index++;
	}
	
	glutPostRedisplay();
}

/* mouse movement event */
void mouseMoveEv (GLint mouseX, GLint mouseY) {

	/* store coordinates x and y in the array */
	array[index].x = mouseX;
	array[index].y = screenHeight - mouseY - 1;
	index++;
	
	glutPostRedisplay();
}

void myInit () {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(1.0,0.0,0.0);
	//glColor3f(1.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
	glViewport(0,0,screenWidth,screenHeight);
}

int main (int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(screenWidth,screenHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow("free hand");

	myInit();

	glutMouseFunc(mouseEvent); //mouse stuff here
	glutDisplayFunc(myDisplay);
	glutMotionFunc(mouseMoveEv);

	glutMainLoop();
}
