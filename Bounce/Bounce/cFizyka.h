#pragma once
#include <GL/freeglut.h>
#ifndef __unix__
#include <windows.h>
#else

unsigned long long GetTickCount();

#endif
#define _USE_MATH_DEFINES
#include <cmath>

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
	float x() { return float(x_); }
	float y() { return float(y_); }
	void ustaw_x(float _x) { x_ = (int)_x; }
	void ustaw_y(float _y) { y_ = (int)_y; }
	void odbicie(float alfa_n); //odbicie od sciany charakteryzowanej za pomoca normalnej alfa_n
	void aktualizuj(int czas_aktualny); //zmienia polozenie obiektu na podstawie aktualnego czasu
	void ustaw_predkosc(float _v, float _alfa_v); //ustawia poczatkowa predkosc
	void ustaw_fizyka(float _g, float _alfa_g); //ustawia poczatkowe przyspieszenie
	void ustaw_geometria(float _x, float _y, float _xa, float _ya, float _xb, float _yb);
	virtual int kolizja(cFizyka &X); //wykrywanie kolizji z innym obiektem (funkcja przekazuje 1 gdy jest kolizja 0 gdy brak)
	int w_prosokacie(float _x, float _y, const cFizyka &X);//wykrywa czy dany punkt (_x,_y) znajduje sie wewnatrz pewnego kwadratu
	float odleglosc(float _x, float _y, float _xa, float _ya, float _xb, float _yb);//wyznacza odleglosc od pewnej prostej przechodzacej przez 2 punkty
	virtual float znajdz_normalna(const cFizyka &X);//znajduje normalna boku ktory jest najblizej srodka obiektu (wynikiem funkcji jest orientacja normalnej);
	void reset(); //resetuje czas_
};