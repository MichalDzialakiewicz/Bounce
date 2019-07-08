#pragma once
#include "cFigura.h"

class cObrecz : public cFigura {
	double a_, b_;
	int aktywnosc_;
public:
	cObrecz(double x, double y, double a, double b, int aktywnosc);
	void rysuj();
	int get_aktywnosc() const;
	void set_aktywnosc(int aktywnosc);
};