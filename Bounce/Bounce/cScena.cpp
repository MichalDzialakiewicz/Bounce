#include "cScena.h"

cScena::cScena() // konstruktor
{
	kula = new cKula(2.5, 2.5, 0.5, 3);
	checkpoint = { 2.5,2.5 }; // punkt kontrolny
	l_obreczy = 0; // liczba zaliczonych obreczy
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

void cScena::timer()
{
	// wykrywanie kolizji
	int i = -1;
	for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++) {
		i++;
		std::vector<cFigura*> kolumna = *itr1;
		int j = -1;
		for (std::vector<cFigura*>::iterator itr2 = kolumna.begin(); itr2 != kolumna.end(); itr2++) {
			j++;
			cFigura* tmp = *itr2;
			if (tmp == 0) {
				continue;
			}
			if (kula->kolizja(*tmp)) {
				cSciana* s = dynamic_cast<cSciana*>(tmp); // kolizja ze sciana
				if (s) {
					break;
				}
				cFloor* f = dynamic_cast<cFloor*>(tmp); // kolizja z podloga
				if (f) {
					kula->ruch(0, 0);
					kula->grawitacja(0, 0);
					kula->set_y(znajdz_podloge());
					break;
				}
				cPrzeszkoda* p = dynamic_cast<cPrzeszkoda*>(tmp); // kolizja z przeszkoda
				if (p) { 
					kula->set_hp(kula->get_hp() - 1);
					kula->set_x(checkpoint.first);
					kula->set_y(checkpoint.second);
					kula->ruch(0, 0);
					kula->grawitacja(0, 0);
					if (kula->get_hp() == 0) {
						std::cout << "Straciles wszystkie punkty zycia. Koniec gry." << std::endl;
						Sleep(5000);
						exit(0);
					}
					else {
						std::cout << "Pozostale punkty zycia: " << kula->get_hp() << std::endl;
					}
					break;
				}
				cObrecz* o = dynamic_cast<cObrecz*>(tmp); // kolizja z obrecza
				if (o) {
					if (o->get_aktywnosc() == 1) {
						o->set_aktywnosc(0);
						l_obreczy++;
						std::cout << "Zaliczone obrecze: " << l_obreczy << std::endl;
					}
					break;
				}
				cCheckpoint* c = dynamic_cast<cCheckpoint*>(tmp); // kolizja z punktem kontrolnym
				if (c) {
					if (c->get_aktywnosc() == 0) {
						c->set_aktywnosc(1);
						checkpoint.first = c->get_x();
						checkpoint.second = znajdz_podloge();
						std::cout << "Punkt kontrolny odblkowany." << std::endl;
					}
					break;
				}
				cZycie* z = dynamic_cast<cZycie*>(tmp); // kolizja z punktem zycia
				if (z) {
					kula->set_hp(kula->get_hp()+1);
					delete kolumna[j];
					plansza[i][j] = 0;
					std::cout << "Zdobywasz punkt zycia, masz ich teraz: " << kula->get_hp() << std::endl;
					break;
				}
				cWyjscie* w = dynamic_cast<cWyjscie*>(tmp); // kolizja z wyjsciem
				if (w) {
					if (l_obreczy == 6) {
						kula->ruch(0, 0);
						kula->grawitacja(0, 0);
						std::cout << "Gratulacje, przeszedles gre." << std::endl;
						Sleep(5000);
						exit(0);
					}
					else {
						std::cout << "Nie zaliczyles wszystkich obreczy." << std::endl;
					}
					break;
				}
			}
			
		}
	}
	// wykrywanie podloza pod kula
	if (kula->get_g() == 0 && kula->get_y() != znajdz_podloge()) { // sprawdzenie kiedy kula nie ma przyspieszenia i nie jest na najnizszym mozliwym podlozu
		kula->grawitacja(8.81*1E-6, -90); // upadek na podloze
	}
	kula->aktualizuj(GetTickCount());
    glutPostRedisplay();
    glutTimerFunc(40, timer_binding, 0);
}

