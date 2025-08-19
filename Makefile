run: gameoflife.o
	./gameoflife.o
gameoflife.o: main.o inputHandler.o
	g++ -o gameoflife.o main.o inputHandler.o -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp main.h 
	g++ -c main.cpp 
inputHandler.o: inputHandler.cpp main.h
	g++ -c inputHandler.cpp 
clean:
	rm -f *.o