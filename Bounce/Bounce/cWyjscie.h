#pragma once
#include "cFigura.h"

class cWyjscie : public cFigura {
	double a_, b_;
public:
	cWyjscie(double x, double y, double a, double b);
	void rysuj();
};
