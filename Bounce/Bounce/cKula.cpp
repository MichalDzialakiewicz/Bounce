#include "cKula.h"

cKula::cKula(double x, double y, double r, int hp) : cFigura(x, y), r_(r), hp_(hp) {
	ustaw_geometria(x, y, -r, -r, r, r);
}

void cKula::rysuj() {
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	glColor3d(0.7, 0, 0); // kolor do ustawienia!
	glBegin(GL_POLYGON);
	{
		float precyzja = 0.0005;
		for (float kat = 0; kat <= 2 * M_PI; kat += precyzja) {
			float X = r_*(sin(kat));
			float Y = r_*(cos(kat));
			glVertex3d(X, Y, 0);
		}
	}
	glEnd();
	glPopMatrix();
}

void cKula::ruch(double dv, double dalfa_v) { 
	if (dalfa_v == 90) {
		this->ustaw_predkosc(dv, dalfa_v);
		this->ustaw_fizyka(9.81*1E-6, -90); // grawitacja do ustawienia!
	}
	else {
		this->ustaw_predkosc(dv, dalfa_v);
	}
}

int cKula::get_hp() const {
	return hp_;
}

void cKula::set_hp(int hp) {
	hp_ = hp;
}