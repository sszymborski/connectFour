CC = g++
LINK = -lalleg

all:	main.o gra.o gui.o
	$(CC) main.o gra.o gui.o $(LINK) -o connectFour

main.o: main.cpp
	$(CC) -c main.cpp -o main.o

gra.o: Gra.cpp
	$(CC) -c Gra.cpp -o gra.o

gui.o:	Gui.cpp
	$(CC) -c Gui.cpp -o gui.o

clean:
	rm -f *.o
