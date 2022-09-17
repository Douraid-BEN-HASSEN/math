#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glut.h" // à la racine du projet
#include <GL/gl.h>
#include <GL/glu.h>
#include <Windows.h>

//#define WIDTH  500
//#define HEIGHT 500
//
//int main(int argc, char** argv)
//{
//    // initialisation  des param�tres de GLUT en fonction
//    // des arguments sur la ligne de commande
//    glutInit(&argc, argv);
//    // initialisation du contexte grapique
//    glutInitDisplayMode(GLUT_RGBA);
//
//    // d�finition et cr�ation de la fen�tre graphique
//    glutInitWindowSize(WIDTH, HEIGHT);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("TP1 BEN HASSEN");
//
//    
//    // la boucle prinicipale de gestion des �v�nements utilisateur
//    glutMainLoop();
//
//    return 1;
//}

#define KEY_R 114
#define KEY_V 118
#define KEY_B 98
#define KEY_ESC 27
#define KEY_E 101
#define KEY_A 65
#define KEY_a 97
#define KEY_S 83
#define KEY_s 115
#define KEY_o 111
#define PI 3.14159265359
#define KEY_c 99
#define KEY_Z 90
#define KEY_z 122
#define KEY_SPACE 32

int color = 0; // 0:noir 1:rouge 2:vert 3:bleu 4:blanc
float colorS[4][3] = { {1.0,1.0,1.0}, {1.0,0.0,0.0},{0.0,1.0,0.0}, {0.0,0.0,1.0} }; // tableau de couleur pour les rotations
float angle = 0;

void mon_window_display(); // prototype fonction callback d'affichage
void mon_window_key(unsigned char key, int x, int y);

GLvoid mon_window_reshape(GLsizei width, GLsizei height); // prototype fonction de redimensionnement
void mon_mouse(int button, int state, int x, int y);
static void idle(void);
float scaler = 1.0;

void resetInfo();

float windowWidth = 20.0;
float windowHeight = 20.0;
float colorSBoulet[4][3] = { {1.0,1.0,1.0}, {1.0,0.0,0.0},{0.0,1.0,0.0}, {0.0,0.0,1.0} }; // tableau de couleur pour les rotations
float bouletPosCoef[3] = { 0, 0, 0 };
float imerirPosCoef[2] = { -10, 0 };
float scaleVal = 1.0;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	mon_window_display();
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP5 BEN HASSEN");
	glutDisplayFunc(&mon_window_display);
	glutReshapeFunc(&mon_window_reshape);
	glutKeyboardFunc(&mon_window_key);
	glutMouseFunc(&mon_mouse);

	glutMainLoop();
	return 1;
}

