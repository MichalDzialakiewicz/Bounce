#pragma once
#include "cFigura.h"

class cZycie : public cFigura {
	double r_;
public:
	cZycie(double x, double y, double r);
	void rysuj();
};