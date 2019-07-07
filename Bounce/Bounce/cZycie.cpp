#include "cZycie.h"

cZycie::cZycie(double x, double y, double r) : cFigura(x, y), r_(r) {
	ustaw_geometria(x, y, -r, -r, r, r);
}

void cZycie::rysuj() {
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	glColor3d(0, 0, 1); // kolor do ustawienia!
	glBegin(GL_POLYGON);
	{
		float precyzja = 0.0005;
		for (float kat = 0; kat <= 2 * M_PI; kat += precyzja) {
			float X = r_ * (sin(kat));
			float Y = r_ * (cos(kat));
			glVertex3d(X, Y, 0);
		}
	}
	glEnd();
	glPopMatrix();
}