void cScena::key(unsigned char key, int x, int y) { // sterowanie
	switch (key) {
	case 'w': // skok
	{
		if (kula->get_g() == 0) { // zablokowanie wielokrotnego skoku
			kula->ruch(0.009, 90); // predkosc do ustawienia!
		}
		break;
	}
	case 'a': // ruch w lewo
	{
		if (kula->get_g() == 0) { // ruch na podloze
			kula->ruch(0.002, 180); // predkosc do ustawienia!
		}
		else { // ruch w trakcie skoku
			kula->ruch(0.004, 180); // predkosc do ustawienia!
		}
		break;
	}
	case 'd': // ruch w prawo
	{
		if (kula->get_g() == 0) { // ruch na podlodze
			kula->ruch(0.002, 0); // predkosc do ustawienia!
		}
		else { // ruch w trakcie skoku
			kula->ruch(0.004, 0); // predkosc do ustawienia!
		}
		break;
	}
	case 's': // awaryjne przywrocenie kuli do poziomu podlogi
	{
		kula->set_y(znajdz_podloge());
		kula->ruch(0, 0);
		kula->grawitacja(0, 0);
		break;
	}
	case 'r': // zresetowanie rozgrywki
	{
		kula = new cKula(2.5, 2.5, 0.5, 3);
		checkpoint.first = 2.5;
		checkpoint.second = 2.5;
		l_obreczy = 0;
		wczytaj_plansze("plansza.txt");
		// przywrocenie zaliczonych obreczy i punktow kontrolnych do stanu bazowego
		for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++) {
			std::vector<cFigura*> kolumna = *itr1;
			for (std::vector<cFigura*>::iterator itr2 = kolumna.begin(); itr2 != kolumna.end(); itr2++) {
				cFigura* tmp = *itr2;
				if (tmp == 0) {
					continue;
				}
				cCheckpoint* c = dynamic_cast<cCheckpoint*>(tmp);
				if (c) {
					c->set_aktywnosc(0);
				}
				cObrecz* o = dynamic_cast<cObrecz*>(tmp);
				if (o) {
					o->set_aktywnosc(1);
				}
			}
		}
		break;
	}
	case 'b': // powrot do punktu kontrolnego
	{
		kula->set_x(checkpoint.first);
		kula->set_y(checkpoint.second);
		kula->ruch(0, 0);
		kula->grawitacja(0, 0);
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
				else if (tmp == 'f') { // wczytuje podloge
					kolumna.push_back(new cFloor(xp, yp, 1, 1));
				}
				else if (tmp == 'p') { // wczytuje przeszkode
					kolumna.push_back(new cPrzeszkoda(xp, yp-0.5, 0.4, 0.9));
				}
				else if (tmp == 'o') { // wczytuje obrecz
					if (xp == 97.5 || xp == 101.5) { // pozioma
						kolumna.push_back(new cObrecz(xp+0.5, yp, 2, 0.4, 1));
					}
					else { // pionowa
						kolumna.push_back(new cObrecz(xp, yp-0.5, 0.4, 2, 1));
					}
				}
				else if (tmp == 'c') { // wczytuje punkt kontrolny
					kolumna.push_back(new cCheckpoint(xp, yp, 1, 1, 0));
				}
				else if (tmp == 'z') { // wczytuje punkt zycia
					kolumna.push_back(new cZycie(xp, yp, 0.4));
				}
				else if (tmp == 'w') { // wczytuje wyjscie
					kolumna.push_back(new cWyjscie(xp, yp, 1, 1));
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
			double xf = tmp1->get_x(); // wspolrzedna x pierwszej figury kolumny
			if (xk > xf - 0.5 && xk < xf + 0.5) { // sprawdzenie zawartosci x kuli w kolumnie
				double lowest_y = 9.5;
				for (std::vector<cFigura*>::iterator itr3 = kolumna.begin(); itr3 != kolumna.end(); itr3++) { // znalezienie najnizszego poziomu podlogi
					cFigura* tmp2 = *itr3;
					if (tmp2 == 0) {
						continue;
					}
					double yf = tmp2->get_y(); // wspolrzedna y figury
					cFloor* f = dynamic_cast<cFloor*>(tmp2);
					if (f) { //znalezienie podlogi
						if (yf<lowest_y && (*(itr3-1))==0) {
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