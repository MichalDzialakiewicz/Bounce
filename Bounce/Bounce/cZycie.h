#pragma once
#include "cFigura.h"

class cZycie : public cFigura {
	double r_;
public:
	cZycie(double r);
	void rysuj();
};