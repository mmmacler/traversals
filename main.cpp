#include <iostream>
#include <map>
#include <random>
#include <SFML/Graphics.hpp>
using namespace::std;
//#define x_max 1840
//#define y_max 1000
#define x_max 920
#define y_max 500

#define multiplier 14
#define vertex_radius 5
#define private public

struct Vertex {

    //TODO: Determine if we actually want to use this
    // to be potentially used with dijkstra's implementation
    bool visited;
    /*
    *  Stores edges connecting to adjacent vertices.
    *  The first value (pair) is the coordinate pair location of the vertex 
    *  that this vertex is adjacent to.
    *  The second value (float) is the cost to traverse to that vertex.
    */
    vector<pair<pair<int, int>, float>> adjacent_vertices;
};

class Graph {
    private:
        // Maps the coordinate location of a vertex to a vertex object
        map<pair<int, int>, Vertex> vertices;

        /*
         * This method generates the 100,000 vertices in our graph,
         * as well as the edges to go along with them. 
         * This is private as there's no need for it to get called
         * anywhere but in the initialization of the graph object. 
         */
        void initialize_graph() {
            //Random number generation taken from 
            //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(-(x_max/2), x_max/2);

            // Generate the 100,000 vertices
            // Uses a 'while' loop in case we generate duplicate values 
            // by chance, leading to less than 100k vertices
            while (vertices.size() < 10000) {
                int x = distr(gen);

                std::uniform_int_distribution<> distr(-(y_max/2), y_max/2);
                int y = distr(gen);

                Vertex temp;
                vertices.insert({{x, y}, temp});
            }

            //Generate edges and their weights
            //TODO: (this)
            for (auto p: this->vertices) {

            }
        }

    public:
        Graph() {
            this->initialize_graph();
        }
};

int main() {
    Graph* my_graph = new Graph();
    
    sf::RenderWindow window(sf::VideoMode(1840, 1000), "Traversals");
    sf::View view({0, 0}, {x_max*multiplier, y_max*multiplier});
    window.setView(view);

    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    //TODO: make this zoom in
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    //TODO: make this zoom out
                }
            }
            else if(event.type == sf::Event::Closed) {
                window.close();
            }          
        }

        window.clear();
        window.draw(shape);

        // very bad and very slow and very temporary way to draw every vertex
        // (redraws every frame and also uses a private var)
        for(auto p: my_graph->vertices) {
            sf::CircleShape temp(vertex_radius, 20);
            temp.setPosition(p.first.first*multiplier, p.first.second*multiplier);
            window.draw(temp);
        }

        window.display();
    }

    return 0;
}

