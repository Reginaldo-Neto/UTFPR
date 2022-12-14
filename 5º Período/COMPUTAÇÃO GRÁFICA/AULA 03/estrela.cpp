#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

int init();
void display();

GLint pontas = 6;
GLfloat vetx, vety, x, y, angle, metade, ty;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 0); // posição da janela
	glutInitWindowSize(400, 300);	// largura e altura da janela
	glutCreateWindow("ESTRELA");	// cria a janela

	init();					  // executa função de inicialização
	glutDisplayFunc(display); // função "display" como a função de
							  // callback de exibição

	glutMainLoop(); // mostre tudo e espere
	return 0;
}
int init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // define a cor de fundo

	glMatrixMode(GL_PROJECTION); // carrega a matriz de projeção
	gluOrtho2D(0, 400, 0, 300);	 // define projeção ortogonal 2D que
								 // mapeia objetos da coordenada do
	// mundo para coordenadas da tela
	angle = 360 / pontas;
	metade = angle / 2;
	ty = 0;
	return 0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();
	glPointSize(10);
	glBegin(GL_POINTS);
	// PONTAS
	int i = 0;
	float degInRad;
	do
	{
		degInRad = i * 180.0f / 3.14159f;
		glVertex2f(cos(degInRad) * 50.0f + 200, sin(degInRad) * 50.0f + 150);
		degInRad = metade * 180.0f / 3.14159f;
		//glVertex2f(cos(degInRad) * 25.0f + 200, sin(degInRad) * 25.0f + 150);
		i += angle;
		metade += angle;
	} while (i <= 360);
	glEnd();
	glPopMatrix();
	glutPostRedisplay();
	glutSwapBuffers();
}
