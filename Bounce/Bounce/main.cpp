#include "cScena.h"
cScena scena;

void resize_binding(int width, int height) {
	scena.resize(width, height);
}
void idle_binding() {
	//scena.idle();
}
void display_binding() {
	scena.display();
}
void key_binding(unsigned char key, int x, int y) {
	scena.key(key, x, y);
}
void timer_binding(int i) {
	scena.timer();
}

int main(int argc, char *argv[])
{
	scena.init(argc, argv, "Okno sceny");
	return 0;
}