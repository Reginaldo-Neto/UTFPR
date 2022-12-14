#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

int init();
void display();
void movimentaQuadrado();
void desenhaForma();

GLfloat r, g, b, forma, tx, ty = 0, flag = 0;
bool increasing;
GLint x, y, raio, num_linhas;


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200, 0); // posição da janela
    glutInitWindowSize(400, 300);   // largura e altura da janela
    glutCreateWindow("Animação");   // cria a janela

    init();                   // executa função de inicialização
    glutDisplayFunc(display); // função "display" como a função de
                              // callback de exibição

    glutMainLoop(); // mostre tudo e espere
    return 0;
}

int init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // define a cor de fundo

    glMatrixMode(GL_PROJECTION); // carrega a matriz de projeção
    gluOrtho2D(0, 400, 0, 300);  // define projeção ortogonal 2D que
                                 // mapeia objetos da coordenada do
                                 // mundo para coordenadas da tela
    increasing = true;
    tx = 0;
    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    movimentaQuadrado();
    desenhaForma();

    glPopMatrix();
    glutPostRedisplay();
    glutSwapBuffers();
}

void movimentaQuadrado()
{
    if (flag == 0)
    {
        tx += 1;
        ty += 1;
    }
    else if (flag == 1)
    {
        tx += 1;
        ty -= 1;
    }
    else if (flag == 2)
    {
        tx -= 1;
        ty -= 1;
    }
    else if (flag == 3)
    {
        tx -= 1;
        ty += 1;
    }
    glTranslatef(tx, ty, 0);
    r = rand() % 10;
    g = rand() % 10;
    b = rand() % 10;
    r = r / 10;
    g = g / 10;
    b = b / 10;

    if (tx <= 0)
    {
        if (flag == 2)
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        glClearColor(r, g, b, 0.0);
        forma = rand() % 3;
    }
    else if (tx >= 380)
    {
        if (flag == 0)
        {
            flag = 3;
        }
        else
        {
            flag = 2;
        }
        glClearColor(r, g, b, 0.0);
        forma = rand() % 3;
    }
    else if (ty <= 0)
    {
        if (flag == 1)
        {
            flag = 0;
        }
        else
        {
            flag = 3;
        }
        glClearColor(r, g, b, 0.0);
        forma = rand() % 3;
    }
    else if (ty >= 280)
    {
        if (flag == 0)
        {
            flag = 1;
        }
        else
        {
            flag = 2;
        }
        glClearColor(r, g, b, 0.0);
        forma = rand() % 2;
    }
};

void desenhaForma()
{

    if (forma == 0)
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++)
        {
            float degInRad = i * 180.0f / 3.14159f;
            glVertex2f(cos(degInRad) * 10.0f + 10, sin(degInRad) * 10.0f + 10);
        }
        glEnd();
    }
    else if (forma == 1)
    {
        glBegin(GL_QUADS);
        glVertex2f(0, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 0);
        glVertex2f(0, 0);
        glEnd();
    }
    else if (forma == 2)
    {
        glBegin(GL_TRIANGLES);
        glVertex2f(10, 20);
        glVertex2f(0, 0);
        glVertex2f(20, 0);
        glEnd();
    }
};
