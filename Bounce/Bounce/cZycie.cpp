#include "cZycie.h"

cZycie::cZycie(double x, double y, double r) : cFigura(x, y), r_(r) {

}

void cZycie::rysuj() {
	glPushMatrix();

	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);

	glColor3d(0, 0, 0); //do ustawienia

	glBegin(GL_POLYGON); //do ustawienia
	{
		float precyzja = 0.0005;
		for (float kat = 0; kat <= 2 * M_PI; kat += precyzja)
		{
			float X = x_ + (r_*static_cast<float>(sin(kat)));
			float Y = y_ + (r_*static_cast<float>(cos(kat)));
			glVertex3f(X, Y, -5);
		}
	}
	glEnd();
	glPopMatrix();
}