#
# Makefile
#

CC=gcc
DEBUG="-g" # TODO tratar como opção do usuário 
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: dining_sem.o
	gcc -o $(BIN_DIR)/dining_sem $(SRC_DIR)/dining_sem.c -lpthread

dining_sem.o:
	gcc -c $(SRC_DIR)/dining_sem.c

clean:
	rm *.o $(BIN_DIR)/dining_sem
	

