#pragma once
#include "cFigura.h"

class cSciana : public cFigura {
	double a_, b_;
public:
	cSciana(double x, double y, double a, double b);
	void rysuj();
};