#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


void desenhaCubo(void){

}

void teclasEspeciais(int tecla, int x, int y) {

}

void teclas(unsigned char tecla, int x, int y) {

}

void gerenciaMouse(int button, int state, int x, int y) {

}

void gerenciaMovim(int x, int y) {

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    desenhaCubo();
    glutSwapBuffers();

}

void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0);     //define a cor de fundo
    glMatrixMode(GL_PROJECTION);          //define que a matriz é a de projeção
    glLoadIdentity();
    glOrtho(-100,100,-100, 100,-100,100);
}



int main(int argc, char** argv){
    glutInit(&argc,argv);                           //inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    //configura o modo de display
    glutInitWindowPosition(200,0);                  //seta a posição inicial da janela
    glutInitWindowSize(500,500);                    //configura a largura e altura da janela de exibição
    glutCreateWindow("Cubo Colorido");                 //cria a janela de exibição
    init();                                         //executa função de inicialização
    glutDisplayFunc(display);
    glutSpecialFunc(teclasEspeciais);
    glutKeyboardFunc(teclas);
    glutMouseFunc(gerenciaMouse);
    glutMotionFunc(gerenciaMovim);
    glutMainLoop();                                  //mostre tudo e espere
    return 0;
}
