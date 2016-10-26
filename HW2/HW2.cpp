#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>


enum {SPHERE, TEAPOT, JACK};
enum {YES, NO};
enum {INITIAL, ROTATE, TRANSLATE, SCALE};
enum {MAGENTA, GREEN, BLUE, YELLOW, CYAN, WRAPAROUND};

float cam_theta = 45.0;
float cam_phi = 45.0;


int myShape = SPHERE;
int myColor = MAGENTA;
int SOLID = YES;
int state = INITIAL;


/*axis and its cone */
void axis(double length) {
 	
	glPushMatrix();
	glBegin(GL_LINES);
        glVertex3d(0, 0, 0);	//origin
        glVertex3d(0, 0, length); // along the z-axis
	glEnd();

	glTranslated(0, 0, length -0.2);	//translate the cone
	glutSolidCone(0.04, 0.2, 12, 9);	//the cone
	glPopMatrix();
}

void solidJackPart() {
// draw one axis of the unit jack - a stretched sphere
	glPushMatrix();
	glScaled(0.2,0.2,1.0);
	glutSolidSphere(1,15,15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,1.2); // ball on one end
	glutSolidSphere(0.2,15,15);
	glTranslated(0,0, -2.4);
	glutSolidSphere(0.2,15,15); // ball on the other end
	glPopMatrix();
}

void solidJack() {
// draw a unit jack out of spheroids
	glPushMatrix();
	solidJackPart();
	glRotated(90.0, 0, 1, 0);
	solidJackPart();
	glRotated(90.0, 1,0,0);
	solidJackPart();
	glPopMatrix();
}

void wireJackPart() {
// redraw jack using wire spheres
	glPushMatrix();
	glScaled(0.2,0.2,1.0);
	glutWireSphere(1,15,15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,1.2); // ball on one end
	glutWireSphere(0.2,15,15);
	glTranslated(0,0, -2.4);
	glutWireSphere(0.2,15,15); // ball on the other end
	glPopMatrix();
}

void wireJack() {
// draw a unit jack out of spheroids
	glPushMatrix();
	wireJackPart();
	glRotated(90.0, 0, 1, 0);
	wireJackPart();
	glRotated(90.0, 1,0,0);
	wireJackPart();
	glPopMatrix();
}


