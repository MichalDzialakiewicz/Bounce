#pragma once
#include "stdlib.h"
#include "cKula.h"
#include "cSciana.h"
#include "cObrecz.h"
#include "cSlupek.h"
#include "cBonus.h"
#include "cZycie.h"

void resize_binding(int width, int height);
void display_binding();
void key_binding(unsigned char key, int x, int y);
void timer_binding(int i);

class cScena {
	cKula* kula;
	std::pair<double, double> spawn;
	std::vector<std::vector<cFigura*>> plansza;
public:
	cScena();
	void init(int argc, char **argv, const char* window_name);
	void resize(int width, int height);
	void display();
	void set_callbacks();
	void timer();
	void key(unsigned char key, int x, int y);
	void wczytaj_plansze(std::string nazwa);
	double znajdz_podloge();
	~cScena();
};