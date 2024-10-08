// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Ponto.h"
#include "Poligono.h"
#include "InstanciaBZ.h"

#include "Temporizador.h"
#include "ListaDeCoresRGB.h"

Temporizador T;
double AccumDeltaT = 0;
Temporizador T2;

InstanciaBZ Personagens[10];

Bezier Curvas[20];
unsigned int nCurvas;

Ponto pontos[100];
int curvasConectadas[30][30] = {-1};
int nConexoesPorPonto[50];
unsigned int nPontos;


// Limites l�gicos da �rea de desenho
Ponto Min, Max;

bool desenha = false;

Poligono Mapa, MeiaSeta, Mastro;
int nInstancias = 0;

float angulo = 0.0;

double nFrames = 0;
double TempoTotal = 0;

double t=0.0;
//double DeltaT = 1.0/50;

// **********************************************************************
//
// **********************************************************************

int gameOver = 0;
double accumBuscaColisao = 0;
void buscaColisao();

void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    accumBuscaColisao += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0 / 3) // fixa a atualiza��o da tela em 30
    {
        AccumDeltaT = 0;
        angulo += 2;
        if (gameOver = 0)
            glutPostRedisplay();
    }

    if (accumBuscaColisao > 1) {
        accumBuscaColisao = 0;
        buscaColisao();
    }

    if (TempoTotal > 5.0)
    {
        cout << "Tempo Acumulado: " << TempoTotal << " segundos. ";
        cout << "Nros de Frames sem desenho: " << nFrames << endl;
        cout << "FPS(sem desenho): " << nFrames / TempoTotal << endl;
        TempoTotal = 0;
        nFrames = 0;
    }
}
// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
// **********************************************************************
void reshape(int w, int h)
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites logicos da area OpenGL dentro da Janela
    glOrtho(Min.x+10, Max.x-10, Min.y+10, Max.y-10, -10, +10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// **********************************************************************
// **********************************************************************
void DesenhaEixos()
{
    Ponto Meio;
    Meio.x = (Max.x + Min.x) / 2;
    Meio.y = (Max.y + Min.y) / 2;
    Meio.z = (Max.z + Min.z) / 2;

    glBegin(GL_LINES);
    //  eixo horizontal
    glVertex2f(Min.x, Meio.y);
    glVertex2f(Max.x, Meio.y);
    //  eixo vertical
    glVertex2f(Meio.x, Min.y);
    glVertex2f(Meio.x, Max.y);
    glEnd();
}

void DesenhaPersonagem()
{
    defineCor(Personagens[0].cor);
    //glTranslatef(0,0,0);
    Mastro.desenhaPoligono();
}
// **********************************************************************
// void DesenhaTriangulo()
// **********************************************************************
void DesenhaTriangulo()
{
    //defineCor(OrangeRed);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.3,-0.3);
        glVertex2f(0, 0.3);
        glVertex2f(0.3,-0.3);
    glEnd();
}
// **********************************************************************
// Esta funcao deve instanciar todos os personagens do cenario
// **********************************************************************
void CriaInstancias()
{
    /*Personagens[0].Posicao = Curvas[0].getPC(0);
    Personagens[0].Rotacao = 0;
    Personagens[0].modelo = DesenhaTriangulo;
    Personagens[0].Escala = Ponto(1, 1, 1);
    Personagens[0].Curva = Curvas[0];
    Personagens[0].Velocidade = 1.1;

    Personagens[1].Posicao = Curvas[1].getPC(0);
    Personagens[1].Rotacao = 0;
    Personagens[1].modelo = DesenhaTriangulo;
    Personagens[1].Escala = Ponto(1, 1, 1);
    Personagens[1].Curva = Curvas[1];
    Personagens[1].Velocidade = 1;

    Personagens[2].Posicao = Curvas[2].getPC(0);
    Personagens[2].Rotacao = 0;
    Personagens[2].modelo = DesenhaTriangulo;
    Personagens[2].Escala = Ponto(1, 1, 1);
    Personagens[2].Curva = Curvas[2];
    Personagens[2].Velocidade = 0.8;*/

        Personagens[0].Posicao = Curvas[0].getPC(0);
        Personagens[0].Rotacao = 0;
        Personagens[0].modelo = DesenhaPersonagem;
        Personagens[0].Escala = Ponto(1, 1, 1);
        Personagens[0].Curva = Curvas[0];
        Personagens[0].Velocidade = 1.5;
        Personagens[0].cor = SpicyPink;

    nInstancias = 10;
    for(int i = 1; i < nInstancias; i++){
        Personagens[i].Posicao = Curvas[i].getPC(0);
        Personagens[i].Rotacao = 0;
        Personagens[i].modelo = DesenhaTriangulo;
        Personagens[i].Escala = Ponto(1, 1, 1);
        Personagens[i].Curva = Curvas[i];
        Personagens[i].Velocidade = 1 + i/10;
        Personagens[i].cor = i;
    }

}
// **********************************************************************
//  Carrega os modelos que poderão representar os personagens
// **********************************************************************
void CarregaModelos()
{
    MeiaSeta.LePoligono("MeiaSeta.txt");
    Mastro.LePoligono("Mastro.txt");
    
    Ponto A, B;
    Mapa.obtemLimites(A,B);
    cout << "Limites do Mapa" << endl;
    A.imprime();
    cout << endl;
    B.imprime();
    cout << endl;
}
// **********************************************************************
//  Este metodo deve ser alterado para ler as curvas de um arquivo texto
// **********************************************************************
void CriaCurvas()
{   
    /*pontos[0] = Ponto(-2,3);
    pontos[1] = Ponto(2,3);
    pontos[2] = Ponto(-4,0);
    pontos[3] = Ponto(0,0);
    pontos[4] = Ponto(4,0);
    pontos[5] = Ponto(-2,-3);
    pontos[6] = Ponto(2,-3);

    nPontos = 7;

    Curvas[0] = Bezier(pontos[0],pontos[3],pontos[1]);
    Curvas[1] = Bezier(pontos[1], pontos[3], pontos[4]);
    Curvas[2] = Bezier(pontos[4], pontos[3], pontos[6]);
    Curvas[3] = Bezier(pontos[6], pontos[3], pontos[5]);
    Curvas[4] = Bezier(pontos[5], pontos[3],pontos[2]);
    Curvas[5] = Bezier(pontos[2], pontos[3], pontos[0]);
    Curvas[6] = Bezier(pontos[0], pontos[1], pontos[3]);
    Curvas[7] = Bezier(pontos[1], pontos[4], pontos[3]);
    Curvas[8] = Bezier(pontos[4], pontos[6], pontos[3]);
    Curvas[9] = Bezier(pontos[6], pontos[5], pontos[3]);
    Curvas[10] = Bezier(pontos[5], pontos[2], pontos[3]);
    Curvas[11] = Bezier(pontos[2], pontos[0], pontos[3]);
    Curvas[12] = Bezier(pontos[2], pontos[3], pontos[4]);
    
    nCurvas = 13;*/

    Mapa.LePoligono("verticesTeste.txt");
    nPontos = Mapa.getNVertices();
    for(int i = 0; i < Mapa.getNVertices(); i++){
        pontos[i] = Mapa.getVertice(i);
        //cout << "\nPonto: " << i << ": " << pontos[i].x << pontos[i].y;
    }
    Curvas[0] = Bezier(pontos[0], pontos[1], pontos[3]);
    Curvas[1] = Bezier(pontos[0], pontos[2], pontos[5]);
    Curvas[2] = Bezier(pontos[3], pontos[6], pontos[8]);
    Curvas[3] = Bezier(pontos[5], pontos[7], pontos[8]);
    Curvas[4] = Bezier(pontos[0], pontos[9], pontos[4]);
    Curvas[5] = Bezier(pontos[4], pontos[10], pontos[8]);
    Curvas[6] = Bezier(pontos[4], pontos[11], pontos[5]);
    Curvas[7] = Bezier(pontos[4], pontos[12], pontos[3]);
    Curvas[8] = Bezier(pontos[13], pontos[19], pontos[0]);
    Curvas[9] = Bezier(pontos[0], pontos[20], pontos[14]);
    Curvas[10] = Bezier(pontos[15], pontos[17], pontos[8]);
    Curvas[11] = Bezier(pontos[8], pontos[18], pontos[16]);
    Curvas[12] = Bezier(pontos[13], pontos[21], pontos[3]);
    Curvas[13] = Bezier(pontos[14], pontos[22], pontos[5]);
    Curvas[14] = Bezier(pontos[3], pontos[23], pontos[15]);
    Curvas[15] = Bezier(pontos[5], pontos[24], pontos[16]);
    Curvas[16] = Bezier(pontos[13], pontos[1], pontos[4]);
    Curvas[17] = Bezier(pontos[14], pontos[2], pontos[4]);
    Curvas[18] = Bezier(pontos[15], pontos[6], pontos[4]);
    Curvas[19] = Bezier(pontos[16], pontos[7], pontos[4]);


    nCurvas = 20;
    
}

bool comparaPontos(Ponto a, Ponto b){
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
void linkarPontosComCurva(){
    for(int i = 0; i < nPontos; i++){
        for(int j = 0; j < nCurvas; j++){
            if(comparaPontos(pontos[i], Curvas[j].getPC(0)) || comparaPontos(pontos[i], Curvas[j].getPC(2))){
                curvasConectadas[i][nConexoesPorPonto[i]] = j;
                nConexoesPorPonto[i]++;
            }
        }
        cout << "\nPonto " << i << "tem: " << nConexoesPorPonto[i] << "conexões";
    }
}

int getProxCurva(Ponto p, Bezier curvaAtual){
    for(int i = 0; i < nPontos; i++){
        if(comparaPontos(pontos[i], p)){
            int rand = p.numeroRand(nConexoesPorPonto[i]-1);
            while(comparaPontos(Curvas[curvasConectadas[i][rand]].getPC(0),curvaAtual.getPC(0)) && comparaPontos(Curvas[curvasConectadas[i][rand]].getPC(2),curvaAtual.getPC(2))){
                rand = p.numeroRand(nConexoesPorPonto[i]-1);
            }
            return curvasConectadas[i][rand];
        }
    }
    return -1;
}

// **********************************************************************
//
// **********************************************************************
void AssociaPersonagemComCurva(int p, int c)
{
    Personagens[p].Curva = Curvas[c];
}
void AssociaPersonagemComCurva(int p, Bezier *c)
{
    Personagens[p].Curva = *c;
}
// **********************************************************************
//
// **********************************************************************
void init()
{
    // carrega as curvas que farao parte do cenario
    CriaCurvas();
    linkarPontosComCurva();

    // Define a cor do fundo da tela
    glClearColor(0.05f, 0.0f, 0.3f, 0.2f);

    // carrega os modelos armazenados em arquivos
    CarregaModelos();
    
    // cria instancias do modelos
    CriaInstancias();

    // define is limites da área de desenho
    float d = 15;
    Min = Ponto(-d, -d);
    Max = Ponto(d, d);
}

// **********************************************************************
void DesenhaPersonagens(float tempoDecorrido)
{
    //cout << "nInstancias: " << nInstancias << endl;
    for (int i = 0; i < nInstancias; i++)
    {
        Personagens[i].AtualizaPosicao(tempoDecorrido);
        defineCor(Personagens[i].cor);
        Personagens[i].desenha();
    }
}
void DesenhaPoligonoDeControle(int curva)
{
    Ponto P;
    glBegin(GL_LINE_STRIP);
    for (int v=0;v<3;v++)
    {
        P = Curvas[curva].getPC(v);
        glVertex2d(P.x, P.y);
    }
    glEnd();
}
// **********************************************************************
//
// **********************************************************************
void DesenhaCurvas()
{
    for (int i = 0; i < nCurvas; i++)
    {
        defineCor(Curvas[i].cor);
        glLineWidth(2);
        Curvas[i].Traca();

        //defineCor(VioletRed);
        //glLineWidth(2);
        //DesenhaPoligonoDeControle(i);
    }
}

bool verificaColisao(int p1, int p2) {
    double raioColisao = Personagens[p1].Velocidade / 10;

    double distancia = calculaDistancia(Personagens[p1].Posicao, Personagens[p2].Posicao);

    return distancia <= raioColisao * 2;
}

void buscaColisao() {
    for (int i = 0; i < nInstancias; i++) {
        for (int j = i + 1; j < nInstancias; j++)
        {
            if (verificaColisao(i, j)) {
                // handle colision
                // Personagens[i].direcao = (Personagens[i].direcao + 1) % 2;
                // cout << "Colisao detectada entre Personagem " << i << " e Personagem " << j << endl;
                gameOver = 1;
                
            }
        }
            
    }
}

void anda(int p){
    Ponto pontoAtual;
    Ponto proxPonto;
    //double DeltaT = 1.0/50.0;
    double DeltaT = Personagens[p].Curva.CalculaT(Personagens[p].Velocidade)/10;
    // << "\nDeltaT: " << DeltaT << "\n";
    //cout << "\nComprimentoTotalCurva: " << Personagens[p].Curva.ComprimentoTotalDaCurva << "\n";
    pontoAtual = Personagens[p].Curva.Calcula(Personagens[p].tAtual);
    Personagens[p].Posicao = pontoAtual;

    if(Personagens[p].direcao == 0){//Indo do inicio ao fim da curva
        proxPonto = Personagens[p].Curva.Calcula(Personagens[p].tAtual+DeltaT*3);
        if(Personagens[p].tAtual < 1.0){
            Personagens[p].tAtual += DeltaT;
            if(Personagens[p].tAtual >= 0.5 && Personagens[p].proxCurva == -1){
                Personagens[p].proxCurva = getProxCurva(Personagens[p].Curva.getPC(2),Personagens[p].Curva);
                Curvas[Personagens[p].proxCurva].cor = SpicyPink;
            }
        }else{
            if(comparaPontos(Curvas[Personagens[p].proxCurva].getPC(0), Personagens[p].Curva.getPC(2))){
                Personagens[p].tAtual = 0.0;
                Personagens[p].direcao = 0;
            }else if(comparaPontos(Curvas[Personagens[p].proxCurva].getPC(2), Personagens[p].Curva.getPC(2))){
                Personagens[p].direcao = 1;
            }
            AssociaPersonagemComCurva(p,Personagens[p].proxCurva);
            Curvas[Personagens[p].proxCurva].cor = SkyBlue;
            Personagens[p].proxCurva = -1;
        }
        
    }
    
    else{//Indo do fim ao inicio da curva
        proxPonto = Personagens[p].Curva.Calcula(Personagens[p].tAtual-DeltaT*3);
        if(Personagens[p].tAtual > 0.0){
            Personagens[p].tAtual -= DeltaT;
            if(Personagens[p].tAtual <= 0.5 && Personagens[p].proxCurva == -1){
                Personagens[p].proxCurva = getProxCurva(Personagens[p].Curva.getPC(0),Personagens[p].Curva);
                Curvas[Personagens[p].proxCurva].cor = SpicyPink;
            }
        }else{
            if(comparaPontos(Curvas[Personagens[p].proxCurva].getPC(2),Personagens[p].Curva.getPC(0))){
                Personagens[p].tAtual = 1.0;
                Personagens[p].direcao = 1;
            }else if(comparaPontos(Curvas[Personagens[p].proxCurva].getPC(0), Personagens[p].Curva.getPC(0))){
                Personagens[p].direcao = 0;
            }
            AssociaPersonagemComCurva(p,Personagens[p].proxCurva);
            Curvas[Personagens[p].proxCurva].cor = SkyBlue;
            Personagens[p].proxCurva = -1;
        }
    }
    Personagens[p].Rotacao = 180/M_PI * atan2(proxPonto.y-pontoAtual.y,proxPonto.x-pontoAtual.x) - 90;
}
// **********************************************************************
//  void display( void )
// **********************************************************************
void display(void)
{

    // Limpa a tela coma cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites l�gicos da �rea OpenGL dentro da Janela
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // Coloque aqui as chamadas das rotinas que desenham os objetos
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    glLineWidth(1);
    glColor3f(1, 1, 1); // R, G, B  [0..1]

    //DesenhaEixos();

    DesenhaCurvas();
    
    // Desenha os personagens no tempo T2.getDeltaT()
    DesenhaPersonagens(T2.getDeltaT());

    for(int i = 1; i < nInstancias; i++){
        anda(i);
    }
    glutSwapBuffers();
}


// **********************************************************************
// ContaTempo(double tempo)
//      conta um certo n�mero de segundos e informa quanto frames
// se passaram neste per�odo.
// **********************************************************************
void ContaTempo(double tempo)
{
    Temporizador T;

    unsigned long cont = 0;
    cout << "Inicio contagem de " << tempo << "segundos ..." << flush;
    while (true)
    {
        tempo -= T.getDeltaT();
        cont++;
        if (tempo <= 0.0)
        {
            cout << "fim! - Passaram-se " << cont << " frames." << endl;
            break;
        }
    }
}
// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
// **********************************************************************
void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 27:     // Termina o programa qdo
        exit(0); // a tecla ESC for pressionada
        break;
    case 't':
        ContaTempo(3);
        break;
    case ' ':
        desenha = !desenha;
        break;
    default:
        break;
    }
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
// **********************************************************************
void arrow_keys(int a_keys, int x, int y)
{
    Ponto P;
    switch (a_keys)
    {
    case GLUT_KEY_LEFT:
        
        Personagens[0].Posicao.x -= 0.5;
        break;
    case GLUT_KEY_RIGHT:
        Personagens[0].Posicao.x += 0.5;
        break;
    case GLUT_KEY_UP:     // Se pressionar UP
        t += Personagens[0].Curva.CalculaT(Personagens[0].Velocidade)/10;
        P = Personagens[0].Curva.Calcula(t);
        Personagens[0].Posicao = P;
        //glutFullScreen(); // Vai para Full Screen
        break;
    case GLUT_KEY_DOWN: // Se pressionar UP
        t -= Personagens[0].Curva.CalculaT(Personagens[0].Velocidade)/10;
        P = Personagens[0].Curva.Calcula(t);
        Personagens[0].Posicao = P;
                        // Reposiciona a janela
        //glutPositionWindow(50, 50);
        //glutReshapeWindow(700, 500);
        break;
    default:
        break;
    }
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
// **********************************************************************
int main(int argc, char **argv)
{
    cout << "Programa OpenGL" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize(650, 650);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de t�tulo da janela.
    glutCreateWindow("Animacao com Bezier");

    // executa algumas inicializa��es
    init();

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // ser� chamada automaticamente quando
    // for necess�rio redesenhar a janela
    glutDisplayFunc(display);

    // Define que o tratador de evento para
    // o invalida��o da tela. A funcao "display"
    // ser� chamada automaticamente sempre que a
    // m�quina estiver ociosa (idle)
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // ser� chamada automaticamente quando
    // o usu�rio alterar o tamanho da janela
    glutReshapeFunc(reshape);

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // ser� chamada automaticamente sempre
    // o usu�rio pressionar uma tecla comum
    glutKeyboardFunc(keyboard);

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" ser� chamada
    // automaticamente sempre o usu�rio
    // pressionar uma tecla especial
    glutSpecialFunc(arrow_keys);

    // inicia o tratamento dos eventos
    glutMainLoop();

    return 0;
}
