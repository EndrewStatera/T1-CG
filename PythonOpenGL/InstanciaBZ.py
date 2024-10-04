# ************************************************
#   InstanciaBZ.py
#   Define a classe Instancia
#   Autor: Márcio Sarroglia Pinho
#       pinho@pucrs.br
# ************************************************

from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from Ponto import *

""" Classe Instancia """
class InstanciaBZ:   
    def __init__(self):
        self.t = 0
        print(self.tt)
        self.posicao = Ponto (0,0,0) 
        self.escala = Ponto (1,1,1)
        self.rotacao:float = 0.0
        self.modelo = None
    
    """ Imprime os valores de cada eixo do ponto """
    # Faz a impressao usando sobrecarga de funcao
    # https://www.educative.io/edpresso/what-is-method-overloading-in-python
    def imprime(self, msg=None):
        if msg is not None:
            pass 
        else:
            print ("Rotacao:", self.rotacao)

    """ Define o modelo a ser usada para a desenhar """
    def setModelo(self, func):
        self.modelo = func

    def Desenha(self):
        #print ("Desenha")
        #self.escala.imprime("\tEscala: ")
        #print ("\tRotacao: ", self.rotacao)
        glPushMatrix()
        glTranslatef(self.posicao.x, self.posicao.y, 0)
        glRotatef(self.rotacao, 0, 0, 1)
        glScalef(self.escala.x, self.escala.y, self.escala.z)
        self.modelo()
        glPopMatrix()
        
    def translate(self, delta):
        P = self.curva.Calcula(self.tt)
        if self.t <= 1.0:
            self.t += delta
        else:
            self.t = 0.0
        return P
    
    @classmethod
    def associaCurva(self ,curva):
        self.curva = curva
        pass

    def printT(self):
        print(self.tt)
    @classmethod
    def calculaDeslocamento(self, deslocamento):
        t = deslocamento
        um_menos_t = 1-t
        '''
        lista_pontos_curva = self.curva.lst_pt
        if len(self.curva.lst_pt) == 3:
            p0 = lista_pontos_curva[0]
            p1 = lista_pontos_curva[1]
            p2 = lista_pontos_curva[2]
            
            c1x = (um_menos_t**2 * p0.x) + (2*um_menos_t * t * p1.x) + (t**2 * p2.x)
            c1y = (um_menos_t**2 * p0.y) + (2*um_menos_t * t * p1.y) + (t**2 * p2.y)
            c1 = Ponto()
            c1.set(c1x, c1y)
            self.ponto = c1
            return c1
        '''
        return self.curva.Calcula(deslocamento)

    
