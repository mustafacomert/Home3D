#include<GL/glut.h>

#define ROTATIONSPEED 5.0
#define TRANSLATIONSPEED 2.0

//rate of change variables of the rotation
int rx = 0, ry = 0, rz = 0;
//angle values for x, y, z respectively
float rotationAngles[3] = { 0 };
//x: 1, y: 2, z: 3
int currentAxis = -1;
//initial scaling of the home
float sx = 0.5, sy = 0.5, sz = 0.5;
//initial translation of the translation
float tx = 0, ty = 0, tz = 0;

int ground[8][3] = {
		{-110,-90,110},
		{110,-90,110},
		{110,-70,110},
		{-110,-70,110},

		{110,-70,-110},
		{110,-90,-110},
		{-110,-70,-110},
		{-110,-90,-110}
};

int walls[8][3] = {
	//front corners
	{-80,-75,80},
	{80,-75,80},
	{80,50,80},
	{-80,50,80},
	//back corners
	{80,50,-80},
	{80,-75,-80},
	{-80,50,-80},
	{-80,-75,-80}
};

int roof[8][3] = {
		{-120,50,80},
		{120,50,80},
		{0,120,80},
		{0,120,80},

		{0,120,-80},
		{120,50,-80},
		{0,120,-80},
		{-120,50,-80}
};

int door[8][3] = {
		{-30,-70, 80},
		{30,-70, 80},
		{30,5, 80},
		{-30,5, 80},

		{30,5, 81},
		{30,-70, 81},
		{-30,5, 81},
		{-30,-70, 81}
};


void init()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.2, 0.6, 0.6, 1.0);
	glColor3f(0.4, 0.2, 0.6);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawSurface(int* a, int* b, int* c, int* d)
{
	glBegin(GL_POLYGON);
	glVertex3iv(a);
	glVertex3iv(b);
	glVertex3iv(c);
	glVertex3iv(d);
	glEnd();
}

void drawGround()
{
	glColor3f(1.0, 0.6, 0.2);
	drawSurface(ground[0], ground[1], ground[2], ground[3]);
	drawSurface(ground[1], ground[2], ground[4], ground[5]);
	drawSurface(ground[0], ground[3], ground[6], ground[7]);
	drawSurface(ground[0], ground[1], ground[5], ground[7]);
	drawSurface(ground[2], ground[3], ground[6], ground[4]);
	drawSurface(ground[4], ground[5], ground[7], ground[6]);
}


void drawWalls()
{
	glColor3f(1, 0.9, 0.8);
	drawSurface(walls[0], walls[1], walls[2], walls[3]);//front face
	glColor3f(0.54, 0.2, 1);
	drawSurface(walls[1], walls[2], walls[4], walls[5]);//right face
	glColor3f(0.54, 1, 0);
	drawSurface(walls[0], walls[3], walls[6], walls[7]);//left face
	glColor3f(1, 0.9, 0.8);
	drawSurface(walls[0], walls[1], walls[5], walls[7]);//back face
	drawSurface(walls[2], walls[3], walls[6], walls[4]);//up
	drawSurface(walls[4], walls[5], walls[7], walls[6]);//down
}

void drawRoof()
{
	glColor3f(0.54, 0.2, 0.14);
	drawSurface(roof[0], roof[1], roof[2], roof[2]);// front triangle
	drawSurface(roof[1], roof[2], roof[4], roof[5]);// right
	drawSurface(roof[0], roof[3], roof[6], roof[7]);// left
	drawSurface(roof[0], roof[1], roof[5], roof[7]);// down
	drawSurface(roof[4], roof[5], roof[7], roof[6]); // back triangle
}

void drawDoor()
{
	glColor3f(0.5, 0.5, 1);
	drawSurface(door[0], door[1], door[2], door[3]);
	drawSurface(door[1], door[2], door[4], door[5]);
	drawSurface(door[0], door[3], door[6], door[7]);
	drawSurface(door[0], door[1], door[5], door[7]);
	drawSurface(door[2], door[3], door[6], door[4]);
	drawSurface(door[4], door[5], door[7], door[6]);
}


void drawHome() {
	drawGround();
	drawWalls();
	drawRoof();
	drawDoor();
}


void rotateHome()
{
	switch (currentAxis)
	{
	case 0:
		rotationAngles[0] = rx;
		break;
	case 1:
		rotationAngles[1] = ry;
		break;
	case 2:
		rotationAngles[2] = rz;
		break;
	}

	if (rx == 0 && ry == 0 && rz == 0)
	{
		rotationAngles[0] = rotationAngles[1] = rotationAngles[2] = 0;
		glRotatef(0, 1.0, 0.0, 0.0);
		glRotatef(0, 0.0, 1.0, 0.0);
		glRotatef(0, 0.0, 0.0, 1.0);
	}
	else
	{
		glRotatef(rotationAngles[0], 1.0, 0.0, 0.0);
		glRotatef(rotationAngles[1], 0.0, 1.0, 0.0);
		glRotatef(rotationAngles[2], 0.0, 0.0, 1.0);
	}
}

//first translate
//second rotate
//third scale
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
		glTranslatef(tx, ty, tz);
		rotateHome();
		glScalef(sx, sy, sz);
		drawHome();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x1, int y1)
{
	//reset rotation, scaling, and translation
	if (key == 'r' || key == 'R')
	{
		rx = ry = rz = 0;
		sx = sy = sz = 0.5;
		tx = ty = tz = 0;
	}
	if (key == 'x' || key == 'X')
	{
		currentAxis = 0;
	}
	if (key == 'y' || key == 'Y')
	{
		currentAxis = 1;
	}
	if (key == 'z' || key == 'Z')
	{
		currentAxis = 2;
	}
	//scale up
	if (key == 'S' && sx < 1)
	{
		sx += 0.01;
		sy += 0.01;
		sz += 0.01;
	}
	//scale down
	if (key == 's' && sx > 0.02)
	{
		sx -= 0.01;
		sy -= 0.01;
		sz -= 0.01;
	}
	//translate up
	if (key == '8')
	{
		if (ty < 140.0)
			ty += TRANSLATIONSPEED;
	}
	//translate down
	if (key == '2')
	{
		if (ty > -140.0)
			ty -= TRANSLATIONSPEED;
	}
	//translate right
	if (key == '6')
	{
		if (tx < 140.0)
			tx += TRANSLATIONSPEED;
	}
	//translate left
	if (key == '4')
	{
		if (tx > -140.0)
			tx -= TRANSLATIONSPEED;
	}
	//translate front
	if (key == '5')
	{
		tz += TRANSLATIONSPEED;
	}
	//translate back
	if (key == '0')
	{
		tz -= TRANSLATIONSPEED;
	}
}


void specialKeys(int key, int x1, int y1) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		switch (currentAxis)
		{
		case 0:
			rx += ROTATIONSPEED;
			break;
		case 1:
			ry += ROTATIONSPEED;
			break;
		case 2:
			rz += ROTATIONSPEED;
			break;
		}
		break;
	case GLUT_KEY_RIGHT:
		switch (currentAxis)
		{
		case 0:
			rx -= ROTATIONSPEED;
			break;
		case 1:
			ry -= ROTATIONSPEED;
			break;
		case 2:
			rz -= ROTATIONSPEED;
			break;
		}
		break;
	}
}


int main(int argc, char** argv)
{
	//create a 800x800 window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CSE 461 Home3D");

	glEnable(GL_DEPTH_TEST);
	init();

	//callbacks
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}