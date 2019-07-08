#include "cPrzeszkoda.h"

cPrzeszkoda::cPrzeszkoda(double x, double y, double a, double b): cFigura(x, y), a_(a), b_(b) {
	obwiednia(x, y, -a/2, 0, a/2, b);
}

void cPrzeszkoda::rysuj() {
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	glColor3d(1, 0.4, 0); // kolor do ustawienia!
	glBegin(GL_POLYGON);
	{
		glVertex3d(-a_/2, b_, 0);
		glVertex3d(a_/2, b_, 0);
		glVertex3d(a_/2, 0, 0);
		glVertex3d(-a_/2, 0, 0);
	}
	glEnd();
	glPopMatrix();
}