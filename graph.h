#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
using namespace::std;

class Graph {
private:

    // This method generates the vertices in our graph,
    // as well as the edges to go along with them.
    void initialize_graph(int xmax, int ymax);

public:
    // Maps the coordinate location of a vertex(first) to an adjacency list of other vertices(second)
        //The first value (pair) is the coordinate pair location of the vertex 
        //that this vertex is adjacent to.
        //The second value (float) is the weight of the edge.
    map<pair<int, int>, map<pair<int, int>, float>> vertices;
    Graph(int xmax, int ymax);

    vector<pair<int, int>> BFS(pair<int, int> from, pair<int, int> to);
    vector<pair<int, int>> DFS(pair<int, int> from, pair<int, int> to);
};
