#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"


enum {SPHERE, TEAPOT, JACK, AIRPLANE};
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

int n;
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
			glutSolidSphere(1,20,100);
		glPopMatrix();
	}

	else 
		glutSolidSphere(1,20,100);
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

/* SOLID AIRPLANE PARTS */
void drawSolidBody() {
	glPushMatrix();
		glScaled(0.6,0.4,4);
		glutSolidSphere(1, 50, 50);
	glPopMatrix();
}

void drawSolidWingA() {
	glPushMatrix();
		glScaled(9,0.2,1.8);
		glutSolidCube(1);
	glPopMatrix();

}

void drawSolidWingB() {	//fin
	glPushMatrix();
		glScaled(0.9,0.02,1.2);
		glutSolidCone(1.1,1.2,50,50);
	glPopMatrix();
}

void drawSupportBeam() {
	glPushMatrix();
		glScaled(0.1,1.3,0.1);
		glutSolidCube(1);
	glPopMatrix();
}

void drawWheel() {
	glPushMatrix();
		glScaled(0.010,1.5,1.5);
		glutSolidSphere(1,50,50);
	glPopMatrix();
}

void drawSolidAirplane() {
	
	//the body
	drawSolidBody();	

	//the top wing
	glPushMatrix();
		glTranslated(0,1.3,2);
		drawSolidWingA();
	glPopMatrix();

	//the bottom wing
	glPushMatrix();
		glTranslated(0,0,2);
		drawSolidWingA();
	glPopMatrix();

	//the support beams between wings
	glPushMatrix();
		glTranslated(3.2,0.6,2.5);
		drawSupportBeam();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-3.2,0.6,2.5);
		drawSupportBeam();
	glPopMatrix();

	glPushMatrix();
		glTranslated(3.2,0.6,1.5);
		drawSupportBeam();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-3.2,0.6,1.5);
		drawSupportBeam();
	glPopMatrix();


	//horizontal fin
	glPushMatrix();
		glTranslated(0,0.15,-4.5);
		glScaled(0.8,1,1.5);
		drawSolidWingB();
	glPopMatrix();

	//vertical fin
	glPushMatrix();
		glScaled(0.7,0.7,0.7);
		glTranslated(0,1,-5.8);
		glRotated(30,1,0,0);
		glRotated(90,0,0,1);
		drawSolidWingB();
	glPopMatrix();

	//wheel beam
	glPushMatrix();	//the left beam
		glTranslated(1.4,-0.6,2);
		drawSupportBeam();
	glPopMatrix();
	
	glPushMatrix();	//the right beam
		glTranslated(-1.4,-0.6,2);
		drawSupportBeam();
	glPopMatrix();

	//right wheel
	glPushMatrix();
		glTranslated(-1.5,-1.1,2);
		glScaled(0.25,0.25,0.25);
		drawWheel();
	glPopMatrix();

	//left wheel
	glPushMatrix();
		glTranslated(1.5,-1.1,2);
		glScaled(0.25,0.25,0.25);
		drawWheel();
	glPopMatrix();

	//smaller beam 
	glPushMatrix();
		glTranslated(0,-0.6,-1.7);
		glScaled(1,0.5,1);
		drawSupportBeam();
	glPopMatrix();

	//back wheel
	glPushMatrix();
		glTranslated(0,-0.8,-1.7);
		glScaled(0.15,0.15,0.15);
		drawWheel();
	glPopMatrix();

	//propeller
	glPushMatrix();
		glTranslated(0,0,3.5);
		glScaled(0.8,1,0.8);
		drawSupportBeam();
    glPopMatrix();

    glPushMatrix();
		glTranslated(0,0,3.5);
		glRotated(90,0,0,1);
		glScaled(0.8,1,0.8);
		drawSupportBeam();
    glPopMatrix();

    glPushMatrix();
		glTranslated(0,0,3.5);
		glRotated(45,0,0,1);
		glScaled(0.8,1,0.8);
		drawSupportBeam();
    glPopMatrix();


   glPushMatrix();
		glTranslated(0,0,3.5);
		glRotated(135,0,0,1);
		glScaled(0.8,1,0.8);
		drawSupportBeam();
    glPopMatrix();

}

