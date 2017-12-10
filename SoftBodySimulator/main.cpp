#include "Point3d.h"
#include "Particle.h"
#include "SoftBody.h"
#include <glut.h>


// world (cube)
float angleX = 0.f;
float angleY = 0.f;
float worldW = 200.f;
float worldH = 200.f;
float worldD = 200.f;

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };		/* Red diffuse light. */
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };		/* Infinite light location. */
GLfloat light_position2[] = { -1.0, -1.0, -1.0, 0.0 };  /* Infinite light location. */

void init() {
	/* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 800, 800);

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.f, 1.f, 1.f, 900.f);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.f, 0.f, 500.f,	//eye position
		0.f, 0.f, 0.f,			//center position
		0.f, 1.f, 0.f);			//direction

	glClearColor(0.5f, 0.8f, 0.8f, 1.f);
	glPointSize(2);

	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
}

void processRotateKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		angleY += 5.f;
	}
	else if (key == GLUT_KEY_RIGHT) {
		angleY -= 5.f;
	}
	else if (key == GLUT_KEY_DOWN) {
		angleX += 5.f;
	}
	else if (key == GLUT_KEY_UP) {
		angleX -= 5.f;
	}
}

void drawWorld() {
	glPushMatrix();
	glRotatef(angleY, 0.f, 1.f, 0.f);
	//glRotatef(angleX, 1.f, 0.f, 0.f);

	glColor3f(0.f, 0.f, 0.f);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	glVertex3f(-worldW / 2.f, -worldH / 2.f, worldD / 2.f);
	glVertex3f(worldW / 2.f, -worldH / 2.f, worldD / 2.f);

	glVertex3f(-worldW / 2.f, -worldH / 2.f, worldD / 2.f);
	glVertex3f(-worldW / 2.f, worldH / 2.f, worldD / 2.f);

	glVertex3f(-worldW / 2.f, worldH / 2.f, worldD / 2.f);
	glVertex3f(worldW / 2.f, worldH / 2.f, worldD / 2.f);

	glVertex3f(worldW / 2.f, worldH / 2.f, worldD / 2.f);
	glVertex3f(worldW / 2.f, -worldH / 2.f, worldD / 2.f);

	glVertex3f(-worldW / 2.f, -worldH / 2.f, -worldD / 2.f);
	glVertex3f(worldW / 2.f, -worldH / 2.f, -worldD / 2.f);

	glVertex3f(-worldW / 2.f, -worldH / 2.f, -worldD / 2.f);
	glVertex3f(-worldW / 2.f, worldH / 2.f, -worldD / 2.f);

	glVertex3f(-worldW / 2.f, worldH / 2.f, -worldD / 2.f);
	glVertex3f(worldW / 2.f, worldH / 2.f, -worldD / 2.f);

	glVertex3f(worldW / 2.f, worldH / 2.f, -worldD / 2.f);
	glVertex3f(worldW / 2.f, -worldH / 2.f, -worldD / 2.f);

	glVertex3f(worldW / 2.f, -worldH / 2.f, worldD / 2.f);
	glVertex3f(worldW / 2.f, -worldH / 2.f, -worldD / 2.f);

	glVertex3f(-worldW / 2.f, -worldH / 2.f, worldD / 2.f);
	glVertex3f(-worldW / 2.f, -worldH / 2.f, -worldD / 2.f);

	glVertex3f(-worldW / 2.f, worldH / 2.f, worldD / 2.f);
	glVertex3f(-worldW / 2.f, worldH / 2.f, -worldD / 2.f);

	glVertex3f(worldW / 2.f, worldH / 2.f, worldD / 2.f);
	glVertex3f(worldW / 2.f, worldH / 2.f, -worldD / 2.f);

	glEnd();
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawWorld();
	glutSwapBuffers();
}



int main(int argc, char **argv) {

	//Point3d p(2, 3, 4.1), pp(1, 1, 1);
	//Point3d p1(p);
	//p1.show();
	//p1.set(pp);
	//p1.show();

	//Particle particle;
	//particle.setPosition(p);
	//particle.setLastPosition(pp);
	//particle.getLastPosition().show();
	//particle.getPosition().show();
	


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("SoftBodySimulator");

	glutDisplayFunc(display);	
	glutIdleFunc(display);
	init();
	glutSpecialFunc(processRotateKeys);

	glutMainLoop();

	return 0;
}