#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include "vertex.h"
using namespace::std;
//#define x_max 1840
//#define y_max 1000
#define x_max 400
#define y_max 300

#define multiplier 14
#define vertex_radius 6.5
#define private public

class Graph {
private:
    // Maps the coordinate location of a vertex to a vertex object
    map<pair<int, int>, Vertex> vertices;

    // This method generates the 100,000 vertices in our graph,
    // as well as the edges to go along with them.
    void initialize_graph();

public:
    Graph() {
        initialize_graph();
    };
};
