#pragma once
#include "cFigura.h"

class cKula : public cFigura {
	double r_;
	int hp_;
public:
	cKula(double x, double y, double r_, int hp);
	void rysuj();
	void ruch(double dv, double dalfa_v);
	void powrot(double dy);
	double get_y() const;
	void set_y(double y);
};