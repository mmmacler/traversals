main: main.cpp
	g++ -c main.cpp
	g++ main.o -o traversals -lsfml-graphics -lsfml-window -lsfml-system
	./traversals
