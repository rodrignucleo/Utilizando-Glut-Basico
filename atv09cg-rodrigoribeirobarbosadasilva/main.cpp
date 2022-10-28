#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

GLfloat escala=1;
GLfloat rotacao=0;
GLfloat r = 0, g = 0, b = 0;              // vari�veis para controle de cor (inicia em preto)
GLfloat movex = 0, movey = 0;      // vari�veis de movimenta��o para x e y

int submenucor;
int opcao = 0;
int contador=0;
float win;                          // win (window), vai definir o tamanho de cada viewport (quanto maior valor de win, mais longe da tela)
float aspecto;                      // aspecto: vari�vel para controlar windowsize
int largura, altura;                //largura e altura da minha janela
int rotacaoCod=0;

void timerPonto(int passo){                //fun��o timerPonto, que verifica o local do ponto para saber quando deve parar de subir (ou descer) o ponto no eixo y
    switch(rotacaoCod){
        case 1:
                rotacao+=1;
                glutPostRedisplay();                 //chama a fun��o desenha toda vez que for necess�ria
                glutTimerFunc(50,timerPonto,1);
                break;
        case 0:
                printf("\nParou!!");
                break;
    }
}

void quadrado(){
    glBegin(GL_QUADS);                      //lBegin e glEnd delimitam os v�rtices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como par�metro).
        glVertex2f(-5, -5);                 //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
        glVertex2f(-5, 5);                  //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
        glVertex2f(5, 5);                   //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
        glVertex2f(5, -5);                  //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
    glEnd();
}

void triangulo(){
    glBegin(GL_TRIANGLES);                   //lBegin e glEnd delimitam os v�rtices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como par�metro).
        glColor3f(0,0,1);                    //adiciona cor ao nosso quadrado
        glVertex2f(-6, -5);                  //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso triangulo
        glVertex2f(0, 5);                    //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso triangulo
        glVertex2f(6, -5);                   //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso triangulo
    glEnd();
}

void ponto(){
    glBegin(GL_QUADS);                      //lBegin e glEnd delimitam os v�rtices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como par�metro).
        glColor3f(0.5,0.5,0.5);
        glVertex2f(-4, -4);                 //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
        glVertex2f(-4, 4);                  //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
        glVertex2f(4, 4);                   //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
        glVertex2f(4, -4);                  //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso quadrado
    glEnd();
}

void linha(){
    glBegin(GL_QUADS);                   //lBegin e glEnd delimitam os v�rtices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como par�metro).
        glColor3f(0,0,0);                    //adiciona cor ao nosso quadrado
        glVertex2f(-30, 1);                  //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso triangulo
        glVertex2f(30, 1);                    //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso triangulo
        glVertex2f(30, -1);
        glVertex2f(-30, -1);
        //glVertex2f(6, -5);                   //adiciona um ponto na coordenada x, y que ser� usado para fazer nosso triangulo
    glEnd();
}

void contorno(){                            //desenha linhas para ter melhor visualiza��o das viewports
    glLineWidth(3);                         //adiciona espessura da linha
    glBegin(GL_LINE_LOOP);                  //lBegin e glEnd delimitam os v�rtices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como par�metro).
        glColor3f(1,0,0);                   //adiciona cor na linha
        glVertex2f(-win*aspecto, -win);     //inferior esquerdo
        glVertex2f(-win*aspecto, win);      //superior esquerdo
        glVertex2f(win*aspecto, win);       //superior direito
        glVertex2f(win*aspecto, -win);      //inferior direito
    glEnd();
}

void desenhaObjetos(void){
    glClear(GL_COLOR_BUFFER_BIT);                         //buffer padr�o (limpa a tela toda vez que a fun��o � chamada)

    glViewport(0, altura, largura, altura);              //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    glColor3f(r, g, b);
    glPushMatrix();                                       //insere a matriz de transforma��o corrente na pilha
		quadrado();                                      //chama a fun��o triangulo
		//printf("%d, %d", largura, altura*2);
		contorno();                                       //chama a fun��o contorno
    glPopMatrix();                                       //retira a matriz do topo da pilha e torna esta �ltima a matriz de transforma��o corrente

    glViewport(largura, altura, largura, altura);              //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    glPushMatrix();                                       //insere a matriz de transforma��o corrente na pilha
		contorno();                                        //chama a fun��o contorno
		glScalef(escala, escala, 0);
		triangulo();                                      //chama a fun��o triangulo
		//printf("%d, %d", largura, altura*2);
    glPopMatrix();

	glViewport(0, 0, largura, altura);                    //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
	glPushMatrix();                                       //insere a matriz de transforma��o corrente na pilha
        contorno();                                       //chama a fun��o contorno
        glTranslatef(movex, movey,0);
        ponto();                                       //chama a fun��o quadrado
	 glPopMatrix();                                       //retira a matriz do topo da pilha e torna esta �ltima a matriz de transforma��o corrente

	glViewport(largura, 0, largura, altura);              //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    glPushMatrix();                                       //insere a matriz de transforma��o corrente na pilha
		contorno();                                       //chama a fun��o contorno
        glRotatef(rotacao, 0,0,1);
		linha();                                      //chama a fun��o triangulo
    glPopMatrix();                                       //retira a matriz do topo da pilha e torna esta �ltima a matriz de transforma��o corrente

	glutSwapBuffers();                                    //Executa uma troca de buffer na camada em uso para a janela atual (para que consiga trabalhar com dois buffers)
}

