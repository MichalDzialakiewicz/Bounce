#pragma once
#include "cFizyka.h"

class cFigura : public cFizyka {
protected:
	double x_, y_;
public:
	cFigura(double x, double y);
	virtual void rysuj() = 0;
};