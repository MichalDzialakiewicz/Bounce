#include "cFloor.h"

cFloor::cFloor(double x, double y, double a, double b) : cFigura(x, y), a_(a), b_(b) {
	obwiednia(x, y, -a_ / 2.5, -b_ / 2.5, a_ / 2.5, b_ / 2.5);
}

void cFloor::rysuj() {
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	glColor3d(1, 0, 0.2);
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