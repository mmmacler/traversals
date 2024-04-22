#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <SFML/Graphics.hpp>
using namespace::std;
//#define x_max 1840
//#define y_max 1000
#define x_max 800
#define y_max 500

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

class Graph {
    private:
        // Maps the coordinate location of a vertex to a vertex object
        map<pair<int, int>, Vertex> vertices;

        // This method generates the 100,000 vertices in our graph,
        // as well as the edges to go along with them. 
        void initialize_graph() { 
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
                Vertex temp;
                vertices.insert({{x, y}, temp});
            }

            //Generate edges and their weights
            for (auto p: this->vertices) {
                int found = 0;
                //just aliasing to shorter variable names
                int my_x = p.first.first;
                int my_y = p.first.second;

                // check a 17x17 area around the vertex for other vertices
                // we look further out first to avoid the problem of creating
                // isolated clusters of vertices.
                for(int i = 8; i >= -8; i-- ) {
                    for(int j = 8; j >= -8; j-- ) {

                        // check that a vertex exists as that point, we don't already have an edge
                        // connecting the two vertices, and that we're not adding a loop
                        if ((vertices.find({my_x+i, my_y+j}) != vertices.end() && 
                            p.second.adjacent_vertices.find({my_x+i, my_y+j}) == p.second.adjacent_vertices.end()) &&
                            (i != 0 || j != 0)) {
                            
                            // find the distance between the two points with pythagorean theorem
                            int a2 = (my_x-my_x+i)*(my_x-my_x+i);
                            int b2 = (my_y-my_y+i)*(my_y-my_y+i);
                            float c2 = sqrt(a2+b2);

                            // generate a random multiplier for the weight of this edge (to spice things up)
                            float r2 = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.0))) + 0.1;
                            float weight = c2*r2;

                            // we have a new edge,
                            p.second.adjacent_vertices.insert({{my_x+i,my_y+i}, weight});

                            // as does the edge we're linking to
                            vertices.find({my_x+i, my_y+j})->second.adjacent_vertices.insert({{my_x, my_y}, weight});

                            //below is useful for testing.
                            cout << "edge connecting (" << my_x << ", " << my_y << ") to (" << my_x+i << ", " << my_y+j << ")" << endl;
                            found++;
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

    public:
        Graph() {
            this->initialize_graph();
        }
};

int main() {
    Graph* my_graph = new Graph();
    
    // opens the window at 1840x1000 resolution with the title "Traversals"
    sf::RenderWindow window(sf::VideoMode(1840, 1000), "Traversals");

    // have the window display a 'View' rather than the raw objects
    // this is like having a movable camera show what's being rendered
    // and offers much better flexibility for things like zooming in 
    // and moving around
    sf::View view({0, 0}, {x_max*multiplier, y_max*multiplier});
    window.setView(view);

    // default SFML example circle, left in as a nice marking for where
    // the center of the view is
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);

     
    //this block may be useful for testing.
    int sum = 0;
    for (auto p: my_graph->vertices) {
        sum += p.second.adjacent_vertices.size();
    }

    cout << "Num of edges: " << (sum/2) << endl;
    cout << "Num of vertices: " << my_graph->vertices.size() << endl;
    /**/

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // listen for keypresses and do things when certain keys
            // are pressed
            if(event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    //TODO: make this zoom in?
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    //TODO: make this zoom out?
                }
            }
            else if(event.type == sf::Event::Closed) {
                window.close();
            }          
        }

        window.clear();
        window.draw(shape);

        // very bad and very slow and very temporary way to draw every vertex
        // (redraws every frame unnecessarily)
        for(auto p: my_graph->vertices) {
            
            // draw vertices
            sf::CircleShape temp(vertex_radius, 20);
            temp.setPosition(p.first.first*multiplier, p.first.second*multiplier);
            window.draw(temp);

            //draw edges (TODO)
        }

        window.display();
    }

    return 0;
}
