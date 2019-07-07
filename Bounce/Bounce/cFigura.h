#pragma once
#include "cFizyka.h"

class cFigura : public cFizyka {
public:
	cFigura(double x, double y);
	virtual void rysuj() = 0;
	double get_x() const;
	void set_x(double x);
	double get_y() const;
	void set_y(double y);
};