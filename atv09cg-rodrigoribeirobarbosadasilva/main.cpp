#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

GLfloat escala=1;
GLfloat rotacao=0;
GLfloat r = 0, g = 0, b = 0;              // variáveis para controle de cor (inicia em preto)
GLfloat movex = 0, movey = 0;      // variáveis de movimentação para x e y

int submenucor;
int opcao = 0;
int contador=0;
float win;                          // win (window), vai definir o tamanho de cada viewport (quanto maior valor de win, mais longe da tela)
float aspecto;                      // aspecto: variável para controlar windowsize
int largura, altura;                //largura e altura da minha janela
int rotacaoCod=0;

void timerPonto(int passo){                //função timerPonto, que verifica o local do ponto para saber quando deve parar de subir (ou descer) o ponto no eixo y
    switch(rotacaoCod){
        case 1:
                rotacao+=1;
                glutPostRedisplay();                 //chama a função desenha toda vez que for necessária
                glutTimerFunc(50,timerPonto,1);
                break;
        case 0:
                printf("\nParou!!");
                break;
    }
}

void quadrado(){
    glBegin(GL_QUADS);                      //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glVertex2f(-5, -5);                 //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
        glVertex2f(-5, 5);                  //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
        glVertex2f(5, 5);                   //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
        glVertex2f(5, -5);                  //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
    glEnd();
}

void triangulo(){
    glBegin(GL_TRIANGLES);                   //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glColor3f(0,0,1);                    //adiciona cor ao nosso quadrado
        glVertex2f(-6, -5);                  //adiciona um ponto na coordenada x, y que será usado para fazer nosso triangulo
        glVertex2f(0, 5);                    //adiciona um ponto na coordenada x, y que será usado para fazer nosso triangulo
        glVertex2f(6, -5);                   //adiciona um ponto na coordenada x, y que será usado para fazer nosso triangulo
    glEnd();
}

void ponto(){
    glBegin(GL_QUADS);                      //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glColor3f(0.5,0.5,0.5);
        glVertex2f(-4, -4);                 //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
        glVertex2f(-4, 4);                  //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
        glVertex2f(4, 4);                   //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
        glVertex2f(4, -4);                  //adiciona um ponto na coordenada x, y que será usado para fazer nosso quadrado
    glEnd();
}

void linha(){
    glBegin(GL_QUADS);                   //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glColor3f(0,0,0);                    //adiciona cor ao nosso quadrado
        glVertex2f(-30, 1);                  //adiciona um ponto na coordenada x, y que será usado para fazer nosso triangulo
        glVertex2f(30, 1);                    //adiciona um ponto na coordenada x, y que será usado para fazer nosso triangulo
        glVertex2f(30, -1);
        glVertex2f(-30, -1);
        //glVertex2f(6, -5);                   //adiciona um ponto na coordenada x, y que será usado para fazer nosso triangulo
    glEnd();
}

void contorno(){                            //desenha linhas para ter melhor visualização das viewports
    glLineWidth(3);                         //adiciona espessura da linha
    glBegin(GL_LINE_LOOP);                  //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glColor3f(1,0,0);                   //adiciona cor na linha
        glVertex2f(-win*aspecto, -win);     //inferior esquerdo
        glVertex2f(-win*aspecto, win);      //superior esquerdo
        glVertex2f(win*aspecto, win);       //superior direito
        glVertex2f(win*aspecto, -win);      //inferior direito
    glEnd();
}

void desenhaObjetos(void){
    glClear(GL_COLOR_BUFFER_BIT);                         //buffer padrão (limpa a tela toda vez que a função é chamada)

    glViewport(0, altura, largura, altura);              //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    glColor3f(r, g, b);
    glPushMatrix();                                       //insere a matriz de transformação corrente na pilha
		quadrado();                                      //chama a função triangulo
		//printf("%d, %d", largura, altura*2);
		contorno();                                       //chama a função contorno
    glPopMatrix();                                       //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

    glViewport(largura, altura, largura, altura);              //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    glPushMatrix();                                       //insere a matriz de transformação corrente na pilha
		contorno();                                        //chama a função contorno
		glScalef(escala, escala, 0);
		triangulo();                                      //chama a função triangulo
		//printf("%d, %d", largura, altura*2);
    glPopMatrix();

	glViewport(0, 0, largura, altura);                    //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
	glPushMatrix();                                       //insere a matriz de transformação corrente na pilha
        contorno();                                       //chama a função contorno
        glTranslatef(movex, movey,0);
        ponto();                                       //chama a função quadrado
	 glPopMatrix();                                       //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

	glViewport(largura, 0, largura, altura);              //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    glPushMatrix();                                       //insere a matriz de transformação corrente na pilha
		contorno();                                       //chama a função contorno
        glRotatef(rotacao, 0,0,1);
		linha();                                      //chama a função triangulo
    glPopMatrix();                                       //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

	glutSwapBuffers();                                    //Executa uma troca de buffer na camada em uso para a janela atual (para que consiga trabalhar com dois buffers)
}

