//#include <windows.h>
#include <iostream>
#include <math.h>
#include<GL/glut.h>

class wcPt2D{
    public: GLfloat x, y;
};

void translatePolygon(wcPt2D* verts, GLint nVerts, GLfloat tx, GLfloat ty){
    for(int a=0; a<nVerts; a++){
        verts[a].x+= tx;
        verts[a].y+= ty;
    }
};

void rotatePolygon(wcPt2D* verts, GLint nVerts, GLdouble angulo){
    double cosseno, seno;
    angulo = angulo*(M_PI/180);
    cosseno=cos(angulo);
    seno=sin(angulo);

    for(int a=0; a<nVerts; a++){
        verts[a].x = (verts[a].x*cosseno) - (verts[a].y*seno);
        verts[a].y = (verts[a].x*seno) - (verts[a].y*cosseno);
    }
};

void rotatePolygonFixo(wcPt2D* verts, GLint nVerts, GLdouble angulo, wcPt2D pivo){
    wcPt2D * novo = new wcPt2D;
    double cosseno, seno;
    angulo = angulo*(M_PI/180);
    cosseno=cos(angulo);
    seno=sin(angulo);

    for(int k=0; k<nVerts; k++){

        novo[k].x = pivo.x + (verts[k].x - pivo.x) * cosseno - (verts[k].y - pivo.y) * seno;
        std::cout<<(novo[k].x);
        novo[k].y = pivo.y + (verts[k].x - pivo.x) * seno    + (verts[k].y - pivo.y) * cosseno;
        std::cout<<"\n";
        std::cout<<(novo[k].y);
        std::cout<<"\n";
        std::cout<<"\n";
    }
    glBegin(GL_TRIANGLES); //desenha um triangulos
        
        glVertex2i(novo[0].x, novo[0].y);
        
        glVertex2i(novo[1].x, novo[1].y);
        
        glVertex2i(novo[2].x, novo[2].y);
    glEnd();
};

void diminuiEscala(wcPt2D* verts, GLint nVerts, wcPt2D escala){
    wcPt2D * novo = new wcPt2D;
    for(int k=0; k<nVerts; k++){
        novo[k].x = verts[k].x*escala.x;
        novo[k].y = verts[k].y*escala.y;
    }
    glBegin(GL_TRIANGLES); //desenha um triangulos
        
        glVertex2i(novo[0].x, novo[0].y);
        
        glVertex2i(novo[1].x, novo[1].y);
        
        glVertex2i(novo[2].x, novo[2].y);
    glEnd();
};

void diminuiEscalaFixo(wcPt2D* verts, GLint nVerts, wcPt2D escala, wcPt2D centro){
    wcPt2D * novo = new wcPt2D;
    for(int k=0; k<nVerts; k++){
        novo[k].x = verts[k].x*escala.x + centro.x*(1-escala.x);
        novo[k].y = verts[k].y*escala.y + centro.y*(1-escala.y);
    }
    glBegin(GL_TRIANGLES); //desenha um triangulos
        
        glVertex2i(novo[0].x, novo[0].y);
        
        glVertex2i(novo[1].x, novo[1].y);
        
        glVertex2i(novo[2].x, novo[2].y);
    glEnd();
};

//Inicializa parâmetros de rendering
int init(void){
    //define cor de fundo
    // R G B | ALPHA = TRANSPARENCIA(0 OPACO/ 1 TRANSPARENTE)
    glClearColor(0, 0, 0, 0.0);
    //carrega matriz de projeção
    glMatrixMode(GL_PROJECTION);
    //define projeção ortogonal 2D
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);    
    //          Xi,   Xf,   Yi,   Yf
    return 0;
} 

//função callback chamada para fazer o desenho 
//de tempos em tempos (serve pra mostar movimentos/animações)
void display(void){
    //desenha o fundo (limpa a janela)
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3ub(255, 255, 255);
 
    wcPt2D vertices[3];

    vertices[0].x=250;
    vertices[0].y=220;
    vertices[1].x=350;
    vertices[1].y=220;
    vertices[2].x=300;
    vertices[2].y=330;

    glBegin(GL_TRIANGLES); //desenha um triangulos
        glColor3ub(255,0,0);
        glVertex2i(vertices[0].x, vertices[0].y);
        glColor3ub(0,255,0);
        glVertex2i(vertices[1].x, vertices[1].y);
        glColor3ub(0,0,255);
        glVertex2i(vertices[2].x, vertices[2].y);
    glEnd();

    //translatePolygon(vertices, 3, 40,40);
    //rotatePolygon(vertices, 3, 30);
    /*glColor3ub(255,0,0);
    rotatePolygonFixo(vertices, 3, 90, vertices[2]);
    glColor3ub(0,255,0);
    rotatePolygonFixo(vertices, 3, 180, vertices[2]);
    glColor3ub(0,0,255);
    rotatePolygonFixo(vertices, 3, 270, vertices[2]);*/

    wcPt2D escala, fixo;
    escala.x=0.5;
    escala.y=0.5;
    diminuiEscala(vertices, 3, escala);
    fixo.x = 250;
    fixo.y=220;
    diminuiEscalaFixo(vertices, 3, escala, fixo);
    

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


    //glColor3f(1.0, 0.0, 0.0); //altera o atributo de cor, se eu qusier de 0-255 usar glColor3ub
   

    //glBegin(GL_LINES); //desenha uma linha
    //glBegin(GL_POINTS); 
    //glBegin(GL_LOLYGON); 
    //glBegin(GL_LINES); 

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