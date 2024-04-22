#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <map>
#include <random>
#include <SFML/Graphics.hpp>
using namespace::std;
//#define x_max 1840
//#define y_max 1000
#define x_max 400
#define y_max 300

#define multiplier 14
#define vertex_radius 6.5
#define private public

struct Vertex {

    //TODO: Determine if we actually want to use this
    // to be potentially used with dijkstra's implementation
    bool visited;

    //Stores edges connecting to adjacent vertices.
    //The first value (pair) is the coordinate pair location of the vertex 
    //that this vertex is adjacent to.
    //The second value (float) is the weight of the edge.
    map<pair<int, int>, float> adjacent_vertices;
};