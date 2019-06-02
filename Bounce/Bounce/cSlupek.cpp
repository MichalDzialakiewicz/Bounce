#include "cSlupek.h"

cSlupek::cSlupek(double x, double y, double a, double b): cFigura(x, y), a_(a), b_(b) {

}

void cSlupek::rysuj() {
	glPushMatrix();

	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);

	glColor3d(0, 0, 0); //do ustawienia

	glBegin(GL_POLYGON); //do ustawienia
	{
		glVertex3d(-a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, -b_ / 2, 0);
		glVertex3d(-a_ / 2, -b_ / 2, 0);
	}
	glEnd();
	glPopMatrix();
}