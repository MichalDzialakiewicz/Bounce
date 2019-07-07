#include "cSciana.h"

cSciana::cSciana(double x, double y, double a, double b) : cFigura(x, y), a_(a), b_(b) {
	ustaw_geometria(x, y, -a/2, -b/2, a/2, b/2);
}

void cSciana::rysuj() {
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	glColor3d(1, 0, 0); // kolor do ustawienia!
	glBegin(GL_POLYGON);
	{
		glVertex3d(-a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, -b_ / 2, 0);
		glVertex3d(-a_ / 2, -b_ / 2, 0);
	}
	glEnd();
	glPopMatrix();
}