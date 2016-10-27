#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>


enum {SPHERE, TEAPOT, JACK};
enum {YES, NO};
enum {FLAT, SMOOTH};
enum {INITIAL, ROTATE, TRANSLATE, SCALE};
enum {MAGENTA, GREEN, BLUE, YELLOW, CYAN, WRAPAROUND};

float cam_theta = 45.0;
float cam_phi = 45.0;

int myShape = SPHERE;
int myShade = SMOOTH;
int myColor = MAGENTA;
int SOLID = YES;
int state = INITIAL;
int transfomation = NO;

double scale_factor = 1;

double moveInX = 0;
double moveInY = 0;
double moveInZ = 0;

double angleX = 0;
double angleY = 0;
double angleZ = 0;


/***************************** BUILDING OBJECTS **********************/

/* axis and its cone */
void axis(double length) {
 	
	glPushMatrix();
	glBegin(GL_LINES);
        glVertex3d(0, 0, 0);		//origin
        glVertex3d(0, 0, length); 	// along the z-axis
	glEnd();

	glTranslated(0, 0, length -0.2);	//translate the cone
	glutSolidCone(0.3, 0.5, 12, 9);	//the cone
	glPopMatrix();
}

/* Using the axis func append them together to get the coordinate axis */
void drawAxis(double length) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3d(0, 0, 1);
        axis(length);
    
	glPushMatrix();
        glRotated(90, 0 , 1.0, 0);
        glColor3d(1, 0, 0);
        axis(length);
	glPopMatrix();

	glPushMatrix();
        glRotated(-90, 1, 0 , 0);
        glColor3d(0,1,0);
        axis(length);
	glPopMatrix();

	glFlush();
}


/************************* SOLID OBJECTS ***************************/
/* SOLID TEAPOT */
void drawSolidTeapot(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			glutSolidTeapot(1);
		glPopMatrix();
	}

	else 
		glutSolidTeapot(1);
}

/* SOLID SPHERE */
void drawSolidSphere(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			glutSolidSphere(1,200,200);
		glPopMatrix();
	}

	else 
		glutSolidSphere(1,200,200);
}


/* Solid Jack Parts */
void solidJackPart() {
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

/* Solid Jack */
void solidJack() {
	glPushMatrix();
	solidJackPart();
	glRotated(90.0, 0, 1, 0);
	solidJackPart();
	glRotated(90.0, 1,0,0);
	solidJackPart();
	glPopMatrix();
}

void drawSolidJack(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			solidJack();
		glPopMatrix();
	}

	else 
		solidJack();
}
























/********************* WIRED OBJECTS ***********************/
/* WIRED TEAPOT */
void drawWireTeapot(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			glutWireTeapot(1);
		glPopMatrix();
	}

	else 
		glutWireTeapot(1);
}

/* WIRED SPHERE */
void drawWireSphere(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			glutWireSphere(1,200,200);
		glPopMatrix();
	}

	else 
		glutWireSphere(1,200,200);
}

/* WIRED JACK PART */
void wireJackPart() {
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

/* WIRED JACK */
void wireJack() {
	glPushMatrix();
	wireJackPart();
	glRotated(90.0, 0, 1, 0);
	wireJackPart();
	glRotated(90.0, 1,0,0);
	wireJackPart();
	glPopMatrix();
}

/* DRAW WIRED JACK */
void drawWireJack(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			wireJack();
		glPopMatrix();
	}

	else 
		wireJack();
}






/********************* OPENGL FUNCTIONS **********************/

