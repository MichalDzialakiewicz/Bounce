#include "cScena.h"

cScena::cScena() {
	wczytaj_plansze("plansza.txt");
	kula = new cKula(0, -1.5625, 0.625, 3);
	//kula->ustaw_predkosc(0.000001, 90);
	//kula->ustaw_fizyka(4.81*1E-6, -90);
	//figury.push_back(new cSciana(0, -1, 1, 0.5));
	//figury.push_back(new cSciana(1.5, -1, 1, 0.5));
}

void cScena::resize(int width, int height) {
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void cScena::timer() {
	for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++)
	{
		std::vector<cFigura*>tmp = *itr1;
		for (std::vector<cFigura*>::iterator itr2 = tmp.begin(); itr2 != tmp.end(); itr2++)
		{
			if (kula->kolizja(*(*itr2)))
			{
				cSciana* s = dynamic_cast<cSciana*>(*itr2);
				if (s) {
					kula->ruch(0, 0);
					kula->ustaw_fizyka(9.81*1E-6, -90);
					break;
				}
			}
		}
	}
	kula->aktualizuj(GetTickCount());
    glutPostRedisplay();
    glutTimerFunc(40, timer_binding, 0);
}


void cScena::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    {
		for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++) {
			std::vector<cFigura*> figury = (*itr1);
			for (std::vector<cFigura*>::iterator itr2 = figury.begin(); itr2 != figury.end(); itr2++)
			{
				if (*itr2 != 0) {
					(*itr2)->rysuj();
				}
			}
		}
		kula->rysuj();
    }
    glPopMatrix();
	glutSwapBuffers();
}

void cScena::set_callbacks() {
    glutReshapeFunc(resize_binding);
    glutDisplayFunc(display_binding);
    glutTimerFunc(40, timer_binding, 0);
    glutKeyboardFunc(key_binding);
}

void cScena::init(int argc, char **argv, const char *window_name) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(40, 40);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutCreateWindow(window_name);
    glClearColor(0, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    set_callbacks();
    glutMainLoop();
}

void cScena::key(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
	{
		kula->ruch(0.005, 90);
		break;
	}
	case 'a':
	{
		kula->ruch(0.001, 180);
		break;
	}
	case 'd':
	{
		kula->ruch(0.001, 0);
		break;
	}
	case 's':
		kula->set_y(znajdz_poziom());
		kula->ruch(0, 0);
		kula->ustaw_fizyka(0, 0);
		break;
	}
}

void cScena::wczytaj_plansze(std::string nazwa)
{
	std::ifstream plik;
	plik.open(nazwa);
	if (!plik.good()) {
		std::cout << "nie udalo sie otworzyc pliku" << std::endl;
	}
	else {
		double xp = -4.0625;
		for (int i = 0; i < 116; i++) {
			xp = xp + 0.625;
			std::vector<cFigura*> kolumna;
			double yp = 3.4375;
			for (int j = 0; j < 10; j++) {
				yp = yp - 0.625;
				char tmp;
				plik >> tmp;
				if (tmp == 's') {
					kolumna.push_back(new cSciana(xp, yp, 0.625, 0.625));
				}
				else {
					kolumna.push_back(0);
				}
			}
			plansza.push_back(kolumna);
		}
	}
}
 
double cScena::znajdz_poziom() {
	double xk = kula->get_x();
	for (std::vector<std::vector<cFigura*>>::iterator itr1 = plansza.begin(); itr1 != plansza.end(); itr1++) 
	{
		std::vector<cFigura*> figury1 = (*itr1);
		for (std::vector<cFigura*>::iterator itr2 = figury1.begin(); itr2 != figury1.end(); itr2++)
		{
			cFigura* tmp1 = *itr2;
			if (tmp1 == 0) continue;
			double xf1 = tmp1->get_x();
			if (xk > xf1 - 0.3125 && xk < xf1 + 0.3125) {
				double lowest_y = 2.8125;
				for (std::vector<cFigura*>::iterator itr3 = figury1.begin(); itr3 != figury1.end(); itr3++) 
				{
					cFigura* tmp2 = *itr3;
					if (tmp2 == 0) continue;
					double yf = tmp2->get_y();
					cSciana* s = dynamic_cast<cSciana*>(tmp2);
					if (s) {
						
						if (yf<lowest_y && (*(itr3-1))==0) {
							lowest_y = yf+0.625;
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
				break;
			}
		}
	}
}

cScena::~cScena() {
 
}