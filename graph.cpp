#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include "graph.h"
#include <set>
#include <queue>
#include <stack>
using namespace::std;
//#define x_max 1840
//#define y_max 1000
#define x_max 200
#define y_max 200

#define multiplier 14
#define vertex_radius 6.5
#define private public

void Graph::initialize_graph() {
    // Random number generation taken from
    // https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    // and
    // https://stackoverflow.com/questions/686353/random-float-number-generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-(x_max/2), x_max/2);

    // Generate the 100,000 vertices
    // Uses a 'while' loop in case we generate duplicate values
    // by chance, leading to less than 100k vertices
    // while (vertices.size() < 100000) {
    while (vertices.size() < (x_max*y_max)/25 ) {
        int x = distr(gen);
        std::uniform_int_distribution<> distr(-(y_max/2), y_max/2);
        int y = distr(gen);
        map<pair<int, int>, float> temp;
        vertices.insert({{x, y}, temp});
    }

    //Generate edges and their weights
    for (auto p: this->vertices) {
        //counter for how many other valid vertices we've found
        int found = p.second.size();
        //just aliasing to shorter variable names
        int my_x = p.first.first;
        int my_y = p.first.second;

        // check a 19x19 area around the vertex for other vertices
        // we look further out first to avoid the problem of creating
        // isolated clusters of vertices.
        int search_radius = 9;
        for(int i = search_radius; i >= -search_radius; i-- ) {
            for(int j = search_radius; j >= -search_radius; j-- ) {

                // check that a vertex exists as that point, we don't already have an edge
                // connecting the two vertices, and that we're not adding a loop
                if ((vertices.find({my_x+i, my_y+j}) != vertices.end() &&
                     p.second.find({my_x+i, my_y+j}) == p.second.end()) &&
                     found < 3 &&
                     vertices.find({my_x+i, my_y+j})->second.size() < 4 && 
                    (i != 0 || j != 0)) {

                    // find the distance between the two points with pythagorean theorem
                    int a2 = (my_x-my_x+i)*(my_x-my_x+i);
                    int b2 = (my_y-my_y+j)*(my_y-my_y+j);
                    float c2 = sqrt(a2+b2);

                    // generate a random multiplier for the weight of this edge (to spice things up)
                    float r2 = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.0))) + 0.1;
                    float weight = c2*r2;

                    // we have a new edge,
                    //p.second.insert({{my_x+i, my_y+j}, weight});
                    (vertices.find({my_x, my_y}))->second.insert({{my_x+i, my_y+j}, weight});

                    // as does the edge we're linking to
                    (vertices.find({my_x+i, my_y+j}))->second.insert({{my_x, my_y}, weight});

                    //below is useful for testing.
                    //cout << "edge connecting (" << my_x << ", " << my_y << ") to (" << my_x+i << ", " << my_y+j << ")" << endl;

                    found++;
                    // we don't want to add more than 3 edges to this node right now
                    if (found == 3) {
                        // necessary evil as we need to break out of two loops
                        goto out;
                    }
                }
            }
        }
        out:;
    }
}

Graph::Graph() {
    this->initialize_graph();

}

vector<pair<int, int>> Graph::BFS(pair<int, int> from, pair<int, int> to) {
    vector<pair<int, int>> path;
    set<pair<int, int>> visited;
    queue<pair<int, int>> q;
    visited.insert(from);
    q.push(from);
    while(!q.empty())
    {
        pair<int, int> u = q.front();
        q.pop();
        for(auto v: vertices[u])
        {
            if(v.first == to)
                for (int i = 0; i < q.size(); i++) {
                    path.push_back(q.front());
                    q.pop();
                }
            if ((visited.find(v.first) == visited.end()))
            {
                visited.insert(v.first);
                q.push(v.first);
            }
        }
    }
    return path;
}

vector<pair<int, int>> Graph::DFS(pair<int, int> from, pair<int, int> to) {
    /*
        returns the sum of weights of all edges of shortest path
        connecting the from and to vertex. Returns 0 if no edges
        connect the two vertices.
        sources: https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
    */
    vector<pair<int, int>> path;
    set<pair<int, int>> visited;
    stack<pair<int, int>> s;
    visited.insert(from);
    s.push(from);
    while(!s.empty())
    {
        pair<int, int> u = s.top();
        s.pop();
        for(auto v: vertices[u])
        {
            if(v.first == to)
                for (int i = 0; i < s.size(); i++) {
                    path.push_back(s.top());
                    s.pop();
                }
            if ((visited.find(v.first) == visited.end()))
            {
                visited.insert(v.first);
                s.push(v.first);
            }
        }
    }
    return path;
}
