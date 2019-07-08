#include "cFizyka.h"
#include "cScena.h"
#ifndef __unix__
  #include <windows.h>
#else
#include<chrono>
unsigned long long GetTickCount()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}
#endif

cFizyka::cFizyka(double x, double y): x_(x),y_(y) { // konstruktor
	v_ = 0;
	alfa_v_ = 0;
    g_=0;
    alfa_g_=0;
    // ustawia domyslna obwiednie obiektu
    granica_.xa=-0.5;
    granica_.ya=-0.5;
    granica_.xb= 0.5;
    granica_.yb= 0.5;
    reset(); // ustawia czas
}

int cFizyka::kolizja(cFizyka &X) //wykrywanie kolizji z obiektem
{
	// jesli wystepuje kolizja to przynajmniej jeden z wierzcholkow kuli musi zawierac sie wewnatrz obiektu
	// sprawdzenie czy ktorys z wierzcholkow obiektu nie zawiera sie w kuli
	int kolizja = 0;
	if (&X == 0) kolizja = 0;
	else if (w_prosokacie(x_ + granica_.xa, y_ + granica_.ya, X) == 1) kolizja = 1;
	else if (w_prosokacie(x_ + granica_.xa, y_ + granica_.yb, X) == 1) kolizja = 1;
	else if (w_prosokacie(x_ + granica_.xb, y_ + granica_.yb, X) == 1) kolizja = 1;
	else if (w_prosokacie(x_ + granica_.xb, y_ + granica_.ya, X) == 1) kolizja = 1;
	// sprawdzenie czy ktorys z wierzcholkow kuli nie zawiera sie w obiekcie
	else if (w_prosokacie(X.x_ + X.granica_.xa, X.y_ + X.granica_.ya, *this) == 1) kolizja = 1;
	else if (w_prosokacie(X.x_ + X.granica_.xa, X.y_ + X.granica_.yb, *this) == 1) kolizja = 1;
	else if (w_prosokacie(X.x_ + X.granica_.xb, X.y_ + X.granica_.yb, *this) == 1) kolizja = 1;
	else if (w_prosokacie(X.x_ + X.granica_.xb, X.y_ + X.granica_.ya, *this) == 1) kolizja = 1;
	// obsluga kolizji
	if (kolizja) // wystapienie kolizji = 1
	{
		cSciana* s = dynamic_cast<cSciana*>(&X); // odbicie od sciany
		if (s) {
			float alfa_n = znajdz_normalna(X);
			odbicie(alfa_n);
			float kat = (alfa_n > 0) ? alfa_n - 180 : alfa_n + 180;
			X.odbicie(kat);
			return kolizja;
		}
		cFloor* f = dynamic_cast<cFloor*>(&X); // brak odbicia od podlogi
		if (f) {
			return kolizja;
		}
		cPrzeszkoda* p = dynamic_cast<cPrzeszkoda*>(&X); // brak odbicia od przeszkody
		if (p) {
			return kolizja;
		}
		cObrecz* o = dynamic_cast<cObrecz*>(&X); // brak odbicia od obreczy
		if (o) {
			return kolizja;
		}
		cCheckpoint* c = dynamic_cast<cCheckpoint*>(&X); // brak odbicia od punktu kontrolnego
		if (c) {
			return kolizja;
		}
		cZycie* z = dynamic_cast<cZycie*>(&X); // brak odbicia od punktu zycia
		if (z) {
			return kolizja;
		}
		cWyjscie* w = dynamic_cast<cWyjscie*>(&X); // brak odbicia od wyjscia
		if (w) {
			return kolizja;
		}
	}
	else {
		return kolizja; // brak kolizji = 0
	}
}

int cFizyka::w_prosokacie(float x, float y, const cFizyka &X) //wykrywa czy dany punkt znajduje sie wewnatrz obiektu
{
	if (((x < X.x_ + X.granica_.xb) && (x > X.x_ + X.granica_.xa)) && ((y < X.y_ + X.granica_.yb) && (y > X.y_ + X.granica_.ya))) {
		return 1;
	}
	else {
		return 0;
	}
}

