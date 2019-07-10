#include "cScena.h"
cScena scena;

// bindingi do callbackow
void resize_binding(int width, int height) {
	scena.resize(width, height);
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
	scena.zasady();
	scena.init(argc, argv, "Okno sceny");
	return 0;
}