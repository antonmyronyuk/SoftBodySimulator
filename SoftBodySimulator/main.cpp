#include "SoftBody.h"
#include <glut.h>
#include <iostream>


// world (cube)
float angleX = 0.f;
float angleY = 0.f;
float worldW = 200.f;
float worldH = 200.f;
float worldD = 200.f;
float pi = 3.141592f;
float size = 40.f;

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };		/* Red diffuse light. */
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };		/* Infinite light location. */
GLfloat light_position2[] = { -1.0, -1.0, -1.0, 0.0 };  /* Infinite light location. */

ParticlesSym particlesSym;
std::vector<std::pair<unsigned int, unsigned int> > constraints;
SoftBody body(&particlesSym);

Point3d getOGLPos(int x, int y) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	std::cout << winZ << std::endl;
	
	if (winZ > 0.999999999f) {
		winZ = 0.997f;
	}
	

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	std::cout << posX << "   " << posY << "   " << posZ << std::endl;
	return Point3d(posX, posY, posZ);
}

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
		body.disableFix();
	}
	std::cout << angleY << std::endl;

}

bool rightDown = false;
bool leftDown = false;

void mouseFunc(int button, int state, int x, int y) {
	
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		leftDown = true;
	}
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		leftDown = false;
		particlesSym.turnForceOff();
	}

	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
		rightDown = true;
	}
	if (state == GLUT_UP && button == GLUT_RIGHT_BUTTON) {
		rightDown = false;
	}

	if (leftDown) {
		Point3d p = getOGLPos(x, y);
		particlesSym.turnForceOn(Point3d(p.X() * cos(angleY * pi / 180) - p.Z() * sin(angleY * pi / 180),
			p.Y(),
			p.Z() * cos(angleY * pi / 180) + p.X() * sin(angleY * pi / 180)),
			size * size * size / 12 //different power for different bodies
		);
	}
	/*
	if (rightDown) {
		Point3d p = getOGLPos(x, y);
		body.addFix(0, p.X(), p.Y(), p.Z());
	}
	*/
}

void motionFunc(int x, int y) {
	
	std::cout << "x = " << x
		<< "y = " << y << std::endl;
	if (rightDown) {
		Point3d p = getOGLPos(x, y);
		body.addFix(0, 0.55f * p.X() * cos(angleY * pi / 180), 0.55f * p.Y(), 0.55f * p.X() * sin(angleY * pi / 180));
	}
}



void buildCube(float size) {
	std::vector<Point3d> points;
	std::vector<size_t> inds;
	std::vector<std::pair<unsigned int, unsigned int> > constraints;
	points.push_back(Point3d(-size, -size, size)); //1
	points.push_back(Point3d(-size, -size, -size)); //2
	points.push_back(Point3d(size, -size, -size)); //3
	points.push_back(Point3d(size, -size, size)); //4
	points.push_back(Point3d(-size, size, size)); //5
	points.push_back(Point3d(-size, size, -size)); //6
	points.push_back(Point3d(size, size, -size)); //7
	points.push_back(Point3d(size, size, size)); //8

	inds.clear();
	inds.push_back(0);
	inds.push_back(1);
	inds.push_back(2);

	inds.push_back(2);
	inds.push_back(3);
	inds.push_back(0);

	inds.push_back(4);
	inds.push_back(5);
	inds.push_back(6);

	inds.push_back(6);
	inds.push_back(7);
	inds.push_back(4);

	inds.push_back(0);
	inds.push_back(4);
	inds.push_back(7);

	inds.push_back(7);
	inds.push_back(3);
	inds.push_back(0);

	inds.push_back(1);
	inds.push_back(5);
	inds.push_back(6);

	inds.push_back(6);
	inds.push_back(2);
	inds.push_back(1);

	inds.push_back(0);
	inds.push_back(4);
	inds.push_back(5);

	inds.push_back(5);
	inds.push_back(1);
	inds.push_back(0);

	inds.push_back(3);
	inds.push_back(7);
	inds.push_back(6);

	inds.push_back(6);
	inds.push_back(2);
	inds.push_back(3);

	constraints.clear();
	constraints.push_back(std::make_pair(0, 1));
	constraints.push_back(std::make_pair(1, 2));
	constraints.push_back(std::make_pair(2, 3));
	constraints.push_back(std::make_pair(3, 0));
	constraints.push_back(std::make_pair(4, 5));
	constraints.push_back(std::make_pair(5, 6));
	constraints.push_back(std::make_pair(6, 7));
	constraints.push_back(std::make_pair(7, 4));
	constraints.push_back(std::make_pair(0, 4));
	constraints.push_back(std::make_pair(1, 5));
	constraints.push_back(std::make_pair(2, 6));
	constraints.push_back(std::make_pair(3, 7));

	constraints.push_back(std::make_pair(0, 6));
	constraints.push_back(std::make_pair(4, 2));
	constraints.push_back(std::make_pair(3, 5));
	constraints.push_back(std::make_pair(1, 7));

	constraints.push_back(std::make_pair(0, 7));
	constraints.push_back(std::make_pair(4, 3));

	constraints.push_back(std::make_pair(1, 6));
	constraints.push_back(std::make_pair(5, 2));

	constraints.push_back(std::make_pair(0, 5));
	constraints.push_back(std::make_pair(4, 1));

	constraints.push_back(std::make_pair(3, 6));
	constraints.push_back(std::make_pair(7, 2));

	constraints.push_back(std::make_pair(0, 2));
	constraints.push_back(std::make_pair(1, 3));

	constraints.push_back(std::make_pair(4, 6));
	constraints.push_back(std::make_pair(5, 7));

	//body.setStiffness(0.017f);
	body.setColor(1.f, 1.f, 1.f);
	body.setMesh(points, inds, false, constraints);
	//body.setPointPos(0, 200.f, 200.f, 200.f);
	//body.addFix(0, -size, -size + 50.f, size);
}

void drawWorld() {

	particlesSym.step(20);
	glPushMatrix();
	glRotatef(angleY, 0.f, 1.f, 0.f);
	//std::cout << sin(angleY) << std::endl;

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
	body.renderCube();
	//body.setPointPos(0, 0.f, 0.f, 0.f);
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawWorld();
	glutSwapBuffers();
}



int main(int argc, char **argv) {
	float stiffness;
	float gravity;
	std::cout << "SoftCube edge size (recommended 40): ";
	std::cin >> size;
	size = fabs(size);
	std::cout << "Stiffness (float number from 0 to 1, recommended 0.01 - 0.02): ";
	std::cin >> stiffness;
	stiffness = fabs(stiffness);
	if (stiffness < 0.001) {
		stiffness = 0.001;
	}
	std::cout << "Gravity (recommended 0.5): ";
	std::cin >> gravity;

	
	particlesSym.setGravity(Point3d(0.f, -gravity, 0.f)); // -0.98
	particlesSym.setFriction(0.97f);
	particlesSym.setGroundFriction(0.96f);
	particlesSym.setWorldSize(worldW, worldH, worldD);
	body.setStiffness(stiffness); // 0.017
	buildCube(size / 2); // 40
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("SoftBodySimulator");

	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutIdleFunc(display);
	init();
	glutSpecialFunc(processRotateKeys);

	glutMainLoop();

	return 0;
}