float cFizyka::znajdz_normalna(const cFizyka &X) // znajduje normalna boku ktory jest najblizej srodka obiektu
{
	// tablica zawierajaca odleglosci srodka obiektu od bokow, przyjmuje sie ze odbicie nastepuje od boku lezacego najblizej srodka obiektu
	float tab[4];
	int min_idx = 0;
	tab[0] = odleglosc(x_, y_, X.x_ + X.granica_.xa, X.y_ + X.granica_.ya, X.x_ + X.granica_.xa, X.y_ + X.granica_.yb);
	tab[1] = odleglosc(x_, y_, X.x_ + X.granica_.xa, X.y_ + X.granica_.yb, X.x_ + X.granica_.xb, X.y_ + X.granica_.yb);
	tab[2] = odleglosc(x_, y_, X.x_ + X.granica_.xb, X.y_ + X.granica_.yb, X.x_ + X.granica_.xb, X.y_ + X.granica_.ya);
	tab[3] = odleglosc(x_, y_, X.x_ + X.granica_.xb, X.y_ + X.granica_.ya, X.x_ + X.granica_.xa, X.y_ + X.granica_.ya);
	// poszukiwanie minimalnej wartosci odleglosci
	for (int i = 1; i < 4; i++) {
		if (tab[i] < tab[min_idx]) {
			min_idx = i;
		}
	}
	// wyznaczenie normalnych najblizej lezacego boku
	switch (min_idx)
	{
	case 0: return 180;
	case 1: return 90;
	case 2: return 0;
	case 3: return -90;
	}
}

float cFizyka::odleglosc(float x, float y, float xa, float ya, float xb, float yb) // wyznacza odleglosc od pewnej prostej przechodzacej przez dwa punkty
{
	// rownanie prostej przechodzacej przez dwa punkty: y_=Ax+B
	float d;
	if (xb != xa)
	{
		float A = (yb - ya)/(xb - xa);
		float B = ya - A*xa;
		// wyznaczenie odleglosci
		d = fabs(A*x - y + B)/sqrt(A*A + 1);
	}
	else
		d = fabs(x-xb);
	return d;
}

void cFizyka::odbicie(float alfa_n) // odbicie od sciany charakteryzowanej za pomoca normalnej alfa_n
{
    //prawo odbicia - kat padania rowny katowi odbicia
	if (fabs(alfa_n - alfa_v_) > 90) {
		alfa_v_ = alfa_n - (180 + alfa_v_ - alfa_n);
	}
}

void cFizyka::aktualizuj(int czas_aktualny) // zmienia polozenie obiektu na podstawie aktualnego czasu
{
    float delta_t = czas_aktualny - czas_, v_x, v_y;
	if (delta_t > 1000) { //dla przerwy dluzszej niz 1s nie przeprowadzana jest aktualizacja
		delta_t = 100;
	}
    v_x = v_*cos(alfa_v_/180.0*M_PI);
    v_y = v_*sin(alfa_v_/180.0*M_PI);
    x_ = x_+ v_x*delta_t + 0.5*g_*cos(alfa_g_/180.0*M_PI)*delta_t*delta_t;
    y_ = y_+ v_y*delta_t + 0.5*g_*sin(alfa_g_/180.0*M_PI)*delta_t*delta_t;
    //aktualizacja predkosci
    v_x = v_x + g_*cos(alfa_g_/180.0*M_PI)*delta_t;
    v_y = v_y + g_*sin(alfa_g_/180.0*M_PI)*delta_t;
    //wypadkowa predkosc
    v_ = sqrt(v_x*v_x+v_y*v_y);
    //kierunek predkosci
    alfa_v_ = atan2(v_y,v_x)*180.0/M_PI;
    czas_ += delta_t;
}

void cFizyka::predkosc(float v, float alfa_v) // ustawia poczatkowa predkosc
{
    v_=v;
    alfa_v_=alfa_v;
    reset();
}

void cFizyka::grawitacja(float g, float alfa_g) // ustawia poczatkowe przyspieszenie
{
    g_=g;
    alfa_g_=alfa_g;
    reset();
}

void cFizyka::obwiednia(float x, float y, float xa, float ya, float xb, float yb) // ustawia obwiednie
{
    x_=x;
    y_=y;
    granica_.xa=xa;
    granica_.xb=xb;
    granica_.ya=ya;
    granica_.yb=yb;
    reset();
}

void cFizyka::reset() // resetuje czas
{
    czas_=GetTickCount();
}