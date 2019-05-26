#pragma once
#include "cFigura.h"

class cBonus : public cFigura {
	double a_, b_;
public:
	cBonus(double a, double b);
	void rysuj();
};