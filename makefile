main: main.cpp
	g++ -c main.cpp graph.cpp graph.h vertex.h
	g++ main.o -o traversals -lsfml-graphics -lsfml-window -lsfml-system
	./traversals
