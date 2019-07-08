#include "cObrecz.h"

cObrecz::cObrecz(double x, double y, double a, double b, int aktywnosc) : cFigura(x, y), a_(a), b_(b), aktywnosc_(aktywnosc) {
	obwiednia(x, y, -a_ / 2, -b_ / 2, a_ / 2, b_ / 2);
}

void cObrecz::rysuj() 
{
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	if (aktywnosc_ == 1) { // obrecz niezaliczona
		glColor3d(1, 1, 0); // kolor do ustawienia!
	}
	else { // obrecz zaliczona
		glColor3d(0.4, 0.4, 0.4); // kolor do ustawienia!
	}
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

int cObrecz::get_aktywnosc() const {
	return aktywnosc_;
}

void cObrecz::set_aktywnosc(int aktywnosc) {
	aktywnosc_ = aktywnosc;
}