main: main.cpp
	g++ -c main.cpp graph.cpp
	g++ main.o graph.o -o traversals -lsfml-graphics -lsfml-window -lsfml-system
	./traversals
