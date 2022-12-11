#
# Copyright 2021 Alysson Ribeiro da Silva - Federal University of Minas Gerais
#
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to deal 
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
# of the Software, and to permit persons to whom the Software is furnished to do 
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

# cc and flags
CC = g++ -pg
CFLAGS = -std=c++11 -g -Wall -c -pg -I $(INC)

# folders
INC = include
BIN = bin
OBJ = obj
SRC = src

# all sources, objs, and header files
OBJS = $(OBJ)/Significado.o $(OBJ)/FilaCelula.o $(OBJ)/FilaSignificado.o $(OBJ)/main.o $(OBJ)/memlog.o
HDRS = $(INC)/Significado.hpp $(INC)/FilaCelula.hpp $(INC)/FilaSignificado.hpp $(INC)/memlog.h $(INC)/msgassert.h 

TARGET = $(BIN)/run.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(BIN)/run.out $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/Significado.o: $(HDRS) $(SRC)/Significado.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Significado.o $(SRC)/Significado.cpp 

$(OBJ)/FilaCelula.o: $(HDRS) $(SRC)/FilaCelula.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/FilaCelula.o $(SRC)/FilaCelula.cpp

$(OBJ)/FilaSignificado.o: $(HDRS) $(SRC)/FilaSignificado.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/FilaSignificado.o $(SRC)/FilaSignificado.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 

clean:
	@rm -rf $(OBJ)* $(BIN)*