void mon_window_display()
{
	glClear(GL_COLOR_BUFFER_BIT); // définit la couleur du fond
	glLoadIdentity();
	//glLoadIdentity();
	//glRotatef(45.f, 0.f, 0.f, 1.f);	 
	//glLoadIdentity();
	//glTranslatef(-5, 5, 0.f);
	//glLoadIdentity();
	//glScalef(0.5, 2.f, 0.f);

	if (GetAsyncKeyState(VK_RIGHT)) imerirPosCoef[0] += 0.25;
	if (GetAsyncKeyState(VK_LEFT)) imerirPosCoef[0] -= 0.25;
	if (GetAsyncKeyState(VK_UP)) imerirPosCoef[1] += 0.25;
	if (GetAsyncKeyState(VK_DOWN)) imerirPosCoef[1] -= 0.25;

	glScalef(scaleVal, scaleVal, 0.f);
	
	// boulet
	glRotatef(bouletPosCoef[2], 0.f, 0.f, 1.f);
	glBegin(GL_LINE_LOOP);
	 
	glColor3f(colorSBoulet[0][0], colorSBoulet[0][1], colorSBoulet[0][2]);
	glVertex2f(bouletPosCoef[0] + 0.5 + (windowWidth-(windowWidth/4.0)), bouletPosCoef[1] + 0.5);
	glColor3f(colorSBoulet[1][0], colorSBoulet[1][1], colorSBoulet[1][2]);
	glVertex2f(bouletPosCoef[0] + 1 + (windowWidth - (windowWidth / 4.0)), bouletPosCoef[1] + 0.5);
	glColor3f(colorSBoulet[2][0], colorSBoulet[2][1], colorSBoulet[2][2]);
	glVertex2f(bouletPosCoef[0] + 1 + (windowWidth - (windowWidth / 4.0)), bouletPosCoef[1] + 1);
	glColor3f(colorSBoulet[3][0], colorSBoulet[3][1], colorSBoulet[3][2]);
	glVertex2f(bouletPosCoef[0] + 0.5 + (windowWidth - (windowWidth / 4.0)), bouletPosCoef[1] + 1);
	
	float tempColor[3];
	tempColor[0] = colorSBoulet[0][0];
	tempColor[1] = colorSBoulet[0][1];
	tempColor[2] = colorSBoulet[0][2];

	for (int it = 0; it < 4; it++)
	{
		if (it == 3) {
			colorSBoulet[it][0] = tempColor[0];
			colorSBoulet[it][1] = tempColor[1];
			colorSBoulet[it][2] = tempColor[2];
		}
		else {
			colorSBoulet[it][0] = colorSBoulet[it + 1][0];
			colorSBoulet[it][1] = colorSBoulet[it + 1][1];
			colorSBoulet[it][2] = colorSBoulet[it + 1][2];
		}
	}
	if (bouletPosCoef[2] < 1.0) bouletPosCoef[2] += 0.10;
	else bouletPosCoef[2] = 0;

	if (bouletPosCoef[0] + 0.5 + (windowWidth - (windowWidth / 4.0)) > -windowWidth) bouletPosCoef[0] -= 0.1;
	else {
		bouletPosCoef[1] = imerirPosCoef[1];
		bouletPosCoef[0] = 0;
	}
	glEnd();
	
	glLoadIdentity();
	glScalef(scaleVal, scaleVal, 0.f);

	// IMERIR
	glColor3f(colorS[0][0], colorS[0][1], colorS[0][2]);
	{
		// A
		/*glScalef(scaler, scaler, 0.f);
		glRotatef(angle, 0.f, 0.f, 1.f);*/
		glTranslatef(imerirPosCoef[0], imerirPosCoef[1], 0.f);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-6, -1);
		glVertex2f(-5.5, -1);
		glVertex2f(-5.5, 1);
		glVertex2f(-6, 1);
		glEnd();
		// B
		glBegin(GL_LINE_LOOP);
		glVertex2f(-5, -1);
		glVertex2f(-4.5, -1);
		glVertex2f(-4.5, 0);
		glVertex2f(-4, -0.25);
		glVertex2f(-3.5, 0);
		glVertex2f(-3.5, -1);
		glVertex2f(-3, -1);
		glVertex2f(-3, 1);
		glVertex2f(-4, 0.25);
		glVertex2f(-5, 1);
		glEnd();
		// C
		glBegin(GL_LINE_LOOP);
		glVertex2f(-2.5, -1);
		glVertex2f(-1.5, -1);
		glVertex2f(-1.5, -3.0 / 5);
		glVertex2f(-2, -3.0 / 5);
		glVertex2f(-2, -1.0 / 5);
		glVertex2f(-1.5, -1.0 / 5);
		glVertex2f(-1.5, 1.0 / 5);
		glVertex2f(-2, 1.0 / 5);
		glVertex2f(-2, 3.0 / 5);
		glVertex2f(-1.5, 3.0 / 5);
		glVertex2f(-1.5, 1);
		glVertex2f(-2.5, 1);
		glEnd();
		// D
		glBegin(GL_LINE_LOOP);
		glVertex2f(-1, -1);
		glVertex2f(-0.5, -1);
		glVertex2f(-0.5, 0);
		glVertex2f(0.0, -1);
		glVertex2f(0.5, -1);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.5, 0);
		glVertex2f(0.5, 1);
		glVertex2f(-1.0, 1);
		glEnd();
		// E
		glBegin(GL_LINE_LOOP);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0, 0.5);
		glVertex2f(0, 0.75);
		glVertex2f(-0.5, 0.75);
		glEnd();
		// F
		glBegin(GL_LINE_LOOP);
		glVertex2f(1, -1);
		glVertex2f(1.5, -1);
		glVertex2f(1.5, 1);
		glVertex2f(1, 1);
		glEnd();
		// G
		glBegin(GL_LINE_LOOP);
		glVertex2f(2, -1);
		glVertex2f(2.5, -1);
		glVertex2f(2.5, 0);
		glVertex2f(3.0, -1);
		glVertex2f(3.5, -1);
		glVertex2f(3.0, 0.0);
		glVertex2f(3.5, 0);
		glVertex2f(3.5, 1);
		glVertex2f(2.0, 1);
		glEnd();
		// H
		glBegin(GL_LINE_LOOP);
		glVertex2f(2.5, 0.5);
		glVertex2f(3, 0.5);
		glVertex2f(3, 0.75);
		glVertex2f(2.5, 0.75);
		glEnd();

		glFlush(); // trace la scène graphique qui vient juste d'être définie

		scaler += 0.1;
		angle += 0.1;
	}

	glFlush(); // trace la scène graphique qui vient juste d'être défixnie
 
	/*imerirPosCoef[0] -= 0.1;*/

}

