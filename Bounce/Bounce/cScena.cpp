#include "cScena.h"
#include <chrono>

cScena::cScena() {
	kula = new cKula(0, -1.25, 0.5, 3);
	kula_y = kula->get_y();
	figury.push_back(new cSciana(0, -2.5, 7, 2));
	figury.push_back(new cSciana(0, 2.5, 7, 2));
	figury.push_back(new cSciana(-3.2, 0, 2, 5));
	figury.push_back(new cSciana(3.2, 0, 2, 5));
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
    //int current_time = getTickCount();
    //auto current_time = std::chrono::high_resolution_clock::now();
    //std::cout<<current_time<<std::endl;
    //std::cout.flush();
	for (std::vector<cFigura*>::iterator itr = figury.begin(); itr != figury.end(); itr++)
	{
		if (kula->kolizja(*(*itr))) {
			kula->ustaw_predkosc(0, 0);
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
		for (std::vector<cFigura*>::iterator itr = figury.begin(); itr != figury.end(); itr++)
		{
			(*itr)->rysuj();
		}
		kula -> rysuj();
    }
    glPopMatrix();

    glutSwapBuffers();
}


void cScena::set_callbacks() {
    glutReshapeFunc(resize_binding);
    glutDisplayFunc(display_binding);
    //glutIdleFunc(idle_binding);
    glutTimerFunc(40, timer_binding, 0);
    glutKeyboardFunc(key_binding);
}

void cScena::init(int argc, char **argv, const char *window_name) {

    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(40, 40);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutCreateWindow(window_name);

    // set white as the clear colour
    glClearColor(1, 1, 1, 1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    set_callbacks();

    // start GLUT event loop. It ends when user close the window.
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
		kula->ruch(0, 0);
		break;
	}
}

cScena::~cScena() {
 
}