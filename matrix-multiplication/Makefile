#
# Makefile
#

CC=gcc
DEBUG="-g" # TODO tratar como opção do usuário 
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: 

matrix_fork: $(SRC_DIR)/matrix_fork.c parser.o
	$(CC) -o $(SRC_DIR)/matrix_fork $(SRC_DIR)/matrix_fork.c $(BIN_DIR)/parser.o -Wall
	
parser.o: $(INC_DIR)/parser.h $(SRC_DIR)/parser.c
	mkdir -p $(BIN_DIR) && $(CC) $(DEBUG) -c -o $(BIN_DIR)/parser.o $(SRC_DIR)/parser.c -Wall

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
