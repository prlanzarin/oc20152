#
# Makefile
#

CC=gcc
CFLAGS =-Wall -O3
DEBUG="-g" # TODO tratar como opção do usuário 
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
EXE =./bin/matrix_p ./bin/matrix_fork ./bin/generator ./bin/checker

all: mfork pmatrix generator checker

mfork: $(SRC_DIR)/matrix_fork.c utils.o matrix.o
	$(CC) $(DEBUG) -o $(BIN_DIR)/matrix_fork $(SRC_DIR)/matrix_fork.c $(BIN_DIR)/*.o $(CFLAGS) 
	
pmatrix: $(SRC_DIR)/matrix_pthread.c utils.o matrix.o
	$(CC) $(DEBUG) -o $(BIN_DIR)/matrix_p $(SRC_DIR)/matrix_pthread.c $(BIN_DIR)/*.o $(CFLAGS) -pthread

generator: $(SRC_DIR)/matrix_generator.c utils.o matrix.o
	$(CC) $(DEBUG) -o $(BIN_DIR)/generator $(SRC_DIR)/matrix_generator.c $(BIN_DIR)/*.o $(CFLAGS) 

checker: $(SRC_DIR)/checker.c utils.o matrix.o
	$(CC) $(DEBUG) -o $(BIN_DIR)/checker $(SRC_DIR)/checker.c $(BIN_DIR)/*.o $(CFLAGS) 
	
utils.o: $(INC_DIR)/utils.h $(SRC_DIR)/utils.c matrix.o
	mkdir -p $(BIN_DIR) && $(CC) $(DEBUG) -c -o $(BIN_DIR)/utils.o $(SRC_DIR)/utils.c $(CFLAGS) 

matrix.o: $(INC_DIR)/matrix.h $(SRC_DIR)/matrix.c
	mkdir -p $(BIN_DIR) && $(CC) $(DEBUG) -c -o $(BIN_DIR)/matrix.o $(SRC_DIR)/matrix.c $(CFLAGS) 

clean:
	rm -rf $(BIN_DIR)/*.o $(EXE) $(SRC_DIR)/*~ $(INC_DIR)/*~ *~

rebuild: clean all
	
