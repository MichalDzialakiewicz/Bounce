#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#ifndef __unix__
#include <windows.h>
#else

unsigned long long GetTickCount();

#endif

typedef struct sGranica {
	float xa;
	float ya;
	float xb;
	float yb;
} sGranica;

class cFizyka {
protected:
	int czas_;
	sGranica granica_;
	float x_, y_;
	float v_;
	float alfa_v_;
	float g_;
	float alfa_g_;
public:
	cFizyka(double x, double y);
	// metody kolizji
	virtual int kolizja(cFizyka &X);
	int w_prosokacie(float _x, float _y, const cFizyka &X);
	virtual float znajdz_normalna(const cFizyka &X);
	float odleglosc(float x, float y, float xa, float ya, float xb, float yb);
	void odbicie(float alfa_n);
	void aktualizuj(int czas_aktualny);
	// settery do konstruktora
	void predkosc(float v, float alfa_v);
	void grawitacja(float g, float alfa_g);
	void obwiednia(float x, float y, float xa, float ya, float xb, float yb);
	void reset();
};