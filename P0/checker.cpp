#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int screenWidth = 800;
const int screenHeight = 800;

float r1;
float g1;
float b1;

float r2;
float g2;
float b2;

void checkerboard() {

    int i, j;
	bool color1 = true;

	glClear(GL_COLOR_BUFFER_BIT);

	for(i=0; i<800; i+=100) {

		for(j=0; j<800; j+=100) {

			if(color1 == true) {
				glColor3f(r1,g1,b1);
				glRecti(j,i,j+100,i+100);
				color1 = false; //alternate colors
			}
			else {
				glColor3f(r2,g2,b2);
				glRecti(j,i,j+100,i+100);
				color1 = true; //alternate colors
			}
		}

		/* alternate colors for next row */
		if (color1 == true)
			color1 = false;
		else
			color1 = true;
	}

	glFlush();
}

/*
function that randomly generates a floating value from 0.0 to max)
*/
float floating_rand(float max) {

	float num = (float)rand() / (float)(RAND_MAX/max);
	return num;
}

void myInit(void) {

	glClearColor(1.0,1.0,1.0,0.0);

	//initialize the two colors
    r1 = floating_rand(1.0);
    g1 = floating_rand(1.0);
    b1 = floating_rand(1.0);

    r2 = floating_rand(1.0);
    g2 = floating_rand(1.0);
    b2 = floating_rand(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)screenWidth,0.0,(GLdouble)screenHeight);

}

int main (int argc, char *argv[]) {

	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(screenWidth,screenHeight);
	glutCreateWindow("Checker Board");

	glutDisplayFunc(checkerboard);

	myInit();
	glutMainLoop();
}