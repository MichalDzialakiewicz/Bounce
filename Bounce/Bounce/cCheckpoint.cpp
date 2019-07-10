#include "cCheckpoint.h"

cCheckpoint::cCheckpoint(double x, double y, double a, double b, int aktywnosc) : cFigura(x,y), a_(a), b_(b), aktywnosc_(aktywnosc) {
	obwiednia(x, y, -a_ / 2, -b_ / 2, a_ / 2, b_ / 2);
}

void cCheckpoint::rysuj() {
	if (aktywnosc_ == 1) { // punkt kontrolny aktywowany
		glPushMatrix();
		glTranslated(x_, y_, 0);
		glRotated(0, 1, 0, 0);
		glRotated(0, 0, 1, 0);
		glRotated(0, 0, 0, 1);
		glColor3d(0, 1, 0);
		glBegin(GL_POLYGON);
		{
			glVertex3d(0, b_ / 3, 0);
			glVertex3d(a_ / 3, 0, 0);
			glVertex3d(0, -b_ / 3, 0);
			glVertex3d(-a_ / 3, 0, 0);
		}
		glEnd();
		glPopMatrix();
	}
	// punkt kontrolny nieaktywowany
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	glColor3d(1, 1, 0);
	glBegin(GL_POLYGON);
	{
		glVertex3d(0, b_ / 2, 0);
		glVertex3d(a_ / 2, 0, 0);
		glVertex3d(0, -b_ / 2, 0);
		glVertex3d(-a_ / 2, 0, 0);
	}
	glEnd();
	glPopMatrix();
}

int cCheckpoint::get_aktywnosc() const {
	return aktywnosc_;
}

void cCheckpoint::set_aktywnosc(int aktywnosc) {
	aktywnosc_ = aktywnosc;
}