#pragma once
#include "cFizyka.h"

class cFigura : public cFizyka {
public:
	cFigura(double x, double y);
	virtual void rysuj() = 0;
};