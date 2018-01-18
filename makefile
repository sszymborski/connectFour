CC = g++
CLAGS = -std=c++11
LINK = -lalleg

all:	main.o game.o gui.o ai.o
	$(CC) $(CFLAGS) main.o game.o gui.o ai.o $(LINK) -o connectFour

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

game.o:	Game.cpp
	$(CC) $(CFLAGS) -c Game.cpp -o game.o

gui.o:	Gui.cpp
	$(CC) $(CFLAGS) -c Gui.cpp -o gui.o

ai.o:	AI.cpp
	$(CC) $(CFLAGS) -c AI.cpp -o ai.o

clean:
	rm -f *.o
