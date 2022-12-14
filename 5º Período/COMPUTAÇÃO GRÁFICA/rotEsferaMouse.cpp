#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
int X=250, Y=250, Z=1;
int tempx, tempy;

// void desenhaEsfera(void){
    
//     glutWireSphere(5.0f, 50, 50);
//     glColor3f(0, 0, 1);
//     glTranslatef(X, Y, Z);
//     glScalef(4, 0.1f, 4);
// }

void gerenciaMouse(int button, int state, int x, int y) {
     
    if(button==GLUT_LEFT_BUTTON){
        
        if(x!=X || y!=Y){
            // tempx=X-x;
            // tempy=Y-y;
            Y=y;
            X=x;
            
        }
    }

    glutPostRedisplay();
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutWireSphere(5.0f, 50, 50);
    glColor3f(0, 1, 1);
    glTranslated(X, Y, Z);
    std::cout<<X<<" - "<<Y<<std::endl;
    //desenhaEsfera();
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
    glutCreateWindow("Esfera Andante");                 //cria a janela de exibição
    init();                                         //executa função de inicialização
    glutDisplayFunc(display);
    glutMouseFunc(gerenciaMouse);
    glutMainLoop();                                  //mostre tudo e espere
    return 0;
}
