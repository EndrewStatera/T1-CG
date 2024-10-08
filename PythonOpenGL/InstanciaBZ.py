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
        print(self.t)
        self.posicao = Ponto (0,0,0) 
        self.escala = Ponto (1,1,1)
        self.rotacao:float = 0.0
        self.modelo = None
        self.next_curve = None
        self.curve = None
        self.direction = 1
    
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
        P = self.curve.Calcula(self.t)
        if self.t <= 1.0:
            self.t += delta
            if(self.next_curve == None and self.t > 0.5):
                self.get_next_curve()
        else:
            self.t = 0.0
            self.curve = self.next_curve
            self.next_curve = None
        self.posicao.x = P.x
        self.posicao.y = P.y
        return P

    def get_next_curve(self):
        self.next_curve = self.curve.random_curve()

    def associaCurva(self, curva):
        self.curve = curva
        pass

    def change_direction(self):
        self.direction *= -1

    def posicao_final_curva(self):
        return self.curve.Calcula(1*self.direction)
    