void display(void) {

	int r, g, b;

	switch(myColor) {
		case MAGENTA:
			r = 1.0;
			g = 0.0;
			b = 1.0;
			break;

		case GREEN:
			r = 0.0;
			g = 1.0;
			b = 0.0;
			break;

		case BLUE:
			r = 0.0;
			g = 0.0;
			b = 1.0;
			break;

		case YELLOW:
			r = 1.0;
			g = 1.0;
			b = 0.0;
			break;

		case CYAN:
			r = 0.0;
			g = 1.0;
			b = 1.0;
			break;
	}

	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); // Camera initially points to -z direction

	glTranslatef(0.0, 0.0, -10.0);
	glRotated(cam_phi, 1, 0, 0); 
	glRotated(-cam_theta, 0, 1, 0); 

	/*draw the axis*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3d(0, 0, 1);
        axis(2);
    
	glPushMatrix();
        glRotated(90, 0 , 1.0, 0);
        glColor3d(1, 0, 0);
        axis(2);
	glPopMatrix();

	glPushMatrix();
        glRotated(-90, 1, 0 , 0);
        glColor3d(0,1,0);
        axis(2);
	glPopMatrix();

	glFlush();

	if (state == INITIAL) {
		if (myShape == SPHERE && SOLID == YES) {
			glColor3d(r,g,b);
			glutSolidSphere(.45, 200, 200);
			glFlush();
		}

		else if (myShape == SPHERE && SOLID == NO) {
			glColor3d(r,g,b);
			glutWireSphere(0.45, 10, 20);
			glFlush();
		}

		else if (myShape == TEAPOT && SOLID == YES) {
			glColor3d(r,g,b);
			glutSolidTeapot(.4);
			glFlush();
		}

		else if (myShape == TEAPOT && SOLID == NO) {
			glColor3d(r,g,b);
			glutWireTeapot(0.4);
			glFlush();
		}

		else if (myShape == JACK && SOLID == YES) {
			glColor3d(r,g,b);
			solidJack();
			glFlush();
		}

		else if (myShape == JACK && SOLID == NO) {
			glColor3d(r,g,b);
			wireJack();
			glFlush();
		}
	}

	else { //the state is not INITAL it is in ROTATE/TRANS/ OR SCALE

		if (state == ROTATE && myShape == SPHERE) {
			glColor3d(r,g,b);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();


		}


	}

}



void myKeyboard(unsigned char Key, int mouseX, int mouseY) {
// Deals with normal keys

	switch(Key) {
		case '1': 
			myShape = SPHERE; 
			display();
			glutSwapBuffers();
			break;
		
		case '2': 
			myShape = TEAPOT;
			display();
			glutSwapBuffers();
			break;

		case '3':
			myShape = JACK;
			display();
			glutSwapBuffers();
			break;

		case 'w':
			if (SOLID == YES) {
				SOLID = NO;
				display();
				glutSwapBuffers();
				break;
			}
			else {
				SOLID = YES;
				display();
				glutSwapBuffers();
				break;
			}

		case 'm':
			++myColor;
			
			if (myColor == WRAPAROUND) {
                myColor = MAGENTA;
                display();
				glutSwapBuffers();
            }

            else {
				display();
				glutSwapBuffers();
			}
			break;

		case 't':
			state = TRANSLATE;
			break;
		case 'r':
			state = SCALE;
			break;
		case 's':
			state = ROTATE;
			break;

		

		case 'x':
			if (state == TRANSLATE) {

			}
			else if (state == ROTATE) {

			}
			else if (state == SCALE) {

			}

			else
				printf("in initial state\n");

			break;


		case 'X':
			if (state == TRANSLATE) {

			}
			
			else if (state == SCALE) {

			}

			else
				printf("in initial state\n");

			break;

		case 'y':
			if (state == TRANSLATE) {

			}
			else if (state == ROTATE) {

			}
			else
				printf("in initial state\n");

			break;
		case 'Y':
			if (state == TRANSLATE) {

			}
			else
				printf("in initial state\n");

			break;

		case 'z':
			if (state == TRANSLATE) {

			}
			else if (state == ROTATE) {

			}
			else
				printf("in initial state\n");

			break;
		case 'Z':
			if (state == TRANSLATE) {

			}
			else
				printf("in initial state\n");

			break;

		case 'd':
			break;	
	}
			
}

void mySpecialKeyboard(int Key, int mouseX, int mouseY) {
// Deals with special keys

	switch(Key)	{
		case GLUT_KEY_RIGHT: // increase theta
			cam_theta += 2;
			display();
			glutSwapBuffers();
			break;
		case GLUT_KEY_LEFT: // increase theta
			cam_theta -= 2;
			display();
			glutSwapBuffers();
			break;
		case GLUT_KEY_UP: // increase phi
			cam_phi += 2;
			display();
			glutSwapBuffers();
			break;
		case GLUT_KEY_DOWN: // increase phi
			cam_phi -= 2;
			display();
			glutSwapBuffers();
			break;
	}
}



void Init() {

	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 64/48, 0.1, 1000);

	/*sets up the model matrix for camera*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4, 2, 4, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
    glEnable(GL_DEPTH_TEST);
}


int main (int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("HW2");

    Init();
    //glutReshapeFunc(Reshape);
	glutDisplayFunc(display);

	glutKeyboardFunc(myKeyboard);


	glutSpecialFunc(mySpecialKeyboard);


	//glClearColor(0.60, 0.75, 0.65, 0.0);
	glViewport(0, 0, 640, 480);

	glutMainLoop();

}

