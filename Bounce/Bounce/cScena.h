#pragma once
#include "cKula.h"
#include "cSciana.h"
#include "cObrecz.h"
#include "cSlupek.h"
#include "cBonus.h"
#include "cZycie.h"
#include <vector>

void resize_binding(int width, int height);
void idle_binding();
void display_binding();
void key_binding(unsigned char key, int x, int y);
void timer_binding(int i);

class cScena {
	cKula* kula;
	double kula_y;
	std::vector<cFigura*> figury;
	std::vector<std::vector<cFigura*>> plansza;
public:
	cScena();
	void resize(int width, int height);
	void idle();
	void display();
	void timer();
	void init(int argc, char **argv, const char* window_name);
	void set_callbacks();
	void key(unsigned char key, int x, int y);
	void wczytaj_plansze(std::string nazwa);
	~cScena();
};