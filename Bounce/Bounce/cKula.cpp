#include "cKula.h"

cKula::cKula(double x, double y, double r, int hp) : cFigura(x, y), r_(r), hp_(hp) {
	obwiednia(x, y, -r, -r, r, r);
}

void cKula::rysuj()
{
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glRotated(0, 1, 0, 0);
	glRotated(0, 0, 1, 0);
	glRotated(0, 0, 0, 1);
	if (hp_ == 4) {
		glColor3d(1, 0, 0);
	}
	else if (hp_ == 3) {
		glColor3d(0.8, 0, 0);
	}
	else if (hp_ == 2) {
		glColor3d(0.6, 0, 0);
	}
	else if (hp_ == 1) {
		glColor3d(0.4, 0, 0);
	}
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
		this->predkosc(dv, dalfa_v);
		this->grawitacja(7.81*1E-6, -90);
	}
	else {
		this->predkosc(dv, dalfa_v);
	}
}

int cKula::get_hp() const {
	return hp_;
}

void cKula::set_hp(int hp) {
	hp_ = hp;
}

double cKula::get_v() const {
	return v_;
}
double cKula::get_g() const {
	return g_;
}