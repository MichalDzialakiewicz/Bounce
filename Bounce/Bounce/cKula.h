#pragma once
#include "cFigura.h"

class cKula : public cFigura {
	double r_;
	int hp_;
public:
	cKula(int hp, double r_);
	void rysuj();
	void ruch(double dv, double dalfa_v);
};