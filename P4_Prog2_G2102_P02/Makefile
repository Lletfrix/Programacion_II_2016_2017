################            Macros            ################
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
EJS = p4_e1 p4_e2_test p4_e2 p4_e2_bal p4_e3 p4_e4
################            Objects           ################
OB_E1 = p4_e1.o functions.o  tree.o node_p4.o list.o
OB_E2 = p4_e2.o tree.o list.o functions.o node_p4.o
OB_E2T = p4_e2_test.o tree.o list.o functions.o node_p4.o
OB_E3 = p4_e3.o tree.o list.o functions.o node_p4.o
OB_E4 = p4_e4.o tree.o functions.o node_p4.o list.o
################             Make             ################

.PHONY: all
all: $(EJS)

p4_e1: $(OB_E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OB_E1)

p4_e1.o: p4_e1.c functions.h tree.h node.h list.h
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2_test: $(OB_E2T)
	$(CC) $(CFLAGS) -o p4_e2_test $(OB_E2T)

p4_e2_test.o: p4_e2_test.c functions.h tree.h list.h node.h
	$(CC) $(CFLAGS) -c p4_e2_test.c

p4_e2: $(OB_E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OB_E2)

p4_e2_bal: $(OB_E2)
	$(CC) $(CFLAGS) -o p4_e2_bal $(OB_E2)

p4_e2.o: p4_e2.c tree.h functions.h list.h node.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e3: $(OB_E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OB_E3)

p4_e3.o: p4_e3.c tree.h list.h functions.h node.h
	$(CC) $(CFLAGS) -c p4_e3.c

p4_e4: $(OB_E4)
	$(CC) $(CFLAGS) -o p4_e4 $(OB_E4)

p4_e4.o: p4_e4.c tree.h functions.h list.h node.h
	$(CC) $(CFLAGS) -c p4_e4.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

node_p4.o: node_p4.c node.h
	$(CC) $(CFLAGS) -c node_p4.c

.PHONY: clear
clear:
	rm -rf *.o 

.PHONY: clean
clean:
	rm -rf *.o $(EJS)

.PHONY: run
run:	
	@echo "\n***************************\n****** RUNNING p4_e1 ******\n***************************\n"
	./p4_e1 numeros.txt
	@echo "\n********************************\n****** RUNNING p4_e2_test ******\n********************************\n"
	./p4_e2_test
	@echo "\n***************************\n****** RUNNING p4_e2 ******\n***************************\n"
	./p4_e2 dict10.dat
	@echo "\n*******************************\n****** RUNNING p4_e2_bal ******\n*******************************\n"
	./p4_e2_bal dict10.dat
	@echo "\n***************************\n****** RUNNING p4_e3 ******\n***************************\n"
	./p4_e3 numeros.txt
	@echo "\n***************************\n****** RUNNING p4_e4 ******\n***************************\n"
	./p4_e4 cadenas.txt

.PHONY: runv
runv:
	@echo "\n*****************************************\n****** RUNNING p4_e1 WITH VALGRIND ******\n*****************************************\n"
	valgrind --leak-check=full ./p4_e1 numeros.txt
	@echo "\n**********************************************\n****** RUNNING p4_e2_test WITH VALGRIND ******\n**********************************************\n"
	valgrind --leak-check=full ./p4_e2_test
	@echo "\n*****************************************\n****** RUNNING p4_e2 WITH VALGRIND ******\n*****************************************\n"
	valgrind --leak-check=full ./p4_e2 dict10.dat
	@echo "\n*********************************************\n****** RUNNING p4_e2_bal WITH VALGRIND ******\n*********************************************\n"
	valgrind --leak-check=full ./p4_e2_bal dict10.dat
	@echo "\n*****************************************\n****** RUNNING p4_e3 WITH VALGRIND ******\n*****************************************\n"
	valgrind --leak-check=full ./p4_e3 numeros.txt
	@echo "\n*****************************************\n****** RUNNING p4_e4 WITH VALGRIND ******\n*****************************************\n"
	valgrind --leak-check=full ./p4_e4 cadenas.txt
