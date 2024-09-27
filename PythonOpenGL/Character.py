from Ponto import *
from Curva import *

class Character:
    
    def __init__ (self, modelo, ponto, rotacao, escala, curva):
        self.modelo = modelo
        self.ponto = ponto 
        self.rotacao = rotacao
        self.escala = escala
        self.curva = curva
        pass
    
    @classmethod
    def translate(self, direction):
        self.calculaDeslocamento(direction)
        pass
    
    @classmethod
    def associaCurva(self ,curva):
        self.curva = curva
        pass
        
    @classmethod
    def calculaDeslocamento(self, deslocamento):
        t = deslocamento
        um_menos_t = 1-t
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
        pass