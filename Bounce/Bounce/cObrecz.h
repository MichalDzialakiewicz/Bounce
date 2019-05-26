#pragma once
#include "cFigura.h"

class cObrecz : public cFigura {
	double a_, b_;
public:
	cObrecz(double a, double b);
	void rysuj();
};