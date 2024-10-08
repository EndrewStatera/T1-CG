# Makefile para Windows

PROG = bezier.exe

SRC_DIR = src
OBJ_DIR = obj

ARQUIVOS = AnimacaoComBezier.cpp Bezier.cpp InstanciaBZ.cpp ListaDeCoresRGB.cpp Poligono.cpp Ponto.cpp Temporizador.cpp
FONTES = $(addprefix $(SRC_DIR)/, $(ARQUIVOS))
OBJETOS = $(addprefix $(OBJ_DIR)/, $(ARQUIVOS:.cpp=.o))

CPPFLAGS = -O3 -g -Iinclude -Wall -g  # Todas as warnings, infos de debug
# Se estiver usando mingw64, troque lib por lib\x64 abaixo
LDFLAGS = -Llib -lfreeglut -lopengl32 -lglu32 -lm
CC = g++

$(PROG): $(OBJETOS)
	$(CC) $(CPPFLAGS) $(OBJETOS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	-del /Q $(OBJ_DIR)\*.o $(PROG)