void teclas(unsigned char tecla, GLint x, GLint y){
    switch(tecla){
        case '+': escala++;         // adiciona 1 ao valor de escala
        break;
        case '-': escala--;         // remove 1 ao valor de escala
        break;
       /* case '1': rotacao-=10;      // rotaciona o objeto no sentido hor�rio (diminui o �ngulo em 10)
        break;
        case '2': rotacao+=10;      // rotaciona o objeto no sentido anti-hor�rio (aumenta o �ngulo em 10)
       */ break;
    }
    glutPostRedisplay();            //redesenha a cena que est� na janela
}

void escolheCor(int opcao){                //verifica a op��o escolhida
    switch(opcao){
        case 0:                           //caso  o valor de op��o for 0 pinta de vermelho
            r = 1;                        //atribui valores as vari�veis de cor
            g = 0.4;                        //atribui valores as vari�veis de cor
            b = 0.7;                        //atribui valores as vari�veis de cor
        break;
        case 1:                           //caso  o valor de op��o for 1 pinta de verde
            r = 0.3;                        //atribui valores as vari�veis de cor
            g = 1;                        //atribui valores as vari�veis de cor
            b = 0.7;                        //atribui valores as vari�veis de cor
        break;
        case 2:                           //caso  o valor de op��o for 2 pinta de azul
            r = 0.3;                        //atribui valores as vari�veis de cor
            g = 0.2;                        //atribui valores as vari�veis de cor
            b = 1;                        //atribui valores as vari�veis de cor
        break;
        case 3:                           //caso  o valor de op��o for 2 pinta de azul
            r = 0.3;                        //atribui valores as vari�veis de cor
            g = 0.6;                        //atribui valores as vari�veis de cor
            b = 0.3;                        //atribui valores as vari�veis de cor
        break;
    }
    glutPostRedisplay();                  //chama a fun��o desenha toda vez que for necess�ria
}

void gerenciaMouse(int botao, int estado, int x, int y){      //Par�metros de entrada da fun��o: (int button, int state, int x, int y).  Os par�metros x e y indicam a localiza��o do mouse no momento que o evento ocorreu.
    if(botao == GLUT_RIGHT_BUTTON)  {                           //se o bot�o do mouse clicado for o esquerdo
        if(estado == GLUT_DOWN){                              //O par�metro state pode ser GLUT_UP ou GLUT_DOWN.
            if(opcao>3) {
                    opcao = 0;
            }
            escolheCor(opcao);
            printf("%d", opcao);
            opcao = opcao + 1;
        }}
    else if(botao == GLUT_LEFT_BUTTON){
            if(estado == GLUT_DOWN){                              //O par�metro state pode ser GLUT_UP ou GLUT_DOWN.
                switch(rotacaoCod){
                    case 0: rotacaoCod = 1;
                            glutTimerFunc(10,timerPonto,1);
                            printf("\nRodando!!");break;
                    case 1: rotacaoCod=0; break;}
            }}
    glutPostRedisplay();                                      //chama a fun��o desenha toda vez que for necess�ria
}

void alteraTamanhoJanela(GLsizei w, GLsizei h){           //faz o controle do tamanho das viewports (padr�o de par�metros, altura e largura) (800x600 no glutInitWindowSize)
    if(h == 0) h = 1;                                     //caso altura seja = 0, setamos ela pra 1, pra corrigir eventuais erros
    largura = w/2;                                        //largura eu divido o valor da janela por 2, para criar duas viewports do mesmo tamanho, no caso 800/2
    altura = h/2;                                           //altura eu mantenho a mesma, pois vou dividir s� em duas partes.

    aspecto = (float) largura / altura;                   // largura dividida pela altura (utilizada para controlar a largura da janela automaticamente, independente de eu alterar a windowsize) (faz com que as janelas tenham a mesma propor��o em cada viewport)

    glMatrixMode(GL_PROJECTION);                          //proje��o do tipo modelo
    glLoadIdentity();                                     //carrega a identidade de proje��o de modelo
    gluOrtho2D(-win*aspecto, win*aspecto, -win, win);     //sistema de coordenadas, agora definido de acordo com os par�metros de janela, win e aspecto) direta x, esqueda -x, abaixo -y e acima y (cada viewport ter� seu sistema de coordenadas)
}

void setasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){
        case GLUT_KEY_LEFT: movex--;               // move nosso objeto para a esquerda
        break;
        case GLUT_KEY_RIGHT: movex++;              // move nosso objeto para a direita
        break;
        case GLUT_KEY_UP: movey++;                 // move nosso objeto para cima
        break;
        case GLUT_KEY_DOWN: movey--;               // move nosso objeto para baixo
        break;
    }
    glutPostRedisplay();
}

void inicializa(){                                        // inicializa nossas vari�veis
     glClearColor(1,1,1,0);                               //informa a cor de fundo da tela (branco)
     win = 50;                                            // quanto menor o valor de win, mais perto da tela (como se fosse um zoom)
}

int main(void){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);          //somente um double buffer | sistema de cores RGB
    glutInitWindowSize(800,600);                          //define o tamanho da janela
    glutInitWindowPosition(320,150);                      //medidas usadas para posicionar a janela no meio da tela - isso depende da resolu��o do monitor
	glutCreateWindow("Atividade 9 - ViewPort");                 //permite a cria��o de uma janela
    glutDisplayFunc(desenhaObjetos);                      //fun��o de callback - chama a fun��o desenhaObjetos
    glutReshapeFunc(alteraTamanhoJanela);                 //fun��o que altera o tamanho da janela, redesenha o tamanho da janela
    glutKeyboardFunc(teclas);
    glutSpecialFunc(setasDirecionais);
    glutMouseFunc(gerenciaMouse);
    inicializa();
    glutMainLoop();                                       //loop infinito - escuta as informa��es do sistema at� encerrar a aplica��o
    return 0;                                             //retorna zero
}
