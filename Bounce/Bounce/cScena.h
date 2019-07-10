#pragma once
#include "cKula.h"
#include "cSciana.h"
#include "cFloor.h"
#include "cPrzeszkoda.h"
#include "cObrecz.h"
#include "cCheckpoint.h"
#include "cZycie.h"
#include "cWyjscie.h"

void resize_binding(int width, int height);
void display_binding();
void key_binding(unsigned char key, int x, int y);
void timer_binding(int i);

class cScena {
	cKula* kula;
	std::pair<double, double> checkpoint;
	int l_obreczy;
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
	void zasady();
	~cScena();
};