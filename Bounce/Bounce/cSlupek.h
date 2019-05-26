#pragma once
#include "cFigura.h"

class cSlupek : public cFigura {
	double a_, b_;
public:
	cSlupek(double a, double b);
	void rysuj();
};