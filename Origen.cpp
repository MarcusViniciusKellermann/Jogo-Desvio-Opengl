#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <iostream>




float esferaX = 0, esferaY = 1.8, plataformaX = 0, plataformaY = -1.5, trianguloX = 0, trianguloY = -1.2;
int rand(), r, queda = 0, count = 0;
float VelocidadeDaEsfera = 0;





void init()// Inicializaçao
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

void esfera()
{
    glColor3f(1, 0, 0);
    glutSolidSphere(0.2, 25, 25);
}

void triangulo()
{
    glColor3f(0, 1, 0);
    glutSolidCone(0.3, 0.5, 25, 25);
}

void plataforma()
{
    glColor3f(0, 0, 1);
    glutSolidCube(1.5);

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();




    if (count == 3)// se o circulo cai mais de 3 vezes aumenta a velocidade da queda da esfera
    {
        VelocidadeDaEsfera += 0.008;
        count = 0;
    }


    if (esferaY < -1.5 && (esferaX > trianguloX - 1.0 && esferaX < trianguloX + 1.0))// coordenada feita se a esfera(circulo) cair em cima do triangulo, acaba o jogo 
    {
        esferaY = 1.8;// posçao inicial de queda do circulo
        r = rand() % 4;
        if (r == 1)// se acertou pelo menos uma vez o triangulo acaba o jogo
        {
            queda = -1;// igual a -1 para finalizar o jogo

        }

    }
    else if (esferaY < -1.5 && (esferaX > plataformaX - 1.9 && esferaX < plataformaX + 5.5))// plataforma e feita como um sensor se a esfera o atingir ira cair outras esferas ate o fim do jogo
    {
        count++; // contador
        esferaY = 1.8; // posicao inicial
        r = rand() % 4;
        if (r == 0)
        {
            esferaX = -1.8;

        }
        if (r == 1)// atingiu uma vez
        {
            esferaX = -1;// caira em -1

        }
        if (r == 2)// atingiu duas vezes
        {
            esferaX = 1;// caira em 1

        }
        if (r == 3)// atingiu tres vezes
        {
            esferaX = 1.8; // caira em 1.8

        }
    }





    if (queda == 0)// metodo de queda da esfera
        esferaY -= 0.01 + VelocidadeDaEsfera;// velocidade inicial de queda da esfera

    if (esferaY < -2)
    {
        queda = 1;
    }

    glPushMatrix();
    glTranslatef(esferaX, esferaY, 0);
    esfera();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(trianguloX, trianguloY, 0);
    glRotatef(90, -2.5, 0, 0);
    glScalef(2.0, 0.4, 1.0);
    triangulo();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(plataformaX, plataformaY, 0);
    glRotatef(90, -0.9, 0, 0);
    glScalef(4.5, 1, 0.5);
    plataforma();
    glPopMatrix();


    glutSwapBuffers();
    glutPostRedisplay();

}








void teclado(int key, int x, int y)// teclado seta esquerda e seta direita(unicas teclas que movem)
{
    if (key == GLUT_KEY_LEFT)
        trianguloX -= 0.3;
    if (key == GLUT_KEY_RIGHT)
        trianguloX += 0.3;
}





int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Game");
    init();

    glutDisplayFunc(display);
    glutSpecialFunc(teclado);
    
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
