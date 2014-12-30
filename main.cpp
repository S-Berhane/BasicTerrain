/**
CompSci 3GC3 Assignment 3: Terrain Modelling
By: Simon Berhane
Email: s.berhane23@gmail.com
Features:
*/

#include <stdlib.h>
#include <stdio.h>
#include "BasicTerrain.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
using namespace std;
/**
Begin: Global variables
*/
//specifies the camera's eye
float pos[] = {0, 1, 0};
float rot[] = {0, 0, 0};

//values for the camera in perspective and orthogonal mode
float perspCamPos[] = {40,10,40};
float orthoCamPos[] = {5,5,0};
bool mode = true;
BasicTerrain terrain(10,10);

/**
End: Global Variables
*/

/**
Returns a random float between 2 numbers.
*/
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-100,0,0);
	glColor3f(1,1,1);
	glVertex3f(100,0,0);

	glColor3f(0,1,0);
	glVertex3f(0,-100,0);
	glColor3f(1,1,1);
	glVertex3f(0,100,0);

	glColor3f(0,0,1);
	glVertex3f(0,0,-100);
	glColor3f(1,1,1);
	glVertex3f(0,0,100);
	glEnd();
}

/**
Setting to change the camera to orthogonal display mode or perspective display mode.
*/
void orthoDisplay()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
}
void perspectiveDisplay()
{
    //change to projection matrix mode, set the extents of our viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(50, 1, 1,200);

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

    if(mode == true){
        perspectiveDisplay();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(perspCamPos[0], perspCamPos[1], perspCamPos[2], 0,0,0, 0,30,0);
    }
    else{
        orthoDisplay();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(orthoCamPos[0], orthoCamPos[1], orthoCamPos[2], 0,0,0, 0,30,0);
    }
    glRotatef(rot[1], 0, 1, 0);
    drawAxis();
    terrain.drawTerrain();
	glutSwapBuffers();

}
void reshape(int w, int h)
{

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    //the current matrix specifies the projection transformations and subsequent
    //transformation calls affect the proj matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0,2.0,1.5,20.0); //determines the shape of the viewing volume
    //the succeeding transformations now affect the modelview matrix instead of proj matrix
    glMatrixMode(GL_MODELVIEW);
}
void keyb(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;

        case 'm':
        case 'M':
            if (mode == true)
                mode = false;
            else
                mode = true;
            break;
	}
	glutPostRedisplay();
}
void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch(key)
	{
		case GLUT_KEY_LEFT:
			if (mode == true)perspCamPos[0] -= 0.5;
			else orthoCamPos[0] -= 0.5;
			break;

		case GLUT_KEY_RIGHT:
			if (mode == true)perspCamPos[0] += 0.5;
			else orthoCamPos[0] += 0.5;
			break;

		case GLUT_KEY_UP:
			if (mode == true)perspCamPos[2] -= 0.5;
			else orthoCamPos[2] -= 0.5;
			break;

		case GLUT_KEY_DOWN:
			if (mode == true)perspCamPos[2] += 0.5;
			else orthoCamPos[2] += 0.5;
			break;

		case GLUT_KEY_HOME:
			if (mode == true)perspCamPos[1] += 0.5;
			else orthoCamPos[1] += 0.5;
			break;

		case GLUT_KEY_END:
			if (mode == true)perspCamPos[1] -= 0.5;
			else orthoCamPos[1] -= 0.5;
			break;

	}
	glutPostRedisplay();
}
void init(void)
{

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

    //GLfloat amb[4] = {1.0,1.0,1.0,1.0};
    GLfloat dif[4] = {1,0,0,1};
    GLfloat spec[4] = {1.0, 1.0, 1.0, 1.0};

    float m_amb[] = {0.33,0.22,0.03,1.0};
    float m_dif[] = {0.78,0.57,0.11,1.0};
    float m_spec[] = {1.0, 1.0, 1.0, 1.0};
    float shiny = 50;

    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_amb);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_dif);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m_spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);

    //glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_AMBIENT_AND_DIFFUSE);

    //enable backface culling
    //glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    //terrain.lineAlgorithm(0);
    terrain.calculateFaceNormals();

}

/* main function - program entry point */
int main(int argc, char** argv)
{
    //glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(900, 900);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("BasicTerrain");
	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);
    init();
	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(keyb);
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	//glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	//start the program!
	glutMainLoop();

	return 0;
}
