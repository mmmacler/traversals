#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
using namespace::std;
//#define x_max 1840
//#define y_max 1000

#define multiplier 14
#define vertex_radius 6.5
#define private public

class Graph {
private:
    // Maps the coordinate location of a vertex(first) to an adjacency list of other vertices(second)
        //The first value (pair) is the coordinate pair location of the vertex 
        //that this vertex is adjacent to.
        //The second value (float) is the weight of the edge.
    map<pair<int, int>, map<pair<int, int>, float>> vertices;

    // This method generates the 100,000 vertices in our graph,
    // as well as the edges to go along with them.
    void initialize_graph();
    int numEdges;
    int numVertices;

public:
    Graph();
    // returns sum of shortest distance
    float Dijkstras(pair<int, int> from, pair<int, int> to);
    float Bellman_Ford(pair<int, int> from, pair<int, int> to);
};
