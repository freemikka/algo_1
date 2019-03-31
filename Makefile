CC = g++ -std=c++11

CompileParms = -c -Wall

OBJS = standaard.o mastermind.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Mastermind

standaard.o: standaard.cc standaard.h
	$(CC) $(CompileParms)  standaard.cc

mastermind.o: mastermind.cc mastermind.h
	$(CC) $(CompileParms)  mastermind.cc

main.o: main.cc standaard.h mastermind.h
	$(CC) $(CompileParms)  main.cc
