CC=gcc
CFLAGS=-Wall -g -pedantic -ansi
EJS = p3_e1 p3_e2 p3_e3 p3_e4

OBJSP3_E1= p3_e1.o functions.o node.o  queue.o list.o
OBJSP3_E2= p3_e2.o functions.o queue.o graph.o node.o list.o
OBJSP3_E3 = p3_e3.o functions.o list.o node.o
OBJSP3_E4 = p3_e4.o functions.o list.o graph-list.o node.o queue.o

.PHONY: all
all: $(EJS)
p3_e1:$(OBJSP3_E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJSP3_E1)

p3_e1.o: p3_e1.c functions.h node.h queue.h list.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2:$(OBJSP3_E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJSP3_E2)

p3_e2.o: p3_e2.c functions.h queue.h graph.h list.h node.h
	$(CC) $(CFLAGS) -c p3_e2.c

p3_e3: $(OBJSP3_E3)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJSP3_E3)

p3_e3.o: p3_e3.c functions.h list.h node.h
	$(CC) $(CFLAGS) -c p3_e3.c

p3_e4: $(OBJSP3_E4)
	$(CC) $(CFLAGS) -o  p3_e4 $(OBJSP3_E4)

p3_e4.o: p3_e4.c graph.h node.h
	$(CC) $(CFLAGS) -c p3_e4.c

functions.o: functions.c functions.h list.h
	$(CC) $(CFLAGS) -c functions.c

node.o: node.c node.h types.h
	$(CC) $(CFLAGS) -c node.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

graph-list.o: graph-list.c graph.h functions.h list.h
	$(CC) $(CFLAGS) -c graph-list.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

.PHONY: clean
clean:
	rm -rf *.o