void teclas(unsigned char tecla, GLint x, GLint y){
    switch(tecla){
        case '+': escala++;         // adiciona 1 ao valor de escala
        break;
        case '-': escala--;         // remove 1 ao valor de escala
        break;
       /* case '1': rotacao-=10;      // rotaciona o objeto no sentido horário (diminui o ângulo em 10)
        break;
        case '2': rotacao+=10;      // rotaciona o objeto no sentido anti-horário (aumenta o ângulo em 10)
       */ break;
    }
    glutPostRedisplay();            //redesenha a cena que está na janela
}

void escolheCor(int opcao){                //verifica a opção escolhida
    switch(opcao){
        case 0:                           //caso  o valor de opção for 0 pinta de vermelho
            r = 1;                        //atribui valores as variáveis de cor
            g = 0.4;                        //atribui valores as variáveis de cor
            b = 0.7;                        //atribui valores as variáveis de cor
        break;
        case 1:                           //caso  o valor de opção for 1 pinta de verde
            r = 0.3;                        //atribui valores as variáveis de cor
            g = 1;                        //atribui valores as variáveis de cor
            b = 0.7;                        //atribui valores as variáveis de cor
        break;
        case 2:                           //caso  o valor de opção for 2 pinta de azul
            r = 0.3;                        //atribui valores as variáveis de cor
            g = 0.2;                        //atribui valores as variáveis de cor
            b = 1;                        //atribui valores as variáveis de cor
        break;
        case 3:                           //caso  o valor de opção for 2 pinta de azul
            r = 0.3;                        //atribui valores as variáveis de cor
            g = 0.6;                        //atribui valores as variáveis de cor
            b = 0.3;                        //atribui valores as variáveis de cor
        break;
    }
    glutPostRedisplay();                  //chama a função desenha toda vez que for necessária
}

void gerenciaMouse(int botao, int estado, int x, int y){      //Parâmetros de entrada da função: (int button, int state, int x, int y).  Os parâmetros x e y indicam a localização do mouse no momento que o evento ocorreu.
    if(botao == GLUT_RIGHT_BUTTON)  {                           //se o botão do mouse clicado for o esquerdo
        if(estado == GLUT_DOWN){                              //O parâmetro state pode ser GLUT_UP ou GLUT_DOWN.
            if(opcao>3) {
                    opcao = 0;
            }
            escolheCor(opcao);
            printf("%d", opcao);
            opcao = opcao + 1;
        }}
    else if(botao == GLUT_LEFT_BUTTON){
            if(estado == GLUT_DOWN){                              //O parâmetro state pode ser GLUT_UP ou GLUT_DOWN.
                switch(rotacaoCod){
                    case 0: rotacaoCod = 1;
                            glutTimerFunc(10,timerPonto,1);
                            printf("\nRodando!!");break;
                    case 1: rotacaoCod=0; break;}
            }}
    glutPostRedisplay();                                      //chama a função desenha toda vez que for necessária
}

void alteraTamanhoJanela(GLsizei w, GLsizei h){           //faz o controle do tamanho das viewports (padrão de parâmetros, altura e largura) (800x600 no glutInitWindowSize)
    if(h == 0) h = 1;                                     //caso altura seja = 0, setamos ela pra 1, pra corrigir eventuais erros
    largura = w/2;                                        //largura eu divido o valor da janela por 2, para criar duas viewports do mesmo tamanho, no caso 800/2
    altura = h/2;                                           //altura eu mantenho a mesma, pois vou dividir só em duas partes.

    aspecto = (float) largura / altura;                   // largura dividida pela altura (utilizada para controlar a largura da janela automaticamente, independente de eu alterar a windowsize) (faz com que as janelas tenham a mesma proporção em cada viewport)

    glMatrixMode(GL_PROJECTION);                          //projeção do tipo modelo
    glLoadIdentity();                                     //carrega a identidade de projeção de modelo
    gluOrtho2D(-win*aspecto, win*aspecto, -win, win);     //sistema de coordenadas, agora definido de acordo com os parâmetros de janela, win e aspecto) direta x, esqueda -x, abaixo -y e acima y (cada viewport terá seu sistema de coordenadas)
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

void inicializa(){                                        // inicializa nossas variáveis
     glClearColor(1,1,1,0);                               //informa a cor de fundo da tela (branco)
     win = 50;                                            // quanto menor o valor de win, mais perto da tela (como se fosse um zoom)
}

int main(void){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);          //somente um double buffer | sistema de cores RGB
    glutInitWindowSize(800,600);                          //define o tamanho da janela
    glutInitWindowPosition(320,150);                      //medidas usadas para posicionar a janela no meio da tela - isso depende da resolução do monitor
	glutCreateWindow("Atividade 9 - ViewPort");                 //permite a criação de uma janela
    glutDisplayFunc(desenhaObjetos);                      //função de callback - chama a função desenhaObjetos
    glutReshapeFunc(alteraTamanhoJanela);                 //função que altera o tamanho da janela, redesenha o tamanho da janela
    glutKeyboardFunc(teclas);
    glutSpecialFunc(setasDirecionais);
    glutMouseFunc(gerenciaMouse);
    inicializa();
    glutMainLoop();                                       //loop infinito - escuta as informações do sistema até encerrar a aplicação
    return 0;                                             //retorna zero
}
