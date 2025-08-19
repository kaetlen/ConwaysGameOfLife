run: main.o
	./main.o

main.o: main.cpp main.h
	g++ -o main.o main.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o