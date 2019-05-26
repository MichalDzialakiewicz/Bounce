#pragma once
#include "cFigura.h"

class cSciana : public cFigura {
	double a_, b_;
public:
	cSciana(double a, double b);
	void rysuj();
};