void mon_window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_R:
	{
		resetInfo();
		glutIdleFunc(idle);
		printf("r : Lancer l'animation \n");
		break;
	}
	case KEY_S: case KEY_s:
	{
		resetInfo();
		glutIdleFunc(NULL);
		printf("r : Arrêter l'animation \n");
		break;
	}
	case KEY_c:
	{
		float tempColor[3];
		tempColor[0] = colorS[0][0];
		tempColor[1] = colorS[0][1];
		tempColor[2] = colorS[0][2];

		for (int it = 0; it < 4; it++)
		{
			if (it == 3) {
				colorS[it][0] = tempColor[0];
				colorS[it][1] = tempColor[1];
				colorS[it][2] = tempColor[2];
			}
			else {
				colorS[it][0] = colorS[it + 1][0];
				colorS[it][1] = colorS[it + 1][1];
				colorS[it][2] = colorS[it + 1][2];
			}
		}

		printf("c : Changer la couleur \n");
		break;
	}
	case KEY_Z:
	{
		scaleVal += 0.1;
		printf("Z : Zoom avant \n");
		break;
	}
	case KEY_z:
	{
		scaleVal -= 0.1;
		printf("Z : Zoom arrière \n");
		break;
	}
	case 120:
		resetInfo();
		glutIdleFunc(NULL);
		printf("r : Collision \n");
		break;
	case KEY_ESC:
		exit(1);
		break;
	default:
		printf("La touche %d n�est pas active.\n", key);
		break;
	}
}

void resetInfo()
{
	scaleVal = 1;
	bouletPosCoef[0] = 0;
	bouletPosCoef[1] = 0;
	bouletPosCoef[2] = 0;
	imerirPosCoef[0] = -10;
	imerirPosCoef[1] = 0;
	colorS[0][0] = 1.0;
	colorS[0][1] = 1.0;
	colorS[0][2] = 1.0;

	colorS[1][0] = 1.0;
	colorS[1][1] = 0.0;
	colorS[1][2] = 0.0;

	colorS[2][0] = 0.0;
	colorS[2][1] = 1.0;
	colorS[2][2] = 0.0;

	colorS[3][0] = 0.0;
	colorS[3][1] = 0.0;
	colorS[3][2] = 1.0;

	mon_window_display();
}

GLvoid mon_window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);// valeurs de largeur et de hauteur de la fenêtre après redimensionnement
	glMatrixMode(GL_PROJECTION); // chargement de la matrice de projection
	glLoadIdentity(); // Initialisation de la matrice courante à l'identité
	gluOrtho2D(-20.0, 20.0, -20.0, 20.0);// spécification du type et des arguments de la projection
	glMatrixMode(GL_MODELVIEW);// retour dans l'espace de modélisation (modèle de vue)
	glLoadIdentity();
}

void mon_mouse(int button, int state, int x, int y) {
	if (state == 0) {
		switch (color)
		{
		case 0:
			if (button == 0) {
				color = 1;
				glClearColor(1, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			else {
				color = 4;
				glClearColor(1, 1, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			break;
		case 1:
			if (button == 0) {
				color = 2;
				glClearColor(0, 1, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			else {
				color = 0;
				glClearColor(0, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			break;
		case 2:
			if (button == 0) {
				color = 3;
				glClearColor(0, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			else {
				color = 1;
				glClearColor(1, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			break;
		case 3:
			if (button == 0) {
				color = 4;
				glClearColor(1, 1, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			else {
				color = 2;
				glClearColor(0, 1, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			break;
		case 4:
			if (button == 0) {
				color = 0;
				glClearColor(0, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			else {
				color = 3;
				glClearColor(0, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				glutPostRedisplay();
			}
			break;
		default:
			printf("not found \n");
			break;
		}
	}
}

static void idle(void)
{	
	Sleep(10);	
	mon_window_display();
}
