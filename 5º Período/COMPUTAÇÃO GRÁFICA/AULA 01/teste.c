//TRIANGULO GRADIENTE

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>

//Inicializa parâmetros de rendering
int init(void){
    //define cor de fundo
    // R G B | ALPHA = TRANSPARENCIA(0 OPACO/ 1 TRANSPARENTE)
    glClearColor(0, 0, 0, 0.0);
    //carrega matriz de projeção
    glMatrixMode(GL_PROJECTION);
    //define projeção ortogonal 2D
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);    
    //          Xi,   Xf,   Yi,   Yf
    return 0;
} 

//função callback chamada para fazer o desenho 
//de tempos em tempos (serve pra mostar movimentos/animações)
void display(void){
    //desenha o fundo (limpa a janela)
    glClear(GL_COLOR_BUFFER_BIT);

    //glColor3f(1.0, 0.0, 0.0); //altera o atributo de cor, se eu qusier de 0-255 usar glColor3ub
    glColor3ub(255, 255, 255);
    //glBegin(GL_LINES); //desenha uma linha
    //glBegin(GL_POINTS); 
    //glBegin(GL_LOLYGON); 
    //glBegin(GL_LINES); 

    glBegin(GL_TRIANGLES); //desenha um triangulos
        glColor3ub(255,0,0);
        glVertex2i(50, 20);
        glColor3ub(0,255,0);
        glVertex2i(150, 20);
        glColor3ub(0,0,255);
        glVertex2i(100, 130);
    glEnd();



    /*
    glBegin(GL_LINES); //desenha uma linha
        glVertex2i(200, 15);
        glVertex2i(10, 140);
    glEnd();
    
    glPointSize(3.0);
    glBegin(GL_POINTS);
        glVertex2i(100, 150);
        glVertex2i(100, 130);
        glVertex2i(150, 130);
    glEnd(); 
    */


    //esvazia o buffer, enviando todos os comandos emitidos
    //ate o momento para a GPU, sem esperar pelo render
    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv); //INICIALIZA O GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //DEFINE O MODO DE DISPLAY
    glutInitWindowPosition(200,0); //POSIÇÃO INICIAL DA JANELA
    glutInitWindowSize(400,300); //LARGURA DA ALTURA DA JANELA
    
    //CRIA JANELA DE EXIBIÇÃO
    glutCreateWindow("Exemplo de programa OpenGL");
    
    //CHAMAM A FUNÇÃO DE INICIALIZAÇÃO
    init();

    //DEFINE A FUNÇÃO display() COMO A FUNÇÃO CALLBACK DE EXIBIÇÃO
    glutDisplayFunc(display); //FUNCAO CALLBACK DE EXIBIÇÃO, (PODERIA SER IMAGEM OU TELA E ETC)
    glutMainLoop(); //MOSTRA TUDO E SE REPETE
}