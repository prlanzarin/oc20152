#
# Makefile
#

CC=gcc
DEBUG="-g" # TODO tratar como opção do usuário 
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: 

mfork: $(SRC_DIR)/matrix_fork.c parser.o matrix.o
	$(CC) $(DEBUG) -o $(BIN_DIR)/matrix_fork $(SRC_DIR)/matrix_fork.c $(BIN_DIR)/*.o -Wall
	
parser.o: $(INC_DIR)/parser.h $(SRC_DIR)/parser.c matrix.o
	mkdir -p $(BIN_DIR) && $(CC) $(DEBUG) -c -o $(BIN_DIR)/parser.o $(SRC_DIR)/parser.c -Wall

matrix.o: $(INC_DIR)/matrix.h $(SRC_DIR)/matrix.c
	mkdir -p $(BIN_DIR) && $(CC) $(DEBUG) -c -o $(BIN_DIR)/matrix.o $(SRC_DIR)/matrix.c -Wall

clean:
	rm -rf $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~

#regra2: #dependências para a regra2
#
#$(CC) -o $(BIN_DIR)regra2 $(SRC_DIR)regra2.c -Wall
#
#regran: #dependências para a regran
#	$(CC) -o $(BIN_DIR)regran $(SRC_DIR)regran.c -Wall
#
#clean:
#	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~
