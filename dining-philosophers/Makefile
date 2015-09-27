#
# Makefile
#

CC=gcc
CFLAGS = -Wall -O3 -lpthread
DEBUG="-g" # TODO tratar como opção do usuário 
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: dining_sem dining_cv

dining_sem: dining_sem.o
	mkdir -p $(BIN_DIR) && $(CC) -o $(BIN_DIR)/dining_sem $(SRC_DIR)/dining_sem.c $(CFLAGS)

dining_cv: dining_cv.o
	mkdir -p $(BIN_DIR) && $(CC) -o $(BIN_DIR)/dining_cv $(SRC_DIR)/dining_cv.c $(CFLAGS)

dining_sem.o:
	$(CC) -c $(SRC_DIR)/dining_sem.c

dining_cv.o:
	$(CC) -c $(SRC_DIR)/dining_cv.c

clean:
	rm *.o $(BIN_DIR)/dining_sem $(BIN_DIR)/dining_cv
	
rebuild: clean all
