CC = g++
LINK = -lalleg

all:	main.o game.o gui.o ai.o
	$(CC) main.o game.o gui.o ai.o $(LINK) -o connectFour

main.o: main.cpp
	$(CC) -c main.cpp -o main.o

game.o:	Game.cpp
	$(CC) -c Game.cpp -o game.o

gui.o:	Gui.cpp
	$(CC) -c Gui.cpp -o gui.o

ai.o:	AI.cpp
	$(CC) -c AI.cpp -o ai.o

clean:
	rm -f *.o
