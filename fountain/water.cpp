#include<gl/glut.h>
#include<math.h>
#include<string.h>
#define GLUT_BITMAP_TIMES_ROMAN_24 ((void*)5)
void myinit()
{
	glClearColor(51.0 / 255.0, 25.0 / 255.0, 0 / 255.0, 1);
	gluOrtho2D(-220, 30, -10, 240);
}
void Sprint(float x, float y, char *st)
{
	int l, i;
	l = strlen(st);
	glRasterPos2f(x, y);
	for (i = 0; i<l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}
	glFlush();
}
void slow(int k)
{
	double i = 0;
	while (k--)
		for (i = 0; i<999999; i++);
}
void erase()
{
	glColor3f(51.0 / 255.0, 25.0 / 255.0, 0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(-100, 80);
	glVertex2f(-100, 140);
	glVertex2f(-170, 140);
	glVertex2f(-170, 80);
	glEnd();
	glFlush();
}
void display()
{
	int k = 900, a = 0;
	char hi[50][50] = { "38440 KM","76880 KM","115320 KM","153760 KM","192200 KM","230640 KM","269080 KM","307520 KM","345960 KM","384400 KM" };
	glClear(GL_COLOR_BUFFER_BIT);
	Sprint(-150, 110, "NEW HORIZON'S");
	slow(200);
	erase();
	slow(50);
	glColor3f(1, 1, 1);

	Sprint(-150, 112, "FIRST ROCKET");
	slow(100);
	erase();
	slow(50);
	glColor3f(0.7, 0, 1);

	Sprint(-170, 118, "BY NITESH YADAV");
	slow(200);
	erase();
	slow(50);
	glColor3f(1, 0, 1);


	Sprint(-170, 112, "TOTAL  DISTANCE  FROM");
	slow(50);

	Sprint(-160, 102, "EARTH TO MOON");
	slow(50);
	glColor3f(.7, 0, 0);
	Sprint(-155, 92, "3,84,400 km");
	slow(200);

	glColor3f(0.0 / 255.0, 100.0 / 255.0, 0.0 / 255.0);
	glBegin(GL_POLYGON);
	for (float n = 0; n<360; n++)
	{
		float h = 6.28*n / 360.0;
		glVertex3f(-95 + 190 * cosf(h), -160 + 190 * sinf(h), 0);
	}
	glEnd();

	glColor3f(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0);
	glBegin(GL_POLYGON);
	for (float n = 0; n<360; n++)
	{
		float h = 6.28*n / 360.0;
		glVertex3f(-180 + 20 * cosf(h), 210 + 20 * sinf(h), 0);
	}
	glEnd();

	glColor3f(1, 1, 1);
	Sprint(-187, 182, "MOON");
	Sprint(-90, 10, "EARTH");
	while (k--)
	{
		glTranslatef(0, .3, 0);
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(2, 0);
		glVertex2f(2, 5);
		glVertex2f(5, 10);
		glVertex2f(5, 3);
		glEnd();

		glColor3f(188.0 / 255.0, 198.0 / 255.0, 204.0 / 255.0);
		glBegin(GL_POLYGON);
		glVertex2f(5, 3);
		glVertex2f(5, 30);
		glVertex2f(10, 30);
		glVertex2f(10, 3);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(10, 3);
		glVertex2f(10, 10);
		glVertex2f(13, 5);
		glVertex2f(13, 0);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(5, 30);
		glVertex2f(7.5, 35);
		glVertex2f(10, 30);
		glEnd();

		glColor3f(255, 250, 250);
		glBegin(GL_POINTS);
		glVertex2f(4, 0);
		glVertex2f(5, 0);
		glVertex2f(6, 0);
		glVertex2f(7, 0);
		glVertex2f(8, 0);
		glVertex2f(9, 0);
		glVertex2f(10, 0);
		glEnd();

		if (k == 1)
		{
			glColor3f(1, 0, 0);
			Sprint(-95, 15, "MISSION COMPLETE");
		}
		glFlush();
		if ((k % 90) == 0)
		{
			Sprint(-30, 15, hi[a++]);
		}

		glColor3f(51.0 / 255.0, 25.0 / 255.0, 0 / 255.0);
		glBegin(GL_POLYGON);
		glVertex2f(2, 0);
		glVertex2f(2, 5);
		glVertex2f(5, 10);
		glVertex2f(5, 3);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(5, 3);
		glVertex2f(5, 30);
		glVertex2f(10, 30);
		glVertex2f(10, 3);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(10, 3);
		glVertex2f(10, 10);
		glVertex2f(13, 5);
		glVertex2f(13, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(4, 30);
		glVertex2f(7.5, 35);
		glVertex2f(10, 30);
		glEnd();

		glRotated(0.075, 0, 0, 1);
	}
}
int main(int argc, char*argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("ROCKET");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}