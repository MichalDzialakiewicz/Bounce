#include "cScena.h"

cScena::cScena() // konstruktor
{
	kula = new cKula(2.5, 2.5, 0.5, 1);
	spawn = { 2.5,2.5 }; // punkt kontrolny
	wczytaj_plansze("plansza.txt");
}

void cScena::init(int argc, char **argv, const char *window_name) { // wyswietlenie okna
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600); // rozmiar okna
	glutInitWindowPosition(40, 40); // polozenie okna
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutCreateWindow(window_name);
	glClearColor(0, 1, 1, 1); // kolor tla
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	set_callbacks();
	glutMainLoop();
}

void cScena::resize(int width, int height) {
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void cScena::display() // zawartosc okna
{
	// ruch kamery
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (kula->get_x() > 0 && kula->get_x() < 5, 4) { // plansza poczatkowa
		gluLookAt(5.4, 5, 8, 5.4, 5, 0, 0, 1, 0);
	}
	if (kula->get_x() > 5.4 && kula->get_x() < 111.6) { // ruch
		gluLookAt(-5.4 + kula->get_x() * 1, 0.001, 0.001, -5.4 + kula->get_x() * 1, 0.001, 0, 0, 1, 0);
	}
	if (kula->get_x() > 111.6 && kula->get_x() < 117) { // plansza koncowa
		gluLookAt(106.2, 0.001, 0.001, 106.2, 0.001, 0, 0, 1, 0);
	}
	// rysowanie planszy
	glPushMatrix();
	{
		for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++) {
			std::vector<cFigura*> figury = (*itr1);
			for (std::vector<cFigura*>::iterator itr2 = figury.begin(); itr2 != figury.end(); itr2++) {
				cFigura* tmp = *itr2;
				if (tmp != 0) {
					tmp->rysuj();
				}
			}
		}
		kula->rysuj();
	}
	glutSwapBuffers();
}

void cScena::set_callbacks() { // callbacki
	glutReshapeFunc(resize_binding);
	glutDisplayFunc(display_binding);
	glutTimerFunc(40, timer_binding, 0);
	glutKeyboardFunc(key_binding);
}

void cScena::timer() // wykrywanie kolizji
{
	int j = -1;
	for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++) {
		j++;
		std::vector<cFigura*> kolumna = *itr1;
		int i = -1;
		for (std::vector<cFigura*>::iterator itr2 = kolumna.begin(); itr2 != kolumna.end(); itr2++) {
			i++;
			cFigura* tmp = *itr2;
			if (tmp == 0) {
				continue;
			}
			if (kula->kolizja(*tmp)) {
				cSciana* s = dynamic_cast<cSciana*>(tmp); // kolizja ze sciana
				if (s) {

				}
				cSlupek* p = dynamic_cast<cSlupek*>(tmp); // // kolizja ze slupkiem
				if (p) { 
					kula->set_hp(kula->get_hp() - 1);
					kula->set_x(spawn.first);
					kula->set_y(spawn.second);
					kula->ruch(0, 0);
					kula->ustaw_fizyka(0, 0);
					if (kula->get_hp() == 0) {
						std::cout << "Straciles wszystkie punkty zycia. Koniec gry." << std::endl;
						Sleep(5000);
						exit(0);
					}
					else {
						std::cout << "Pozostale punkty zycia: " << kula->get_hp() << std::endl;
					}
				}
				cZycie* z = dynamic_cast<cZycie*>(tmp); // kolizja z punktem zycia
				if (z) {
					kula->set_hp(kula->get_hp()+1);
					delete kolumna[i];
					plansza[j][i] = 0;
					std::cout << "Zdobywasz punkt zycia, masz ich teraz: " << kula->get_hp() << std::endl;
				}
			}
			
		}
	}
	kula->aktualizuj(GetTickCount());
    glutPostRedisplay();
    glutTimerFunc(40, timer_binding, 0);
}

void cScena::key(unsigned char key, int x, int y) { // sterowanie
	switch (key) {
	case 'w': // skok
	{
		kula->ruch(0.005, 90); // predkosc do ustawienia!
		break;
	}
	case 'a': // ruch w lewo
	{
		kula->ruch(0.002, 180); // predkosc do ustawienia!

		break;
	}
	case 'd': // ruch w prawo
	{
		kula->ruch(0.002, 0); // predkosc do ustawienia!
		break;
	}
	case 's': // przywrocenie kuli do poziomu podlogi
	{
		kula->set_y(znajdz_podloge());
		kula->ruch(0, 0);
		kula->ustaw_fizyka(0, 0);
		break;
	}
	case 'r': // zresetowanie rozgrywki
	{
		wczytaj_plansze("plansza.txt");
		kula = new cKula(2.5, 2.5, 0.5, 3);
		break;
	}
	}
}

void cScena::wczytaj_plansze(std::string nazwa) // wczytywanie planszy z pliku .txt
{
	std::ifstream plik;
	plik.open(nazwa);
	if (!plik.good()) {
		std::cout << "nie udalo sie otworzyc pliku" << std::endl;
	}
	else {
		double xp = -0.5;
		for (int i = 0; i < 117; i++) { // wiersz - 117 kolumn
			xp = xp + 1;
			std::vector<cFigura*> kolumna;
			double yp = 10.5;
			for (int j = 0; j < 10; j++) { // kolumna - 10 figur
				yp = yp - 1;
				char tmp;
				plik >> tmp;
				if (tmp == 's') { // wczytuje sciane
					kolumna.push_back(new cSciana(xp, yp, 1, 1));
				}
				else if (tmp == 'p') { // wczytuje slupek
					kolumna.push_back(new cSlupek(xp, yp, 0.4, 1));
				}
				else if (tmp == 'z') { // wczytuje punkt zycia
					kolumna.push_back(new cZycie(xp, yp, 0.4));
				}
				else {
					kolumna.push_back(0);
				}
			}
			plansza.push_back(kolumna);
		}
	}
	plik.close();
}
 
double cScena::znajdz_podloge() { // metoda wywolywana klawiszem 's' - przywrocenie kuli fo poziomu podlogi
	double xk = kula->get_x(); // wspolrzedna x kuli
	for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++) { // znalezienie kolumny odpowiadajacej wspolrzednej x kuli
		std::vector<cFigura*> kolumna = (*itr1);
		for (std::vector<cFigura*>::iterator itr2 = kolumna.begin(); itr2 != kolumna.end(); itr2++) {
			cFigura* tmp1 = *itr2;
			if (tmp1 == 0) {
				continue;
			}
			double xf1 = tmp1->get_x(); // wspolrzedna x pierwszej figury kolumny
			if (xk > xf1 - 0.5 && xk < xf1 + 0.5) { // sprawdzenie zawartosci x kuli w kolumnie
				double lowest_y = 9.5;
				for (std::vector<cFigura*>::iterator itr3 = kolumna.begin(); itr3 != kolumna.end(); itr3++) { // znalezienie najnizszego poziomu podlogi
					cFigura* tmp2 = *itr3;
					if (tmp2 == 0) {
						continue;
					}
					double yf = tmp2->get_y(); // wspolrzedna y figury
					cSciana* s = dynamic_cast<cSciana*>(tmp2);
					if (s) {
						if (yf<lowest_y && (*(itr3-1))==0) { //znalezienie podlogi
							lowest_y = yf+1;
							break;
						}
						else {
							continue;
						}
					}
					else {
						continue;
					}
				}
				return lowest_y;
			}
			else {
				break; // gdy pierwsza figura nie zawiera x kuli to odpada cala kolumna
			}
		}
	}
}

cScena::~cScena() {
 
}