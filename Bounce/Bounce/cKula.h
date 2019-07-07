#pragma once
#include "cFigura.h"

class cKula : public cFigura {
	double r_;
	int hp_;
public:
	cKula(double x, double y, double r_, int hp);
	void rysuj();
	void ruch(double dv, double dalfa_v);
	int get_hp() const;
	void set_hp(int hp);
};