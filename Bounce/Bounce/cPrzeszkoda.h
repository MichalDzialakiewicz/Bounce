#pragma once
#include "cFigura.h"

class cPrzeszkoda : public cFigura {
	double a_, b_;
public:
	cPrzeszkoda(double x, double y, double a, double b);
	void rysuj();
};