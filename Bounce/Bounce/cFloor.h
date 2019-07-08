#pragma once
#include "cFigura.h"

class cFloor : public cFigura {
	double a_, b_;
public:
	cFloor(double x, double y, double a, double b);
	void rysuj();
};