void mySolidAirplane(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			drawSolidAirplane();
		glPopMatrix();
	}

	else 
		drawSolidAirplane();
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
			glutWireSphere(1,20,200);
		glPopMatrix();
	}

	else 
		glutWireSphere(1,20,200);
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

/* WIRE AIRPLANE PARTS */
void drawWireBody() {
	glPushMatrix();
		glScaled(0.6,0.4,4);
		glutWireSphere(1, 50, 50);
	glPopMatrix();
}

void drawWireWingA() {
	glPushMatrix();
		glScaled(9,0.2,1.8);
		glutWireCube(1);
	glPopMatrix();

}

void drawWireWingB() {	//fin
	glPushMatrix();
		glScaled(0.9,0.02,1.2);
		glutWireCone(1.1,1.2,50,50);
	glPopMatrix();
}

void drawWireSupportBeam() {
	glPushMatrix();
		glScaled(0.1,1.3,0.1);
		glutWireCube(1);
	glPopMatrix();
}

void drawWireWheel() {
	glPushMatrix();
		glScaled(0.010,1.5,1.5);
		glutWireSphere(1,50,50);
	glPopMatrix();
}

void drawWireAirplane() {
	
	//the body
	drawWireBody();	

	//the top wing
	glPushMatrix();
		glTranslated(0,1.3,2);
		drawWireWingA();
	glPopMatrix();

	//the bottom wing
	glPushMatrix();
		glTranslated(0,0,2);
		drawWireWingA();
	glPopMatrix();

	//the support beams between wings
	glPushMatrix();
		glTranslated(3.2,0.6,2.5);
		drawWireSupportBeam();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-3.2,0.6,2.5);
		drawWireSupportBeam();
	glPopMatrix();

	glPushMatrix();
		glTranslated(3.2,0.6,1.5);
		drawWireSupportBeam();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-3.2,0.6,1.5);
		drawWireSupportBeam();
	glPopMatrix();


	//horizontal fin
	glPushMatrix();
		glTranslated(0,0.15,-4.5);
		glScaled(0.8,1,1.5);
		drawWireWingB();
	glPopMatrix();

	//vertical fin
	glPushMatrix();
		glScaled(0.7,0.7,0.7);
		glTranslated(0,1,-5.8);
		glRotated(30,1,0,0);
		glRotated(90,0,0,1);
		drawWireWingB();
	glPopMatrix();

	//wheel beam
	glPushMatrix();	//the left beam
		glTranslated(1.4,-0.6,2);
		drawWireSupportBeam();
	glPopMatrix();
	
	glPushMatrix();	//the right beam
		glTranslated(-1.4,-0.6,2);
		drawWireSupportBeam();
	glPopMatrix();

	//right wheel
	glPushMatrix();
		glTranslated(-1.5,-1.1,2);
		glScaled(0.25,0.25,0.25);
		drawWireWheel();
	glPopMatrix();

	//left wheel
	glPushMatrix();
		glTranslated(1.5,-1.1,2);
		glScaled(0.25,0.25,0.25);
		drawWireWheel();
	glPopMatrix();

	//smaller beam 
	glPushMatrix();
		glTranslated(0,-0.6,-1.7);
		glScaled(1,0.5,1);
		drawWireSupportBeam();
	glPopMatrix();

	//back wheel
	glPushMatrix();
		glTranslated(0,-0.8,-1.7);
		glScaled(0.15,0.15,0.15);
		drawWireWheel();
	glPopMatrix();

	//propeller
	glPushMatrix();
		glTranslated(0,0,3.5);
		glScaled(0.8,1,0.8);
		drawWireSupportBeam();
    glPopMatrix();

    glPushMatrix();
		glTranslated(0,0,3.5);
		glRotated(90,0,0,1);
		glScaled(0.8,1,0.8);
		drawWireSupportBeam();
    glPopMatrix();

    glPushMatrix();
		glTranslated(0,0,3.5);
		glRotated(45,0,0,1);
		glScaled(0.8,1,0.8);
		drawWireSupportBeam();
    glPopMatrix();


   glPushMatrix();
		glTranslated(0,0,3.5);
		glRotated(135,0,0,1);
		glScaled(0.8,1,0.8);
		drawWireSupportBeam();
    glPopMatrix();

}