/* my display function */
void display(void) {
	int r, g, b;

	/* determin the color */
	switch(myColor) {
		case MAGENTA:
			r = 1.0; g = 0.0; b = 1.0; break;
	
		case GREEN:
			r = 0.0; g = 1.0; b = 0.0; break;
		
		case BLUE:
			r = 0.0; g = 0.0; b = 1.0; break;
			
		case YELLOW:
			r = 1.0; g = 1.0; b = 0.0; break;
			
		case CYAN:
			r = 0.0; g = 1.0; b = 1.0; break;
	}

	/* position and aim the camera */
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); // Camera initially points to -z direction

	glTranslatef(0.0, 0.0, -60.0);
	glRotated(cam_phi, 1, 0, 0); 
	glRotated(-cam_theta, 0, 1, 0); 

	/*draw the axis*/
	drawAxis(10);
	
	if (myShape == SPHERE && SOLID == YES) {

		if ()
		glColor3d(r,g,b);
		drawSolidSphere(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == SPHERE && SOLID == NO) {
		glColor3d(r,g,b);
		drawWireSphere(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == TEAPOT && SOLID == YES) {
		glColor3d(r,g,b);
		drawSolidTeapot(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
			
	}

	else if (myShape == TEAPOT && SOLID == NO) {
		glColor3d(r,g,b);
		drawWireTeapot(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == JACK && SOLID == YES) {
		glColor3d(r,g,b);
		drawSolidJack(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == JACK && SOLID == NO) {
		glColor3d(r,g,b);
		drawWireJack(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}
	
	glutSwapBuffers();
}



void myKeyboard(unsigned char Key, int mouseX, int mouseY) {
// Deals with normal keys

	switch(Key) {
		case '1': 
			myShape = SPHERE; 
			display();
			break;
		
		case '2': 
			myShape = TEAPOT;
			display();
			break;

		case '3':
			myShape = JACK;
			display();
			break;


		/* Initially: myShade = SMOOTH / SOLID = YES
		   oder: SMOOTH -> FLAT -> WIRE -> SMOOTH -> ..... */

		case 'w':
			if (SOLID == YES) {
				if (myShade == SMOOTH) {	//display Smooth shading
					glShadeModel(GL_SMOOTH);
					display();
					myShade = FLAT;	//update shading after display
					break;
				}

				else if (myShade == FLAT) {
					glShadeModel(GL_FLAT);
					display();
					SOLID = NO;
					break;
				}
			
			else {			
				display();
				SOLID = YES;
				myShade = SMOOTH;
				break;
			}

		case 'm':
			++myColor;
			
			if (myColor == WRAPAROUND) {
                myColor = MAGENTA;
                display();
            }

            else {
				display();
			}
			break;

		case 't':
			transfomation = YES;
			state = TRANSLATE;
			break;
		case 's':
			transfomation = YES;
			state = SCALE;
			break;
		case 'r':
			transfomation = YES;
			state = ROTATE;
			break;

		case 'x':
			if (state == SCALE) {
				scale_factor+=0.2;
				display();
				break;
			}
			
			else if (state == TRANSLATE) {
				moveInX+=0.5;
				display();
				break;
			}

			else if (state == ROTATE) {
				angleX+=5;
				display();
				break;
			}
			


		case 'X':
			if (state == SCALE) {
				scale_factor-=0.2;
				display();
				break;
			}

			else if (state == TRANSLATE) {
				moveInX-=0.5;
				display();
				break;
			}

			else if (state == ROTATE) {
				angleX-=5;
				display();
				break;
			}

		case 'y':
			if (state == TRANSLATE) {
				moveInY+=0.5;
				display();
				break;
			}

			else if (state == ROTATE) {
				angleY+=5;
				display();
				break;
			}

		case 'Y':
			if (state == TRANSLATE) {
				moveInY-=0.5;
				display();
				break;
			}

			else if (state == ROTATE) {
				angleY-=5;
				display();
				break;
			}
			

		case 'z':
			if (state == TRANSLATE) {
				moveInZ+=0.5;
				display();
				break;
			}

			else if (state == ROTATE) {
				angleZ+=5;
				display();
				break;
			}
		
		case 'Z':
			if (state == TRANSLATE) {
				moveInZ-=0.5;
				display();
				break;
			}

			else if (state == ROTATE) {
				angleZ-=5;
				display();
				break;
			}
			
		case 'd':
			/* resets */
			state = INITIAL;
			transfomation = NO;
			angleX = 0;
			angleY = 0;
			angleZ = 0;
			moveInX = 0;
			moveInY = 0;
			moveInZ = 0;
			scale_factor = 1;
			cam_theta = 45.0;
			cam_phi = 45.0;
			display();
			break;	
	}
			
}

void mySpecialKeyboard(int Key, int mouseX, int mouseY) {
// Deals with special keys

	switch(Key)	{
		case GLUT_KEY_RIGHT: // increase theta
			cam_theta += 2;
			display();
			break;
		case GLUT_KEY_LEFT: // increase theta
			cam_theta -= 2;
			display();
			break;
		case GLUT_KEY_UP: // increase phi
			cam_phi += 2;
			display();
			break;
		case GLUT_KEY_DOWN: // increase phi
			cam_phi -= 2;
			display();
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
   
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);

	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, 640, 480);

	glutMainLoop();

}

