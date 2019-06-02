#include "cKula.h"

cKula::cKula(double x, double y, double r, int hp) : cFigura(x, y), r_(r), hp_(hp) {
	ustaw_geometria(x, y, -0.25, -0.25, 0.25, 0.25);
}

void cKula::rysuj() {
	glPushMatrix();

	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);

	glColor3d(1, 0, 0); //do ustawienia

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

void cKula::ruch(double dv, double dalfa_v) {
	if (dalfa_v == 90) {
		this->ustaw_predkosc(dv, dalfa_v);
		this->ustaw_fizyka(9.81*1E-6, -90);
	}
	else {
		this->ustaw_predkosc(dv, dalfa_v);
	}
}

void cKula::powrot(double dy) {
	y_ += dy;
}

double cKula::get_y() const {
	return y_;
}
void cKula::set_y(double y) {
	y_ = y;
}