void myWireAirplane(double sc, double mx, double my, double mz, double ax, double ay, double az) {
	if (transfomation == YES) {
		glPushMatrix();
			glTranslated(mx,my,mz);
			glScaled(sc,sc,sc);
			glRotated(az,0,0,1);
			glRotated(ay,0,1,0);
			glRotated(ax,1,0,0);
			drawWireAirplane();
		glPopMatrix();
	}

	else 
		drawWireAirplane();
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
		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		drawSolidSphere(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == SPHERE && SOLID == NO) {
		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		drawWireSphere(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);	
		glFlush();
	}

	else if (myShape == TEAPOT && SOLID == YES) {
		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		drawSolidTeapot(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
			
	}

	else if (myShape == TEAPOT && SOLID == NO) {
		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		drawWireTeapot(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == JACK && SOLID == YES) {
		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		drawSolidJack(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == JACK && SOLID == NO) {
		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		drawWireJack(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == AIRPLANE && SOLID == YES) {

		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		mySolidAirplane(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}

	else if (myShape == AIRPLANE && SOLID == NO) {
		GLfloat mat_diffuse[] = { (GLfloat)r, (GLfloat)g, (GLfloat)b, 0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		myWireAirplane(scale_factor, moveInX, moveInY, moveInZ, angleX, angleY, angleZ);
		glFlush();
	}
	
	glutSwapBuffers();
}



void myKeyboard(unsigned char Key, int mouseX, int mouseY) {
// Deals with normal keys

	switch(Key) {
		case '1': 
			myShape = SPHERE; 
			n = ret();
			printf("n is %d",n);
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

		case '4':
			myShape = AIRPLANE;
			display();
			break;


		/* Initially: myShade = SMOOTH / SOLID = YES
		   oder: SMOOTH -> FLAT -> WIRE -> SMOOTH -> ..... */
		/* buggy */
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
				
				if (scale_factor < 0)
					scale_factor = 0;

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
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT: // increase theta
			cam_theta -= 2;
			display();
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP: // increase phi
			cam_phi += 2;
			display();
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN: // increase phi
			cam_phi -= 2;
			display();
			glutPostRedisplay();
			break;
	}
}

void Init() {

	// set properties of the surface material
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; // gray
	GLfloat mat_diffuse[] = { 0.6, 0.0, 0.0, 1.0 }; 
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; 
	GLfloat mat_shininess[] = { 50.0 }; 
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// Set the lights
	GLfloat light_intensity[] = {0.8, 0.8, 0.8, 1.0};
	GLfloat light_position[] = {0, 10, 10, 1}; 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
	//float local_view[] = {0.0};
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glClearColor(0.97, 0.78, 0.64, 0.0);  // background color
    glColor3f(1.0, 1.0, 1.0);
	
	// set the camera
	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	
	gluPerspective(20, 64/48., 0.1, 1000);

	glEnable(GL_DEPTH_TEST);
  
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
}


int main (int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("HW2");

    Init();
   
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glEnable(GL_LIGHTING); // enable the light source
	glEnable(GL_LIGHT0); // use this specific light
	

	glShadeModel(GL_SMOOTH); // shading method
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.97, 0.78, 0.64, 0.0);  // background color
	glViewport(0, 0, 640, 480);
	glutMainLoop();
}
