PROG = bin/bezier
SRC_DIR = src
OBJ_DIR = obj

FONTES = $(SRC_DIR)/AnimacaoComBezier.cpp $(SRC_DIR)/Bezier.cpp $(SRC_DIR)/InstanciaBZ.cpp $(SRC_DIR)/ListaDeCoresRGB.cpp $(SRC_DIR)/Poligono.cpp $(SRC_DIR)/Ponto.cpp $(SRC_DIR)/Temporizador.cpp
OBJETOS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(FONTES))
CPPFLAGS = -g -O3 -DGL_SILENCE_DEPRECATION -Wno-deprecated -I$(SRC_DIR)
CC = g++

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	LDFLAGS = -framework OpenGL -framework Cocoa -framework GLUT -lm
else
	LDFLAGS = -lGL -lGLU -lglut -lm
endif

# Regra para criar o binário final
$(PROG): $(OBJETOS)
	$(CC) $(CPPFLAGS) $(OBJETOS) $(LDFLAGS) -o $(PROG)

# Regra para compilar os arquivos .cpp em .o no diretório obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

# Regra para limpar os arquivos objetos e binários
clean:
	-@ rm -f $(OBJ_DIR)/*.o $(PROG)