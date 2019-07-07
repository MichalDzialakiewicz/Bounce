#include "cFigura.h"

cFigura::cFigura(double x, double y): cFizyka(x,y) {

}

double cFigura::get_x() const {
	return x_;
}

void cFigura::set_x(double x) {
	x_ = x;
}
double cFigura::get_y() const {
	return y_;
}
void cFigura::set_y(double y) {
	y_ = y;
}